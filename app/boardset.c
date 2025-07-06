#include <stm32f10x.h>

void Overbroad_init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}