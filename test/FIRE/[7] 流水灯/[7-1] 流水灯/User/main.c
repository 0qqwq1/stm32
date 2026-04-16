/**
  ******************************************************************************
  * @file    main.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/3/21
  * @brief   流水灯
  ******************************************************************************
  * @attention
  * 文件最后要留出一行
  * 
  ******************************************************************************
  */
#include "stm32f10x.h"
#include "led/bsp_gpio_led.h"
#include "delay/bsp_delay.h"

/**
  * @brief  主函数
  * @param  无
  * @note   无
  * @retval 无
  */
int main(void)
{
    uint32_t time_temp = 1000;
    LED_GPIO_Config();
    
    while (1)
    {
        R_LED_ON_ONLY;
        Rough_Delay_Ms(time_temp);
        
        G_LED_ON_ONLY;
        Rough_Delay_Ms(time_temp);
        
        B_LED_ON_ONLY;
        Rough_Delay_Ms(time_temp);
        
        for (uint32_t i = 0; i < 3; i++)
        {
        ALL_LED_ON;
        Rough_Delay_Ms(time_temp);
        
        ALL_LED_OFF;
        Rough_Delay_Ms(1000);
        }
    }
}


