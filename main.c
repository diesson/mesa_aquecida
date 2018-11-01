#ifndef F_CPU
#define F_CPU 14745600UL
#endif
/*

Arrumar botão
verificar NTC

*/
// AVR
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
// LIB
//#include "lib/avr_i2c.h"
#include "lib/TWI_Master.h"
#include "display/LCD_I2C.h"
#include "control.h"
#include "control/C_pwm.h"

extern volatile control_t controle;
extern fsm_t myFSM[];

int main(){

	controleInit();
	//i2c_init();
	TWI_Master_Initialise();
	sei();

	inic_LCD_4bits_i2c();

	_delay_ms(100);

	while(1){

		(*myFSM[controle.curr_state].func)();

	}

	return 0;

}
