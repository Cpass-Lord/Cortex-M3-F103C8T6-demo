#ifndef _LCD_SPI_H
#define _LCD_SPI_H

typedef void (*spi_senddata_completecallback_t)(void);

void spi_init(void);

void spi_send_data_async(uint8_t *data, uint16_t len);

void spi_send_cmd(uint8_t *data, uint16_t len);

void spi_senddata_register(spi_senddata_completecallback_t callback);

void DMA1_Channel3_IRQHandler();

#endif // !
