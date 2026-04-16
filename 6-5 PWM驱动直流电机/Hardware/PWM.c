#include "stm32f10x.h"                  // Device header

/**
  * @brief  PWM初始化
  * @param  无
  * @retval 无
  */
void PWM_Init(void)
{   
    /* 开启时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);        //TIM2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //GPIOA
    
    /* 配置GPIO */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;        //使用复用开漏/推挽输出，使片上外设(CH1)能够连接到输出控制在IO口输出
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* 配置定时器 */
    TIM_InternalClockConfig(TIM2);
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;        //ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;    //PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    /* 配置输出比较 */
    TIM_OCInitTypeDef TIM_OCInitStructure;      
    TIM_OCStructInit(&TIM_OCInitStructure);     //结构体未完全赋值，需要初始化，防止随机值
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High ;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable ;
    TIM_OCInitStructure.TIM_Pulse = 0;       //CCR
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    
    TIM_Cmd(TIM2, ENABLE);
}

/**
  * @brief  TIM2中CCR参数的单独控制
  * @param  Compare：CCR的取值。
  *     取值范围为0x0000到0xFFFF。
  * @retval 无
  */
void PWM_SetCompare3(uint16_t Compare)
{
    TIM_SetCompare3(TIM2, Compare);
}
