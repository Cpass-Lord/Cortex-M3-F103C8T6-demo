#include <stm32f10x.h>
#include <stdbool.h>
#include <string.h>

#define LED_PIN GPIO_Pin_13
#define LED_PORT GPIOC

void led_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    memset(&GPIO_InitStructure, 0, sizeof(GPIO_InitTypeDef));
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(LED_PORT, &GPIO_InitStructure);
    GPIO_SetBits(LED_PORT, LED_PIN);
    GPIO_WriteBit(LED_PORT, LED_PIN, Bit_SET);
}

void led_set(bool on)
{
    GPIO_WriteBit(LED_PORT, LED_PIN, on ? Bit_RESET : Bit_SET);
}

void led_on()
{
    led_set(true);
}

void led_off()
{
    led_set(false);
}

void led_toggle()
{
    uint8_t state = GPIO_ReadOutputDataBit(LED_PORT, LED_PIN);
    if (state == (uint8_t)Bit_RESET)
    {
        led_off();
    }
    else
    {
        led_on();
    }
}