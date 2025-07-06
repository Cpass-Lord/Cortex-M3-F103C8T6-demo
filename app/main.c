#include "main.h"

static void ontime(void)
{
    static uint32_t counter = 0;

    if (++counter == 500)
    {
        counter = 0;
        led_toggle(); // Toggle LED state
    }
}

int main(void)
{
    Overbroad_init();
    led_init();
    timer_init(1000);
    timer_elapsed_regiser(ontime);
    while (1)
    {
    }
}