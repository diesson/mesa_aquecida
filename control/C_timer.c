#include "C_timer.h"

extern volatile control_t controle;

void timerInit(){

	TIMER_1->TCCRA = UNSET(COM1A1) | UNSET(COM1A0) | UNSET(COM1B1) | UNSET(COM1B0) | UNSET(WGM11) | UNSET(WGM10);
	TIMER_1->TCCRB = UNSET(WGM13) | SET(WGM12) | SET(CS12) | UNSET(CS11) | UNSET(CS10);
	TIMER_IRQS->TC1.BITS.OCIEA = 1;
	TIMER_1->OCRA = 57600; // 62500 [p/ 16MHz]

}

void timerOff(){

	controle.tempo[SECONDS] = 0;
	controle.tempo[MINUTES] = 0;
	controle.tempo[HOURS] = 0;
	TIMER_IRQS->TC1.BITS.OCIEA = 0;

}

ISR(TIMER1_COMPA_vect){

	controle.tempo[SECONDS]++;

	if(controle.tempo[SECONDS] > 59){
		controle.tempo[MINUTES]++;
		controle.tempo[SECONDS] = 0;
	}

	if(controle.tempo[MINUTES] > 59){
		controle.tempo[HOURS]++;
		controle.tempo[MINUTES] = 0;
	}

}

