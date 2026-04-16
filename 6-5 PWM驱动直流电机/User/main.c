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
#include "Motor.h"
#include "Key.h"

uint8_t KeyNum;
int8_t Speed;

int main(void)
{
    /* 初始化 */
    OLED_Init();
    Motor_Init();
    Key_Init();
    
    OLED_ShowString(1, 1, "Speed:");

    
	while (1)
	{
        KeyNum = Key_GetNum();      //循环获取KeyNum值,故不需要单独置0
        if (KeyNum)
        {
            Speed += 30;           
            if (Speed > 90)       
            {
                Speed = -90;
            }
            Motor_SetSpeed(Speed);
            OLED_ShowSignedNum(1, 7, Speed, 3);
        }
    }
}
