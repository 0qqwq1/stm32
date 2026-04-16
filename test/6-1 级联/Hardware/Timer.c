#include "stm32f10x.h"

void Timer_Init(void)
{
    // 1. 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
    // ========== 配置TIM2（主定时器）==========
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    
    // TIM2: 每500ms产生一次更新事件（72MHz / 7200 / 5000 = 2Hz）
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 5000 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;  // 72MHz/7200=10kHz
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    
    // 关键：TIM2作为主定时器，输出更新事件作为触发信号
    TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);  // 改为Update！
    
    // ========== 配置TIM3（从定时器）==========
    // TIM3使用TIM2的触发信号作为时钟（ITR2：TIM3的ITR2对应TIM2）
    TIM_ITRxExternalClockConfig(TIM3, TIM_TS_ITR2);
    
    // TIM3的时基配置：每收到10个脉冲中断一次
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;  // 不分频
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
    
    // 清除标志位
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    
    // 只开启TIM3的中断（TIM2不需要中断）
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    
    // NVIC配置（只配置TIM3中断）
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    
    // 启动定时器（先启从，再启主？实际上顺序无所谓，但建议先启主）
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
}

uint16_t Timer_GetCounter(void)
{
    return TIM_GetCounter(TIM3);
}
