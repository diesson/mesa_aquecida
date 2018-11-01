#include "C_pwm.h"
#include "../lib/avr_timer.h"
#include "../lib/bits.h"
#include "../lib/avr_gpio.h"

void pwmInit(){

	// Saida[3] [PWM]
	GPIO_B->DDR  |= SET(PB3);
	GPIO_B->PORT |= UNSET(PB3);

	// Configuracao [Clear OC2B | Fast PWM - TOP: OCRA | Presc. 8 | TOP 255]
	TIMER_2->TCCRA = SET(COM2A1) | UNSET(COM2A0) | UNSET(COM2B1) | UNSET(COM2B0) | SET(WGM21) | SET(WGM20);
	TIMER_2->TCCRB = UNSET(WGM22) | SET(CS22) | UNSET(CS21) | UNSET(CS20);
	TIMER_2->OCRA = 0;
	//TIMER_2->OCRB = 50;

}

void pwmUpdate(uint8_t valor){
	if(valor < (PWMTOP + 1))
		TIMER_2->OCRA = valor;
}
