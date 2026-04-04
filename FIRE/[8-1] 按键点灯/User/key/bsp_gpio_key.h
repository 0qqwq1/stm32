/**
  ******************************************************************************
  * @file    bsp_gpio_key.h
  * @author  RAIN
  * @version V1.0
  * @date    2026/3/21
  * @brief   KEY灯函数接口
  ******************************************************************************
  * @attention
  * 文件最后要留出一行
  * 
  ******************************************************************************
  */

#ifndef __BSP_GPIO_KEY_H
#define __BSP_GPIO_KEY_H

#include "stm32f10x.h"

/* 定义 KEY 连接的GPIO端口，用户只需要修改下面的代码即可改变控制的KEY引脚 */

//KEY1
#define KEY1_GPIO_PORT GPIOA                                /* GPIO端口 */
#define KEY1_GPIO_CLK_PORT RCC_APB2Periph_GPIOA             /* GPIO端口时钟 */
#define KEY1_GPIO_PIN  GPIO_Pin_0                           /* 对应PIN脚 */

/* 按键按下时的IO电平 */
typedef enum
{
    KEY_LOW_TRIGGER  = 0,
    KEY_HIGH_TRIGGER = 1,
}KEY_TriggerLevel;  
               
/* 按键的状态 */
typedef enum
{
    KEY_UP   = 0,
    KEY_DOWN = 1,
    KEY_INIT = 2, //按键初始状态
}KEY_Status; 

void KEY_GPIO_Config(void);

#endif /* __BSP_GPIO_KEY_H */

/************************** END OF FILE ****************************/
