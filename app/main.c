#include "main.h"

static uint8_t rxdata[16];
static uint16_t rxlen;

static void usart_receivedata(uint8_t data)
{
    if (rxlen < 15)
    {
        rxdata[rxlen++] = data;
    }
}

int main(void)
{
    Overbroad_init();
    usart_init();
    usart_receive_register(usart_receivedata);
    st7735_init();
    st7735_fill_screen(ST7735_GREEN);
    const char str[] = "helloworld!";
    while (1)
    {
        usart_send_data(rxdata,rxlen);
        rxlen = 0;
        st7735_write_string(0, 0, (char *)rxdata, &font_ascii_8x16, ST7735_BLUE, ST7735_WHITE);
        st7735_write_string(0, 50, str, &font_ascii_8x16, ST7735_BLUE, ST7735_WHITE);
        st7735_write_fonts(0, 30, &font_ni_hao_shi_jie_16x16,0,4, ST7735_BLUE, ST7735_WHITE);

    }
}