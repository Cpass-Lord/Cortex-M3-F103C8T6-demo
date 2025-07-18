#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <stm32f10x.h>
#include <boardset.h>
#include <delay.h>

#include "led.h"
#include "usart.h"
#include "timer.h"
#include "st7735.h"
#include "mpu6050.h"
#include "pwm.h"
#include "rtc.h"
#include "esp32_at.h"
#include "weather.h"
#include "stimage.h"