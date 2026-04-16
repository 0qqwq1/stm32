/**
  ******************************************************************************
  * @file    LED.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/4/5
  * @brief   LED控制函数
  ******************************************************************************
  * @attention
  *
  * 无。
  ******************************************************************************
  */

#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"

/**
  * @brief  LED初始化
  * @param  无
  * @retval 无
  */
void LED_Init(void)
{
    /* 开启时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* 配置GPIO */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* GPIO状态初始化 */
    GPIO_WriteBit(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6, Bit_SET);
}

void LED1_ON(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void LED2_ON(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

void LED3_ON(void)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
}

void LED4_ON(void)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_6, (BitAction)0);
}

void LED1_OFF(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

void LED2_OFF(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void LED3_OFF(void)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
}

void LED4_OFF(void)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_6, (BitAction)1);
}

/**
  * @brief  LED状态控制
  * @param  GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
  * @param  GPIO_Pin：指定要读取的端口位。
  *   此参数可以表示为 GPIO_Pin_x，其中 x 的取值范围为（0 至 15）。
  * @param  LED_Status：指定LED的新状态。
  *   此参数可设置为：ON 或 OFF。
  * @retval 无
  */
void LED_Switch(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, LED_StatusTypeDef LED_Status)
{
    GPIO_WriteBit(GPIOx, GPIO_Pin, (BitAction)LED_Status);
}

/**
  * @brief  LED闪烁
  * @param  GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
  * @param  GPIO_Pin：指定要读取的端口位。
  *   此参数可以表示为 GPIO_Pin_x，其中 x 的取值范围为（0 至 15）。
  * @param  ms：LED闪烁的延时长度。
  * @retval 无
  */
void LED_Blink(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t ms)
{
    LED_Switch(GPIOx, GPIO_Pin, ON);
    Delay_ms(ms);
    LED_Switch(GPIOx, GPIO_Pin, OFF);
    Delay_ms(ms);
}

/**
  * @brief  LED置反
  * @param  GPIOx：其中 x 可以是 (A..G) 以选择 GPIO 外设。
  * @param  GPIO_Pin：指定要读取的端口位。
  *   此参数可以表示为 GPIO_Pin_x，其中 x 的取值范围为（0 至 15）。
  * @retval 无
  */
void LED_Turn(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* 检测LED当前状态并置反 */
    if (GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin) == ON)
    {
        LED_Switch(GPIOx, GPIO_Pin, OFF);
    }
    else
    {
        LED_Switch(GPIOx, GPIO_Pin, ON);
    }
}
