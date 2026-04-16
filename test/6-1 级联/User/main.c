#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t NUM1 = 0;  // TIM2中断计数（主定时器）
uint16_t NUM2 = 0;  // TIM3中断计数（从定时器）

int main(void)
{
    OLED_Init();
    Timer_Init();

    OLED_ShowString(1, 1, "TIM2:");
    OLED_ShowString(2, 1, "TIM3:");
    
    while (1)
    {
        OLED_ShowNum(1, 6, NUM1, 5);
        OLED_ShowNum(2, 6, NUM2, 5);
    }
}

// TIM2的中断服务函数（如果开启了可以加，但这里不需要）
// 我们只用TIM3的中断

// TIM3的中断服务函数
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
        NUM2++;  // 从定时器每10个脉冲中断一次
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

// 如果你想同时观察主定时器的中断，取消下面的注释
/*
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        NUM1++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
*/
