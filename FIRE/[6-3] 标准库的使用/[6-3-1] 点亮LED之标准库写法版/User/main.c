/**
  ******************************************************************************
  * @file    main.c
  * @author  PIG
  * @version V1.0
  * @date    2026/3/15
  * @brief   [6-3-1] 点亮LED之标准库写法版
  ******************************************************************************
  * @attention
  *文件最后要留出一行
  * 
  ******************************************************************************
  */
#include "stm32f10x.h"
int main(void)
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
    
//    //打开灯
//    GPIO_ResetBits(GPIOA, GPIO_Pin_1);//让端口引脚输出0，使得灯亮
//    GPIO_ResetBits(GPIOA, GPIO_Pin_2);//让端口引脚输出0，使得灯亮
//    GPIO_ResetBits(GPIOA, GPIO_Pin_3);//让端口引脚输出0，使得灯亮
    
    while (1);
}
