#include <stm32f10x.h>
#include <stdint.h>
#include <string.h>

#include "timer.h"

static timer_elapsedcallback_t timer_elapsedcallback;

void timer_init(uint32_t us)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    memset(&TIM_TimeBaseStructure, 0, sizeof(TIM_TimeBaseInitTypeDef));
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = us - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1; // Prescaler value, 72MHz / 72 = 1MHz

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_Cmd(TIM2, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure; // Define NVIC structure
    memset(&NVIC_InitStructure, 0, sizeof(NVIC_InitTypeDef));
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;           // Set timer interrupt channel
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5; // Set preemption priority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // Set sub-priority
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // Enable interrupt

    NVIC_Init(&NVIC_InitStructure); // Initialize NVIC structure
}

void timer_elapsed_regiser(timer_elapsedcallback_t callback)
{
    timer_elapsedcallback = callback;
}

void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        if (timer_elapsedcallback)
        {
            timer_elapsedcallback();
        }
        
    }
}
