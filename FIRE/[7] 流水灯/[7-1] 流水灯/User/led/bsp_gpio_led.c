/**
  ******************************************************************************
  * @file    bsp_gpio_led.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/3/21
  * @brief   LED灯函数接口
  ******************************************************************************
  * @attention
  *文件最后要留出一行
  * 
  ******************************************************************************
  */

#include "led/bsp_gpio_led.h"

/**
  * @brief  初始化控制 LED 的 IO
  * @param  无
  * @note   无
  * @retval 无
  */
void LED_GPIO_Config(void)
{
    /* 定义一个 GPIO 结构体 */
    GPIO_InitTypeDef gpio_initstruct = {0};
    
/************************** 核心板载LED灯 ****************************/
#if 1
    /* 开启 LED 相关的GPIO外设/端口时钟 */
    RCC_APB2PeriphClockCmd(R_LED_GPIO_CLK_PORT, ENABLE);//开启端口时钟
    
    /* IO的输出状态初始化控制 */
    GPIO_SetBits(R_LED_GPIO_PORT, R_LED_GPIO_PIN);
    
    /* 选择要控制的GPIO引脚、设置GPIO模式为 推挽模式、设置GPIO速率为50MHz */
    gpio_initstruct.GPIO_Pin = R_LED_GPIO_PIN;
    gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(R_LED_GPIO_PORT, &gpio_initstruct);
    
#endif
    
#if 1
    
    /* 开启 LED 相关的 GPIO 外设/端口时钟 */
    RCC_APB2PeriphClockCmd(G_LED_GPIO_CLK_PORT, ENABLE);//开启端口时钟
    
    /* IO的输出状态初始化控制 */
    GPIO_SetBits(G_LED_GPIO_PORT, G_LED_GPIO_PIN);
    
    /* 选择要控制的GPIO引脚、设置GPIO模式为 推挽模式、设置GPIO速率为50MHz */
    gpio_initstruct.GPIO_Pin = G_LED_GPIO_PIN;
    gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(G_LED_GPIO_PORT, &gpio_initstruct);
    
#endif
    
#if 1
    /* 开启 LED 相关的GPIO外设/端口时钟 */
    RCC_APB2PeriphClockCmd(B_LED_GPIO_CLK_PORT, ENABLE);
    
    /* IO的输出状态初始化控制 */
    GPIO_SetBits(B_LED_GPIO_PORT, B_LED_GPIO_PIN);
    
    /* 选择要控制的GPIO引脚、设置GPIO模式为 推挽模式、设置GPIO速率为50MHz */
    gpio_initstruct.GPIO_Pin = B_LED_GPIO_PIN;
    gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(B_LED_GPIO_PORT, &gpio_initstruct);
    
#endif
}

/**
  * @brief  开启对应的 LED 灯
  * @param  GPIOx：x 可以是 A、B、C等
  * @param  GPIO_Pin：待操作的pin脚号 
  * @note   无
  * @retval 无
  */
void LED_ON(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_ResetBits(GPIOx, GPIO_Pin);
}

/**
  * @brief  开启对应的 LED 灯
  * @param  GPIOx：x 可以是 A、B、C等
  * @param  GPIO_Pin：待操作的pin脚号 
  * @note   无
  * @retval 无
  */
void LED_OFF(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_SetBits(GPIOx, GPIO_Pin);
}
