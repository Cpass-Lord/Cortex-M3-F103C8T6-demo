#ifndef _USART_H
#define _USART_H

#include <stdint.h>

typedef void (*usart_receivecallback_t)(uint8_t data);
typedef void (*dma_sendcompletecallback_t)(void);

void usart_init(void);
void usart_send_data_async(uint8_t *data, uint16_t len);
void usart_send_data(uint8_t *data, uint16_t len);
void usart_send_string(const char *string);
void usart_receive_register(usart_receivecallback_t callback);
void USART1_IRQHandler();
void dma_sendcomplete_register(dma_sendcompletecallback_t callback);
void DMA1_Channel4_IRQHandler();

#endif // !