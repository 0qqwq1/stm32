/**
  ******************************************************************************
  * @file    流水灯.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/3/21
  * @brief   None.
  ******************************************************************************
  * @attention
  *文件最后要留出一行
  * 
  ******************************************************************************
  */
#include "stm32f10x.h"

void LED_GPIO_Config(void);
void LED_ON(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void LED_OFF(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Rough_Delay(__IO uint32_t ncount);
   
int main(void)
{
    LED_GPIO_Config();
    
    while (1)
    {
        //开灯
        LED_ON(GPIOA, GPIO_Pin_1);
        LED_ON(GPIOA, GPIO_Pin_2);
        LED_ON(GPIOA, GPIO_Pin_3);
        
        for (int i = 0; i < 20; i++)
            __NOP();
        
        //关灯
        LED_OFF(GPIOA, GPIO_Pin_1);
        LED_OFF(GPIOA, GPIO_Pin_2);
        LED_OFF(GPIOA, GPIO_Pin_3);
    }
}

void LED_GPIO_Config(void)
{
    GPIO_InitTypeDef gpio_initstruct = {0};
    
    //开启端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//开启端口时钟
    
    //关闭灯
    GPIO_SetBits(GPIOA, GPIO_Pin_1);//让端口引脚输出1，使得灯灭
    GPIO_SetBits(GPIOA, GPIO_Pin_2);//让端口引脚输出1，使得灯灭
    GPIO_SetBits(GPIOA, GPIO_Pin_3);//让端口引脚输出1，使得灯灭
    
    //配置io模式 推挽模式 50m
    gpio_initstruct.GPIO_Pin = GPIO_Pin_1;
    gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_initstruct);//配置端口引脚的模式
    
    gpio_initstruct.GPIO_Pin = GPIO_Pin_2;
//    gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
//    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_initstruct);//配置端口引脚的模式
    
    gpio_initstruct.GPIO_Pin = GPIO_Pin_3;
//    gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
//    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_initstruct);//配置端口引脚的模式
}

void LED_ON(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_ResetBits(GPIOx, GPIO_Pin);
}

void LED_OFF(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_SetBits(GPIOx, GPIO_Pin);
}

void Rough_Delay(__IO uint32_t ncount)
{
    for (uint32_t i = 0; i < ncount; i++)
        __NOP();
}
