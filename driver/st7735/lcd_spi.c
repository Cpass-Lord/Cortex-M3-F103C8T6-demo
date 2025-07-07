#include <stm32f10x.h>
#include <string.h>
#include <stdint.h>

#include "lcd_spi.h"

#define SPI_SCK_PIN GPIO_Pin_5
#define SPI_MOSI_PIN GPIO_Pin_7

static spi_senddata_completecallback_t spi_senddata_completecallback;

static void spi_gpio(void)
{
    GPIO_InitTypeDef GPIO_Initstructure;

    memset(&GPIO_Initstructure, 0, sizeof(GPIO_InitTypeDef));
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Initstructure.GPIO_Pin = SPI_SCK_PIN;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_Initstructure);
    GPIO_WriteBit(GPIOA, SPI_SCK_PIN, Bit_SET);

    memset(&GPIO_Initstructure, 0, sizeof(GPIO_InitTypeDef));
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Initstructure.GPIO_Pin = SPI_MOSI_PIN;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_Initstructure);
    GPIO_WriteBit(GPIOA, SPI_MOSI_PIN, Bit_SET);
}

static void spi_spi(void)
{
    SPI_InitTypeDef SPI_Initstructure;

    memset(&SPI_Initstructure, 0, sizeof(SPI_InitTypeDef));
    SPI_Initstructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_Initstructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_Initstructure.SPI_CPOL = SPI_CPOL_High;
    SPI_Initstructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_Initstructure.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_Initstructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Initstructure.SPI_Mode = SPI_Mode_Master;
    SPI_Initstructure.SPI_NSS = SPI_NSS_Soft;

    SPI_Init(SPI1, &SPI_Initstructure);
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
    SPI_Cmd(SPI1, ENABLE);
}

static void spi_nvic(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    memset(&NVIC_InitStructure, 0, sizeof(NVIC_InitTypeDef));
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

void spi_init(void)
{
    spi_gpio();
    spi_spi();
    spi_nvic();
}

void spi_send_data_async(uint8_t *data, uint16_t len)
{
    DMA_DeInit(DMA1_Channel3);

    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR; // USART1_DR_Base;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)data;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = len;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

    DMA_Init(DMA1_Channel3, &DMA_InitStructure);
    DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA1_Channel3, ENABLE);
}

void spi_send_cmd(uint8_t *data, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++)
    {
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
            ;
        SPI_I2S_SendData(SPI1, data[i]);
    }
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET)
        ;
}

void spi_senddata_register(spi_senddata_completecallback_t callback)
{
    spi_senddata_completecallback = callback;
}

void DMA1_Channel3_IRQHandler()
{
    if (DMA_GetFlagStatus(DMA1_FLAG_TC3) != RESET)
    {
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET)
            ;

        if (spi_senddata_completecallback)
        {
            spi_senddata_completecallback();
        }
        DMA_ClearITPendingBit(DMA1_IT_TC3);
    }
}