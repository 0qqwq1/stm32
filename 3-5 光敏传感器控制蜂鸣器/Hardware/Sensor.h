/**
  ******************************************************************************
  * @file    Sensor.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/4/5
  * @brief   按传感器控制函数
  ******************************************************************************
  * @attention
  *
  * 无。
  ******************************************************************************
  */

#ifndef __Sensor_H
#define __Sensor_H

void Sensor_Init(void);
void Sensor_Trigger(void);
uint8_t Sensor_Get(void);

#endif /* __Sensor_H */
