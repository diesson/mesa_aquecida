#ifndef CONTROL_C_TIMER_H_
#define CONTROL_C_TIMER_H_

// Bibliotecas AVR
#include <avr/io.h>
#include <avr/interrupt.h>
// Bibliotecas DEJ
#include "../control.h"
#include "../lib/bits.h"
#include "../lib/avr_timer.h"
#include "../lib/avr_gpio.h"
#include "../lib/avr_extirq.h"
#include "../temperatura.h"

void timerInit();
void timerOff();

#endif /* CONTROL_C_TIMER_H_ */
