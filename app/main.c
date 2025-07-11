#include "main.h"

static char *wifi_ssid = "LastOrder";
static const char *wifi_password = "sbsbsb940";
static const char *weather_uri = "https://api.seniverse.com/v3/weather/now.json?key=SvbIvv6pNAQHgF5Aq&location=zhuzhou&language=en&unit=c";

int main(void)
{
    Overbroad_init();
    usart_init();
    st7735_init();
    rtc_init();
    st7735_fill_screen(ST7735_BLACK);
    delay_ms(2000);

    if (!esp_at_init())
    {
        while (1)
            ;
    }

    if (!esp_at_wifi_init())
    {
        while (1)
            ;
    }
    if (!esp_at_wifi_connect(wifi_ssid, wifi_password))
    {
        while (1)
            ;
    }

    bool weather_ok = false;
    bool sntp_ok = false;
    uint32_t t = 0;
    char str[64];
    while (1)
    {
        t++;
        delay_ms(1000);
        rtc_date_t date;
        rtc_get_date(&date);
        snprintf(str, sizeof(str), "%04d-%02d-%02d", date.year, date.month, date.day);
        st7735_write_string(0, 20, str, &font_ascii_8x16, ST7735_BLUE, ST7735_BLACK);
        snprintf(str, sizeof(str), "%02d:%02d:%02d", date.hour, date.minute, date.second);
        st7735_write_string(0, 40, str, &font_ascii_8x16, ST7735_BLUE, ST7735_BLACK);

        if (!weather_ok || t % 60 == 0)
        {
            const char *rsp;
            esp_at_http_get(weather_uri, &rsp, NULL, 1000);
            weather_t weather;
            weather_parse(rsp, &weather);

            snprintf(str, sizeof(str), "%s %s %sC", "zz", weather.weather, weather.temperature);
            st7735_write_string(0, 0, str, &font_ascii_8x16, ST7735_BLUE, ST7735_BLACK);
        }

        if (!sntp_ok || t % 3600 == 0)
        {
            uint32_t ts;
            sntp_ok = esp_at_sntp_init();
            esp_at_time_get(&ts);
            rtc_set_timestamp(ts+8*60*60);
        }
    }
}