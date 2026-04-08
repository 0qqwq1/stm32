/**
  ******************************************************************************
  * @file    CountSensor.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/4/7
  * @brief   对射式红外传感器控制函数(计次)
  ******************************************************************************
  * @attention
  *
  * 无。
  ******************************************************************************
  */

#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count = 0;

/**
  * @brief  对射式红外传感器初始化，外部中断配置
  * @param  无
  * @retval 无
  */
void CountSensor_Init(void)
{
    /* 开启各设备时钟(EXTI和NVIC时钟始终开启，不用另外打开) */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    /* 配置GPIO */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* 配置AFUO */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

    /* 配置EXTI */
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
    
    /* 配置NVIC */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  获取计次值
  * @param  无
  * @retval CountSensor_Count：中断计次
  */
uint16_t CountSensor_Get(void)
{
    return CountSensor_Count;
}

/**
* @brief  中断函数(不需要声明)，中断一次计次一次。
  * @param  无
  * @retval CountSensor_Count：中断计次
  */
void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line14) == SET)
    {
        CountSensor_Count++;
        EXTI_ClearITPendingBit(EXTI_Line0); //清除中断函数标志位，防止标志位始终为1卡死
    }
}

