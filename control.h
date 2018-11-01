#ifndef CONTROL_H_
#define CONTROL_H_

// AVR
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
// Control
#include "control/C_pwm.h"
#include "control/C_timer.h"
// LIB
#include "lib/bits.h"
#include "lib/avr_gpio.h"
#include "lib/avr_extirq.h"
#include "lib/avr_i2c.h"
#include "display/LCD_I2C.h"
#include "temperatura.h"

enum controle{OFF, ON};
enum time{SECONDS, MINUTES, HOURS};
typedef enum {SIM, NAO} opcao_t;
/* Definição dos estados */
typedef enum {
	ATIVO,
	DESATIVO,
	AJUSTE,
	DESLIGAR,
	NUM_STATES
} state_t;

/* Definição da estrutura mantenedora do vetor de estados */
typedef struct {
	state_t myState;
	void (*func)(void);
}fsm_t;

typedef struct{
	uint16_t PWMC;
	uint8_t temperatura;
	uint8_t ajuste;
	opcao_t opcao;
	uint8_t tempo[3];
	state_t curr_state;
}control_t;

// SM
void f_ativo();
void f_desativo();
void f_ajuste();
void f_desligar();

uint8_t tempContrl();
void pwmContrl(uint16_t n);
void controleInit();

#endif /* CONTROL_H_ */
/*
 * ADMUX
 *
 * REFS [Reference Selection Bits] - Seleciona a tensão de referencia do ADC
 * ADLAR [ADC Left Adjust Result] - Configuracao do ADCH e ADCL (Registradores com as informacoes)
 * MUX [Analog Channel Selection Bits] - Selecionar a entrada analogica conctada ao ADC
 *
 *
 * ADCSRA
 *
 * ADEN [ADC Enable] - Habilitar ADC
 * ADSC [ADC Start Conversion] - Ativar esse bit para comecar conversao
 * ADATE [ADC Auto Trigger Enable] -
 * ADIF [ADC Interrupt Flag] - Flag de saida
 * ADIE [ADC Interrupt Enable] - Ativa a interrupcao de conversao AD
 * ADPS [ADC Prescaler Select Bits] - Prescaler
 */
