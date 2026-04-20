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

uint16_t ADVaule;
float Voltage;

int main(void)
{
    /* 初始化 */
    OLED_Init();
    AD_Init();
    
    OLED_ShowString(1, 1, "ADVaule:");
    OLED_ShowString(2, 1, "Voltage:0.00V");
    
	while (1)
	{
        ADVaule = AD_GetVaule();
        Voltage = (float)ADVaule / 4095 * 3.3;      //根据比例获取电压值
        
        OLED_ShowNum(1, 9, ADVaule, 4);
        OLED_ShowNum(2, 9, Voltage, 1);     //将整数和小数部分分开显示，误差很大
        OLED_ShowNum(2, 11, (uint16_t)(Voltage * 100) % 100, 1);    //可以直接把电压值*100显示，较为精确
        
        Delay_ms(100);      //降低检测频率，减小抖动影响
    }
}
