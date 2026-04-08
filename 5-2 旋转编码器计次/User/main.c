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
#include "Encoder.h"

int16_t Num = 0;

int main(void)
{
    OLED_Init();
    Encoder_Init();

    OLED_ShowString(1, 1, "Count:");

	while (1)
	{
        Delay_ms(50);
        Num += Encoder_Get();
        OLED_ShowSignedNum(1, 7, Num, 5);
        Delay_ms(50);
    }
}
