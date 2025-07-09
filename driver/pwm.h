#ifndef _PWM_H
#define _PWM_H

#include <stdint.h>
#include <stdbool.h>

void pwm_init(uint32_t us);
void pwm_set_duty(uint32_t ch, uint32_t duty_us);
void pwm_start(void);
void pwm_stop(void);

#endif