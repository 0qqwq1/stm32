/**
  ******************************************************************************
  * @file    main.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/3/21
  * @brief   按键点灯
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
    LED_GPIO_Config();
    KEY_GPIO_Config();
    
    while (1)
    {

    }
}

/************************** END OF FILE ****************************/
