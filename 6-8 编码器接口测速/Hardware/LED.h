/**
  ******************************************************************************
  * @file    LED.h
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

#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"                  // Device header

/** 
  * @brief   LED的状态声明
  */
typedef enum
{
    ON = 0,
    OFF,
} LED_StatusTypeDef;

/** 
  * @brief   LED的对应Pin脚声明
  */
#define LED1 GPIO_Pin_1
#define LED2 GPIO_Pin_2
#define LED3 GPIO_Pin_4
#define LED4 GPIO_Pin_6

void LED_Init(void);
void LED1_ON(void);
void LED2_ON(void);
void LED3_ON(void);
void LED4_ON(void);
void LED1_OFF(void);
void LED2_OFF(void);
void LED3_OFF(void);
void LED4_OFF(void);
void LED_Switch(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, LED_StatusTypeDef LED_Status);
void LED_Blink(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t ms);
void LED_Turn(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif /* __LED_H */
