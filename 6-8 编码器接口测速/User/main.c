/**
  ******************************************************************************
  * @file    main.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/4/5
  * @brief   编码器接口测速
  ******************************************************************************
  * @attention
  *
  * 无。
  ******************************************************************************
  */
  
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"

int32_t Speed = 0;

int main(void)
{
    /* 初始化 */
    OLED_Init();
    Timer_Init();
    Encoder_Init();

    OLED_ShowString(1, 1, "Speed:");
    
	while (1)
	{
        OLED_ShowSignedNum(1, 8, Speed, 5);
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        Speed = Encoder_Get();
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
//使用extern定义可以跨函数使用变量

