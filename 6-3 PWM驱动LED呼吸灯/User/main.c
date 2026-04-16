/**
  ******************************************************************************
  * @file    main.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/4/5
  * @brief   按键点灯
  ******************************************************************************
  * @attention
  *
  * 无。
  ******************************************************************************
  */
  
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

uint8_t i;

int main(void)
{
    /* 初始化 */
    OLED_Init();
    PWM_Init();

	while (1)
	{
        for(i = 0; i < 100; i++)
        {
            PWM_SetCompare1(i);
            Delay_ms(10);       //避免LED闪烁太快观察不到现象
        }
        for(i = 0; i < 100; i++)
        {
            PWM_SetCompare1(100 - i);
            Delay_ms(10);
        }
    }
}
