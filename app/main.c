#include "main.h"

static bool dmaflag;

static void ontime(void)
{
    static uint32_t counter = 0;

    if (++counter == 500)
    {
        counter = 0;
        led_toggle(); // Toggle LED state
    }
}

static void dmastate(void)
{
    dmaflag = true;
}

int main(void)
{
    Overbroad_init();
    led_init();
    usart_init();
    timer_init(1000);
    timer_elapsed_regiser(ontime);
    dma_sendcomplete_register(dmastate);

    const char str[] = "Helloworld!";

    while (1)
    {
        dmaflag = false;
        usart_send_data_async((uint8_t *)str, strlen(str));
        delay_ms(1000);
        while (!dmaflag)
            ;
    }
}