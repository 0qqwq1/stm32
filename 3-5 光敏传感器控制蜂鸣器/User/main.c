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
#include "Buzzer.h"
#include "Sensor.h"

int main(void)
{
    /* 初始化 */
	Buzzer_Init();
    Sensor_Init();
	
	while (1)
	{
        if (Sensor_Get() == 1)
        {
            Buzzer_ON();
        }
        else
        {
            Buzzer_OFF();
        }
    }
}
