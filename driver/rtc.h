#ifndef _RTC_H
#define _RTC_H

typedef struct
{
    uint16_t year;  // 0-99
    uint8_t month;  // 1-12
    uint8_t day;    // 1-31
    uint8_t hour;   // 0-23
    uint8_t minute; // 0-59
    uint8_t second; // 0-59
} rtc_date_t;

void rtc_init(void);
void rtc_set_date(rtc_date_t *date);
void rtc_get_date(rtc_date_t *date);

#endif