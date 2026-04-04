/**
  ******************************************************************************
  * @file    bsp_gpio_key.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/3/21
  * @brief   扫描按键函数接口
  ******************************************************************************
  * @attention
  *文件最后要留出一行
  * 
  ******************************************************************************
  */

#include "key/bsp_gpio_key.h"

/**
  * @brief  初始化控制 KEY 的 IO
  * @param  无
  * @note   无
  * @retval 无
  */
void KEY_GPIO_Config(void)
{
    /* 定义一个 GPIO 结构体 */
    GPIO_InitTypeDef gpio_initstruct = {0};
    
/************************** 核心板载按键 ****************************/
#if 1
    /* 开启 KEY 相关的GPIO外设/端口时钟 */
    RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK_PORT, ENABLE);//开启端口时钟
    
    /* IO的输出状态初始化控制 */
    GPIO_SetBits(KEY1_GPIO_PORT, KEY1_GPIO_PIN);
    
    /* 选择要控制的GPIO引脚、设置GPIO模式为 浮空输入、设置GPIO速率为50MHz */
    gpio_initstruct.GPIO_Pin   = KEY1_GPIO_PIN;
    gpio_initstruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY1_GPIO_PORT, &gpio_initstruct);
    
#endif

}

/**
  * @brief  基础检测按键
  * @param  GPIOx：x 可以是 A、B、C等
  * @param  GPIO_Pin：待操作的pin脚号
  * @param  key_pressstatus：按键按下时的IO电平状态
  * @note   无
  * @retval KEY_UP(没有触发按键)、KEY_DOWN(触发按键)
  */
KEY_Status KEY_scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, KEY_TriggerLevel key_pressstatus)
{
    if (GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == key_pressstatus) //触发电平等于按键按下时的IO电平状态
    {
        while (GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == key_pressstatus) //如果为真，就一直循环到按键松开
            return KEY_DOWN;
    }
    else
    {
        return KEY_UP;
    }   
}

/**
  * @brief  初始化控制 KEY 的 IO
  * @param  无
  * @note   无
  * @retval 无
  */

/************************** END OF FILE ****************************/
