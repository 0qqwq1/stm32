#include "stm32f10x.h"                  // Device header
#include "PWM.h"

/**
  * @brief  Servo(舵机)初始化
  * @param  无
  * @retval 无
  */
void Servo_Init(void)
{
    PWM_Init();
}

/**
  * @brief  设置舵机角度
  * @param  Angle：舵机角度
  *     取值范围为0~180
  * @retval 无
  */
void Servo_SetAngel(float Angle)
{
    PWM_SetCompare2(Angle / 180 * 2000 + 500);
}
