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
#include "Servo.h"
#include "Key.h"

uint8_t KeyNum;
float Angle;

int main(void)
{
    /* 初始化 */
    OLED_Init();
    Servo_Init();
    Key_Init();

    OLED_ShowString(1, 1, "Angle:");
    
	while (1)
	{
        KeyNum = Key_GetNum();      //循环获取KeyNum值,故不需要单独置0
        if (KeyNum)
        {
            Angle += 30;           
            if (Angle > 180)       
            {
                Angle = 0;
            }
            Servo_SetAngel(Angle);
            OLED_ShowNum(1, 7, Angle, 3);
        }
    }
}
