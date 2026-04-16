#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void IC_Init(void)
{    
     /* 开启时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);        //输入捕获定时器使用TIM3
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //TIM3_CH1对应PA6
    
    /* 配置GPIO */                                              //接收TIM2输出的方波
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;              //使用复用开漏/推挽输出，使片上外设(CH1)能够连接到输出控制在IO口输出
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* 配置定时器 */
    TIM_InternalClockConfig(TIM3);
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;           //ARR 防止溢出
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;           //PSC 标准频率fc = 72M / (PSC + 1), 这里标准频率为1M
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    /* 配置输入捕获 */                                          //对输入的方波进行滤波，计次测周
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    
    /* 配置从模式 */ 
    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);                //TIM3被动接收外部信号，不需要配置主模式
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
    
    TIM_Cmd(TIM3, ENABLE);
}

/**
  * @brief  TIM2输出方波频率获取
  * @param  无
  * @retval TIM2输出方波的频率
  *     由TIM3_CH1输入捕获的CCR值根据对应公式求出，这里CCR理论上与TIM2对应通道的ARR值相等
  */
uint32_t IC_GetFreq(void)
{
    return 1000000 / (TIM_GetCapture1(TIM3) + 1);               //Freq = 72M / (PSC + 1) / (ARR + 1) 这里的+1是为了凑整
}

/**
  * @brief  TIM3中的CCR值检测
  * @param  无
  * @retval TIM3中的CCR值
  */
uint8_t IC_GetCapture1(void)
{
    TIM_GetCapture1(TIM3);
}