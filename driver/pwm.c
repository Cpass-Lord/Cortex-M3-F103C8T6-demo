#include "stm32f10x.h" // Device header
#include "stdint.h"
#include <string.h>

void pwm_init(uint32_t us)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    memset(&GPIO_InitStructure, 0, sizeof(GPIO_InitTypeDef));
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   // Set pin mode to alternate function push-pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Set pin speed to 50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);            // Initialize GPIOA

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; // Define timer base structure
    memset(&TIM_TimeBaseStructure, 0, sizeof(TIM_TimeBaseInitTypeDef));
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1; // Prescaler value, 72MHz / 72 = 1MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_Period = us - 1; // Set period value, 1MHz / period_us = 1Hz
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); // Initialize timer base structure

    TIM_OCInitTypeDef TIM_OCInitStructure; // Define timer output compare structure
    memset(&TIM_OCInitStructure, 0, sizeof(TIM_OCInitTypeDef));
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             // Set PWM mode to PWM1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // Enable output state
    TIM_OCInitStructure.TIM_Pulse = 0;                            // Set pulse width to 50%
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     // Set polarity to high

    TIM_OC1Init(TIM3, &TIM_OCInitStructure); // Initialize timer output compare structure
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); // Enable preload register on TIM3
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3, ENABLE); // Enable auto-reload register on TIM3
}

void pwm_set_duty(uint32_t ch, uint32_t duty_us)
{
    switch (ch)
    {
    case 1:
        TIM_SetCompare1(TIM3, duty_us);
        break; // Set duty cycle for channel 1
    case 2:
        TIM_SetCompare2(TIM3, duty_us);
        break; // Set duty cycle for channel 2
    case 3:
        TIM_SetCompare3(TIM3, duty_us);
        break; // Set duty cycle for channel 3
    case 4:
        TIM_SetCompare4(TIM3, duty_us);
        break; // Set duty cycle for channel 4

    default:
        break;
    }
}

void pwm_start(void)
{
    TIM_Cmd(TIM3, ENABLE); // Start timer
}

void pwm_stop(void)
{
    TIM_Cmd(TIM3, DISABLE); // Stop timer
}