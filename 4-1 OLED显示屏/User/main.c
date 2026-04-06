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

uint8_t KeyNum;

int main(void)
{
    OLED_Init();

    OLED_ShowChar(1, 1, 'A');
    OLED_ShowString(1, 3, "HelloWorld!");
    OLED_ShowNum(2, 1, 12345, 5);
    OLED_ShowSignedNum(2, 8, -66, 2);
    OLED_ShowHexNum(3, 1, 0xAA55, 4);
    OLED_ShowBinNum(4, 1, 0xAA55, 16);
	while (1)
	{

    }
}
