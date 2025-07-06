#include <stm32f10x.h>
#include <string.h>
#include <stdint.h>

#include "usart.h"

static usart_receivecallback_t usart_receivecallback;
static dma_sendcompletecallback_t dma_sendcompletecallback;

static void
usart_gpio(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_Initstructure;
    memset(&GPIO_Initstructure, 0, sizeof(GPIO_InitTypeDef));
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_9; // TX
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_Initstructure);

    memset(&GPIO_Initstructure, 0, sizeof(GPIO_InitTypeDef));
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_10; // RX
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_Initstructure);
}

static void usart_usart(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    USART_InitTypeDef USART_Initstructure;
    memset(&USART_Initstructure, 0, sizeof(USART_InitTypeDef));
    USART_Initstructure.USART_BaudRate = 115200;                                    // 波特率
    USART_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件流控
    USART_Initstructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 // 工作模式
    USART_Initstructure.USART_Parity = USART_Parity_No;                             // 奇偶校验
    USART_Initstructure.USART_StopBits = USART_StopBits_1;                          // 停止位
    USART_Initstructure.USART_WordLength = USART_WordLength_8b;                     // 长度

    USART_Init(USART1, &USART_Initstructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
    USART_Cmd(USART1, ENABLE);
}

static void usart_nvic(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    memset(&NVIC_InitStructure, 0, sizeof(NVIC_InitTypeDef));
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    memset(&NVIC_InitStructure, 0, sizeof(NVIC_InitTypeDef));
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

void usart_init()
{
    usart_gpio();
    usart_usart();
    usart_nvic();
}

void usart_send_data_async(uint8_t *data, uint16_t len)
{
    DMA_DeInit(DMA1_Channel4);

    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR; // USART1_DR_Base;
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

    DMA_Init(DMA1_Channel4, &DMA_InitStructure);
    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA1_Channel4, ENABLE);
}

void usart_send_data(uint8_t *data, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++)
    {
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
            ;
        USART_SendData(USART1, data[i]);
    }
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        ;
}

void usart_send_string(const char *string)
{
    uint16_t lenth = strlen(string);
    usart_send_data((uint8_t *)string, lenth);
}

void usart_receive_register(usart_receivecallback_t callback)
{
    usart_receivecallback = callback;
}

void USART1_IRQHandler()
{
    if (USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET)
    {
        uint32_t data = USART_ReceiveData(USART1);
        if (usart_receivecallback)
        {
            usart_receivecallback(data);
        }
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

void dma_sendcomplete_register(dma_sendcompletecallback_t callback)
{
    dma_sendcompletecallback = callback;
}

void DMA1_Channel4_IRQHandler()
{
    if (DMA_GetFlagStatus(DMA1_FLAG_TC4) != RESET)
    {
        if (dma_sendcompletecallback)
        {
            dma_sendcompletecallback();
        }
        DMA_ClearITPendingBit(DMA1_IT_TC4);
    }
}