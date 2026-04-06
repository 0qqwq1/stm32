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
#include "LED.h"
#include "Key.h"

uint8_t KeyNum;

int main(void)
{
    /* LED及按键初始化 */
	LED_Init();
    Key_Init();
	
	while (1)
	{
        KeyNum = Key_GetNum();
        if (KeyNum == 1)
        {
            LED_Turn(GPIOA, LED1);
        }
        if (KeyNum == 2)
        {
            LED_Turn(GPIOA, LED2);
        }
    }
}
