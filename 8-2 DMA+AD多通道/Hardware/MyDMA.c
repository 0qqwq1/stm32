#include "stm32f10x.h"                  // Device header

/**
  * @brief  DMA初始化
  * @param  AddrA：外设寄存器起始地址
  * @param  AddrB：存储器起始地址
  * @param  Size：传输计数器的值
  * @retval 无
  */
void MyDMA_Init(uint32_t Addr)
{
    /* 开启时钟 */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    /* DMA初始化 */
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;                           //起始地址通过变量AddrA赋予
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;     //数据宽度为字节8位
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;             //开启地址自增
    DMA_InitStructure.DMA_MemoryBaseAddr= Addr;                                //起始地址通过变量AddrB赋予
    DMA_InitStructure.DMA_MemoryDataSize= DMA_MemoryDataSize_Byte;              //数据宽度为字节8位(这里的参数和外设寄存器的不一样)
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                     //开启地址自增(这里的参数和外设寄存器的不一样)
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                          //设置外设寄存器为源
    DMA_InitStructure.DMA_BufferSize = 4;                                    //传输计数器的值通过变量Size赋予
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                               //不开启自动重装器
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                 //开启软件触发
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                         //设置优先级
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    
    ADC_DMACmd(ADC1, ENABLE);
    
    /* DMA失能 */
    DMA_Cmd(DMA1_Channel1, ENABLE);
}


///**
//  * @brief  DMA转运
//  * @param  无
//  * @retval 无
//  */
//void MYDMA_Transfer(void)
//{
//    /* 更改传输计数器的值并使能DMA */
//    DMA_Cmd(DMA1_Channel1, DISABLE);                        //DMA失能
//    DMA_SetCurrDataCounter(DMA1_Channel1, MYDMA_Size);      //更改传输计数器的值并
//    DMA_Cmd(DMA1_Channel1, ENABLE);                         //DMA使能
//    
//    /* 检测并清除标志位 */
//    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);      //循环检测DMA1转运完成标志位，直至DMA1转运完成
//    DMA_ClearFlag(DMA1_FLAG_TC1);                           //清除标志位
//}
