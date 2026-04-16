#include "stm32f10x.h"                  // Device header
#include "PWM.h"

/**
* @brief  电机初始化
  * @param  无
  * @retval 无
  */
void Motor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
 
    PWM_Init();
}

/**
  * @brief  电机速度设置
  * @param  无
  * @retval Speed：电机旋转方向和转速
  *     取值范围为-90~90
  */
void Motor_SetSpeed(int8_t Speed)
{
    if (Speed >= 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        TIM_SetCompare3(TIM2, Speed);
    }
    else
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
        TIM_SetCompare3(TIM2, -Speed);
    }
}
