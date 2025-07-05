#include "main.h"

int main(void)
{
    led_init();
    
    while (1)
    {
        led_on();
    }
}