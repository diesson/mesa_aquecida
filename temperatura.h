#ifndef TEMPERATURA_H_
#define TEMPERATURA_H_

// AVR
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <avr/interrupt.h>
// Control
#include "control/C_pwm.h"
#include "control/C_timer.h"
#include "control.h"
// LIB
#include "lib/bits.h"
#include "lib/avr_gpio.h"
#include "lib/avr_adc.h"
#include "lib/avr_timer.h"

#define ADC_INF 	450
#define ADC_SUP 	950
#define ADC_BUFF 	8

void tempInit();
uint16_t TempGet();
//uint16_t adcGet();
void adcInit();

#endif /* TEMPERATURA_H_ */
