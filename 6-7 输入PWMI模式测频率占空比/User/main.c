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
#include "IC.h"

uint8_t i;

int main(void)
{
    /* 初始化 */
    OLED_Init();
    PWM_Init();
    IC_Init();
    
    OLED_ShowString(1, 1, "Freq:00000Hz");
    OLED_ShowString(2, 1, "Duty:00%");

    PWM_SetPrescaler(7200 - 1);          //Freq = 72M / (PSC + 1) / 100
    PWM_SetCompare1(500);                //Duty = CRR / 100
    
	while (1)
	{
        OLED_ShowNum(1, 6, IC_GetFreq(), 5);
        OLED_ShowNum(2, 6, IC_GetDuty(), 2);
    }
}
