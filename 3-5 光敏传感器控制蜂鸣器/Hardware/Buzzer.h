/**
  ******************************************************************************
  * @file    Buzzer.h
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

#ifndef __Buzzer_H
#define __Buzzer_H

#include "stm32f10x.h"                  // Device header

void Buzzer_Init(void);
void Buzzer_ON(void);
void Buzzer_OFF(void);

#endif /* __Buzzer_H */
