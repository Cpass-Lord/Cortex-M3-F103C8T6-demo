#include <stm32f10x.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "esp32_usart.h"

static esp_usart_receivecallback_t esp_usart_receivecallback;
static esp_dma_sendcompletecallback_t esp_dma_sendcompletecallback;

static void esp_usart_gpio(void)
{
    GPIO_InitTypeDef GPIO_Initstructure;
    memset(&GPIO_Initstructure, 0, sizeof(GPIO_InitTypeDef));
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_2; // TX
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_Initstructure);

    memset(&GPIO_Initstructure, 0, sizeof(GPIO_InitTypeDef));
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_3; // RX
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_Initstructure);
}

static void esp_usart_usart(void)
{
    USART_InitTypeDef USART_Initstructure;
    memset(&USART_Initstructure, 0, sizeof(USART_InitTypeDef));
    USART_Initstructure.USART_BaudRate = 115200;                                    // 波特率
    USART_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件流控
    USART_Initstructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 // 工作模式
    USART_Initstructure.USART_Parity = USART_Parity_No;                             // 奇偶校验
    USART_Initstructure.USART_StopBits = USART_StopBits_1;                          // 停止位
    USART_Initstructure.USART_WordLength = USART_WordLength_8b;                     // 长度

    USART_Init(USART2, &USART_Initstructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
    USART_Cmd(USART2, ENABLE);
}

static void esp_usart_nvic(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    memset(&NVIC_InitStructure, 0, sizeof(NVIC_InitTypeDef));
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    memset(&NVIC_InitStructure, 0, sizeof(NVIC_InitTypeDef));
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

void esp_usart_init()
{
    esp_usart_gpio();
    esp_usart_usart();
    esp_usart_nvic();
}

void esp_usart_send_data_async(uint8_t *data, uint16_t len)
{
    DMA_DeInit(DMA1_Channel7);

    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR; // USART1_DR_Base;
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

    DMA_Init(DMA1_Channel7, &DMA_InitStructure);
    DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA1_Channel7, ENABLE);
}

void esp_usart_send_data(uint8_t *data, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++)
    {
        while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
            ;
        USART_SendData(USART2, data[i]);
    }
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
        ;
}

void esp_usart_send_string(const char *string)
{
    uint16_t lenth = strlen(string);
    esp_usart_send_data((uint8_t *)string, lenth);
}

void esp_usart_receive_register(esp_usart_receivecallback_t callback)
{
    esp_usart_receivecallback = callback;
}

void USART2_IRQHandler()
{
    if (USART_GetFlagStatus(USART2, USART_IT_RXNE) != RESET)
    {
        uint32_t data = USART_ReceiveData(USART2);
        if (esp_usart_receivecallback)
        {
            esp_usart_receivecallback(data);
        }
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}

void esp_dma_sendcomplete_register(esp_dma_sendcompletecallback_t callback)
{
    esp_dma_sendcompletecallback = callback;
}

void DMA1_Channel7_IRQHandler()
{
    if (DMA_GetFlagStatus(DMA1_FLAG_TC7) != RESET)
    {
        if (esp_dma_sendcompletecallback)
        {
            esp_dma_sendcompletecallback();
        }
        DMA_ClearITPendingBit(DMA1_IT_TC7);
    }
}