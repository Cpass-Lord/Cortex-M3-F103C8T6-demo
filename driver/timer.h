#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>

typedef void (*timer_elapsedcallback_t)(void);

void timer_init(uint32_t us);
void timer_elapsed_regiser(timer_elapsedcallback_t callback);
void TIM2_IRQHandler();

#endif // !
