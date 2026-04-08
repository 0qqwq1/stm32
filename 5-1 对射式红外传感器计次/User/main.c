/**
  ******************************************************************************
  * @file    main.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/4/5
  * @brief   对射式红外传感器计次
  ******************************************************************************
  * @attention
  *
  * 对射式红外传感器还没买。
  ******************************************************************************
  */
  
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

int main(void)
{
    /* 初始化 */
    OLED_Init();
    CountSensor_Init();

    OLED_ShowString(1, 1, "Count:");
    
	while (1)
	{
        OLED_ShowSignedNum(1, 7, CountSensor_Get(), 5);
    }
}
