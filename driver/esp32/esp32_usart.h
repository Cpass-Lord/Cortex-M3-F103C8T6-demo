#ifndef _ESP_USART_H
#define _ESP_USART_H

#include <stdint.h>

typedef void (*esp_usart_receivecallback_t)(uint8_t data);
typedef void (*esp_dma_sendcompletecallback_t)(void);

void esp_usart_init(void);
void esp_usart_send_data_async(uint8_t *data, uint16_t len);
void esp_usart_send_data(uint8_t *data, uint16_t len);
void esp_usart_send_string(const char *string);
void esp_usart_receive_register(esp_usart_receivecallback_t callback);
void USART2_IRQHandler();
void esp_dma_sendcomplete_register(esp_dma_sendcompletecallback_t callback);
void DMA1_Channel7_IRQHandler();

#endif // !