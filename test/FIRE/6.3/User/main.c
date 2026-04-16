/**
  ******************************************************************************
  * @file    6.3
  * @author  RAIN
  * @version V1.0
  * @date    2026/3/20
  * @brief   None.
  ******************************************************************************
  * @attention
  *
  * None.
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
int main(void)
{
    GPIO_InitTypeDef gpio_initstruct = {0};
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
    GPIO_SetBits(GPIOA, GPIO_Pin_2);
    GPIO_SetBits(GPIOA, GPIO_Pin_3);
    
    gpio_initstruct.GPIO_Pin   = GPIO_Pin_1;
    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_initstruct.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &gpio_initstruct);
    
    gpio_initstruct.GPIO_Pin   = GPIO_Pin_2;
    GPIO_Init(GPIOA, &gpio_initstruct);
    
    gpio_initstruct.GPIO_Pin   = GPIO_Pin_3;
    GPIO_Init(GPIOA, &gpio_initstruct);
    
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);
    while(1);
}
