/**
  ******************************************************************************
  * @file    CountSensor.h
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

#ifndef __COUNT_SENSOR_H
#define __COUNT_SENSOR_H

void CountSensor_Init(void);
uint16_t CountSensor_Get(void);

#endif
