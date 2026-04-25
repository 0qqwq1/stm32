/**
  ******************************************************************************
  * @file    Key.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/4/5
  * @brief   按键控制函数
  ******************************************************************************
  * @attention
  *
  * 无。
  ******************************************************************************
  */

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
  * @brief  按键初始化
  * @param  无
  * @retval 无
  */
void Key_Init(void)
{
    /* 开启时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    /* 配置GPIO */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief  按键触发电平检测
  * @param  GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
  * @param  GPIO_Pin：指定要读取的端口位。
  *   此参数可以表示为 GPIO_Pin_x，其中 x 的取值范围为（0 至 15）。
  * @retval KeyNum：触发的按键编号
  */
uint8_t Key_GetNum(void)
{
    uint8_t KeyNum = 0;
    
    //GPIO_ReadInputDataBit()：检测触发电平是高电平还是低电平
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
    {
        Delay_ms(20); //消抖
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);  //持续到按键松开
        Delay_ms(20);
        KeyNum = 1;
    }
    
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
    {
        Delay_ms(20); 
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0);  //持续到按键松开
        Delay_ms(20);
        KeyNum = 2;
    }
    
    return KeyNum;
}
