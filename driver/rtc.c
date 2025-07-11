#include "stm32f10x.h" // Device header
#include "rtc.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// 日期验证函数
static bool date_validate(const rtc_date_t *date)
{
    if (date->year < 1970 || date->year > 2099)
        return false;
    if (date->month < 1 || date->month > 12)
        return false;
    if (date->day < 1 || date->day > 31)
        return false;
    if (date->hour > 23)
        return false;
    if (date->minute > 59)
        return false;
    if (date->second > 59)
        return false;
    return true;
}

// 日期转时间戳
uint32_t date_to_ts(const rtc_date_t *date)
{
    uint16_t year = date->year;
    uint8_t month = date->month;
    uint8_t day = date->day;
    uint8_t hour = date->hour;
    uint8_t minute = date->minute;
    uint8_t second = date->second;

    // 调整月份计算
    month -= 2;
    if (month <= 0)
    {
        month += 12;
        year -= 1;
    }

    // 计算时间戳
    return (((year / 4 - year / 100 + year / 400 + 367 * month / 12 + day +
              year * 365 - 719499) *
                 24 +
             hour) *
                60 +
            minute) *
               60 +
           second;
}

// 时间戳转日期
void ts_to_date(uint32_t seconds, rtc_date_t *date)
{
    const uint32_t mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const uint16_t ONE_YEAR_HOURS = 8760;

    memset(date, 0, sizeof(rtc_date_t));

    // 计算秒/分
    date->second = seconds % 60;
    seconds /= 60;
    date->minute = seconds % 60;
    seconds /= 60;

    // 计算年
    uint32_t leapyears = seconds / (1461 * 24);
    date->year = (leapyears << 2) + 1970;
    seconds %= 1461 * 24;

    // 计算剩余时间
    while (1)
    {
        uint32_t yearhours = ONE_YEAR_HOURS;
        if ((date->year & 3) == 0)
            yearhours += 24; // 闰年

        if (seconds < yearhours)
            break;

        date->year++;
        seconds -= yearhours;
    }

    // 计算时
    date->hour = seconds % 24;
    seconds /= 24;
    seconds++;

    // 处理闰年2月29日
    if ((date->year & 3) == 0)
    {
        if (seconds == 60)
        {
            date->month = 2;
            date->day = 29;
            return;
        }
        else if (seconds > 60)
        {
            seconds--;
        }
    }

    // 计算月/日
    date->month = 0;
    while (seconds > mdays[date->month])
    {
        seconds -= mdays[date->month];
        date->month++;
    }
    date->month++;
    date->day = seconds;
}

void rtc_init(void)
{
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForSynchro();
    RTC_WaitForLastTask();   // Wait for last task to complete
    RTC_SetPrescaler(32767); // Set prescaler to 32767 for 1Hz
    RTC_WaitForLastTask();   // Wait for last task to complete
}
void rtc_set_date(rtc_date_t *date)
{
    if (!date_validate(date))
        return;

    uint32_t ts = date_to_ts(date);
    RTC_WaitForLastTask();
    RTC_SetCounter(ts);    // Set RTC counter to timestamp
    RTC_WaitForLastTask(); // Wait for last task to complete
}
void rtc_get_date(rtc_date_t *date)
{
    uint32_t ts = RTC_GetCounter(); // Get RTC counter value
    if (date)
    {
        ts_to_date(ts, date); // Convert timestamp to date structure
    }
}

void rtc_set_timestamp(uint32_t timesatmp)
{
    RTC_WaitForLastTask();
    RTC_SetCounter(timesatmp);
    RTC_WaitForLastTask();
}

void rtc_get_timestamp(uint32_t *timesatmp)
{

    if (timesatmp)
    {
        *timesatmp = RTC_GetCounter();
    }
}