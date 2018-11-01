#include "control.h"

/* Mapeamento entre estado e funções */
fsm_t myFSM[] = {
	{ ATIVO, f_ativo },
	{ DESATIVO, f_desativo },
	{ AJUSTE, f_ajuste },
	{ DESLIGAR, f_desligar }
};

volatile control_t controle;
volatile uint8_t stop = 0;

// Motor
void controleInit(){

	GPIO_D->DDR  |= SET(PD0) | SET(PD1);
	GPIO_D->PORT |= SET(PD0) | SET(PD1);

	PCICR = SET(PCIE2);
	PCMSK2 = SET(PCINT16) | SET(PCINT17);

	controle.PWMC = 0;
	controle.temperatura = 25;
	controle.ajuste = 79;
	controle.opcao = SIM;
	controle.tempo[0] = 0;
	controle.tempo[1] = 0;
	controle.tempo[2] = 0;
	controle.curr_state = DESATIVO;
	pwmInit();
	tempInit();

}

uint8_t tempContrl(){
	return controle.temperatura;
}

void pwmContrl(uint16_t n){
	controle.PWMC = n;
}


void f_ativo(){

	timerInit();

	cmd_LCD_i2c(0x80,0);
	fprintf(inic_stream_i2c(), "Temp.       %3dC", controle.temperatura);

	cmd_LCD_i2c(0xC0,0);
	fprintf(inic_stream_i2c(), "%2d,%1dC   %02d:%02d:%02d", TempGet()/10, TempGet()%10, controle.tempo[HOURS], controle.tempo[MINUTES], controle.tempo[SECONDS]);

	_delay_ms(800);
	stop = 0;

}

void f_desativo(){
	cmd_LCD_i2c(0x80,0);
	fprintf(inic_stream_i2c(), "Temp.           ");
	cmd_LCD_i2c(0xC0,0);

	fprintf(inic_stream_i2c(), "%2d,%1dC      Desl.", TempGet()/10, TempGet()%10);

	_delay_ms(800);
	stop = 0;
}

void f_ajuste(){
	GPIO_D->DDR  |= SET(PD2) | SET(PD3);
	GPIO_D->PORT |= SET(PD2) | SET(PD3);

	if(!tst_bit(PIND,PD2)){
		_delay_ms(200);
		controle.ajuste++;
	}else if(!tst_bit(PIND,PD3)){
		_delay_ms(200);
		controle.ajuste--;
	}

	cmd_LCD_i2c(0xC0,0);
	fprintf(inic_stream_i2c(), "%2d,%1dC   %02d:%02d:%02d", TempGet()/10, TempGet()%10, controle.tempo[HOURS], controle.tempo[MINUTES], controle.tempo[SECONDS]);

	cmd_LCD_i2c(0x80,0);
	fprintf(inic_stream_i2c(), "Temp.       %3dC", controle.ajuste);

	_delay_ms(200);

	cmd_LCD_i2c(0x80,0);
	fprintf(inic_stream_i2c(), "Temp.           ");

	_delay_ms(100);
	stop = 0;
}

void f_desligar(){
	cmd_LCD_i2c(0x80,0);
	fprintf(inic_stream_i2c(), "Desligar?       ");
	cmd_LCD_i2c(0xC0,0);
	if(controle.opcao == SIM)
		fprintf(inic_stream_i2c(), "   SIM    nao   ");
	else if(controle.opcao == NAO)
		fprintf(inic_stream_i2c(), "   sim    NAO   ");

	if(!tst_bit(PIND,PD2)){
		_delay_ms(200);
		if(controle.opcao == SIM)
			controle.opcao = NAO;
		else
			controle.opcao = SIM;
	}else if(!tst_bit(PIND,PD3)){
		_delay_ms(200);
		if(controle.opcao == SIM)
			controle.opcao = NAO;
		else
			controle.opcao = SIM;
	}

	_delay_ms(100);

	stop = 0;
}

ISR(PCINT2_vect){

	if((!tst_bit(PIND,PD0)) && (stop  == 0)){ // Botao de ligar/desligar
		switch (controle.curr_state) {
			case ATIVO:
				controle.curr_state = DESLIGAR;
				break;

			case DESATIVO:
				controle.curr_state = AJUSTE;
				break;

			case AJUSTE:
				controle.curr_state = ATIVO;
				break;

			case DESLIGAR:
				controle.opcao = SIM;
				controle.curr_state = ATIVO;
				break;
			default:
				break;
		}
	}else if((!tst_bit(PIND,PD1)) && (stop  == 0)){ // Botao de ajuste
		switch (controle.curr_state) {
			case ATIVO:
				controle.ajuste = controle.temperatura;
				controle.curr_state = AJUSTE;
				break;

			case AJUSTE:
				controle.temperatura = controle.ajuste;
				controle.curr_state = ATIVO;
				break;

			case DESLIGAR:
				if(controle.opcao == SIM){
					timerOff();
					controle.PWMC = 0;
					pwmUpdate(controle.PWMC);
					controle.ajuste = 80;
					controle.temperatura = 25;
					controle.curr_state = DESATIVO;
				}else{
					controle.opcao = SIM;
					controle.curr_state = ATIVO;
				}
				break;

			default:
				break;
		}
	}

	stop = 1;

}
