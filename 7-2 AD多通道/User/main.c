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
#include "AD.h"

int main(void)
{
    /* 初始化 */
    OLED_Init();
    AD_Init();
    
    OLED_ShowString(1, 1, "AD0:");
    OLED_ShowString(2, 1, "AD1:");
    OLED_ShowString(3, 1, "AD2:");
    OLED_ShowString(4, 1, "AD3:");
    
	while (1)
	{
        //通过连续改变序列1中的通道来实现处理多个值的效果
        OLED_ShowNum(1, 5, AD_GetVaule(ADC_Channel_0), 4);  
        OLED_ShowNum(2, 5, AD_GetVaule(ADC_Channel_1), 4);
        OLED_ShowNum(3, 5, AD_GetVaule(ADC_Channel_2), 4);
        OLED_ShowNum(4, 5, AD_GetVaule(ADC_Channel_3), 4);      
        
        Delay_ms(100);
    }
}
