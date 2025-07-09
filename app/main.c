#include "main.h"

int main(void)
{
    Overbroad_init();
    usart_init();
    st7735_init();
    st7735_fill_screen(ST7735_GREEN);

    rtc_init();
    rtc_date_t date = {2025, 7, 9, 22, 58, 0};
    rtc_set_date(&date);
    char str[64];
    // pwm_init(1000);       // Initialize PWM with 1ms period
    // pwm_set_duty(1, 100); // Set duty cycle for channel 1 to 10%
    // pwm_set_duty(2, 200); // Set duty cycle for channel 2 to 20%
    // pwm_set_duty(3, 300); // Set duty cycle for channel 3 to 33%
    // pwm_set_duty(4, 400); // Set duty cycle for channel 4 to 40%
    // pwm_start();          // Start PWM
    while (1)
    {
        delay_ms(100);
        rtc_get_date(&date);

        sprintf(str, "Year: %u", date.year);
        st7735_write_string(0, 0, str, &font_ascii_8x16, ST7735_WHITE, ST7735_BLACK);
        sprintf(str, "Month: %u", date.month);
        st7735_write_string(0, 16, str, &font_ascii_8x16, ST7735_WHITE, ST7735_BLACK);
        sprintf(str, "Day: %u", date.day);
        st7735_write_string(0, 32, str, &font_ascii_8x16, ST7735_WHITE, ST7735_BLACK);
        sprintf(str, "Hour: %u", date.hour);
        st7735_write_string(0, 48, str, &font_ascii_8x16, ST7735_WHITE, ST7735_BLACK);
        sprintf(str, "Minute: %u", date.minute);
        st7735_write_string(0, 64, str, &font_ascii_8x16, ST7735_WHITE, ST7735_BLACK);
        sprintf(str, "Second: %u", date.second);
        st7735_write_string(0, 80, str, &font_ascii_8x16, ST7735_WHITE, ST7735_BLACK);
    }
}