/**
  ******************************************************************************
  * @file    Buzzer.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/4/5
  * @brief   蜂鸣器控制函数
  ******************************************************************************
  * @attention
  *
  * 无。
  ******************************************************************************
  */

#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
  * @brief  蜂鸣器初始化
  * @param  无
  * @retval 无
  */
void Buzzer_Init(void)
{
    /* 开启时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    /* 配置GPIO */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* GPIO状态初始化 */
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
}

/**
  * @brief  蜂鸣器开启
  * @param  无
  * @retval 无
  */
void Buzzer_ON(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

/**
  * @brief  蜂鸣器关闭
  * @param  无
  * @retval 无
  */
void Buzzer_OFF(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}


