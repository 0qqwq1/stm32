#include "stm32f10x.h"                  // Device header

/**
  * @brief  编码器输入初始化
  * @param  无
  * @retval 无
  */
void Encoder_Init(void)
{
    /* 开启TIM3,GPIO时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* GPIO初始化 */
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
    
    /* 输入捕获初始化 */
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
//    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
//    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI ;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    
    /* 编码器输入配置 */
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, 
    TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);          //这里配置了两条通道的极性，所以上面输入捕获初始化可以不用配置
    
    /* TIM3初始化 */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
    
    /* TIM3使能 */
    TIM_Cmd(TIM3, ENABLE);
}

/**
  * @brief  读取TIM3计数值并清零
  * @param  无
  * @retval TIM3计数值的缓存值，计数值已清零
  */
int32_t Encoder_Get(void)
{
    int16_t Temp;                   //CNT缓冲值
	Temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);        //CNT清零
	return Temp;                    //返回缓冲值
}
