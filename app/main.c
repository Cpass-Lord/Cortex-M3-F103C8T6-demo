#include "main.h"

static uint8_t rxdata[16];
static uint16_t rxlen;

static void usart_receive(uint8_t data)
{
    if (rxlen < 15)
    {
        rxdata[rxlen++] = data;
    }
}

int main(void)
{
    usart_init();
    usart_receive_register(usart_receive);
    while (1)
    {
        if (rxlen > 0)
        {
            usart_send_string("receive:");
            usart_send_data(rxdata, rxlen);
            rxlen = 0;
            usart_send_string("\r\n");
        }
    }
}