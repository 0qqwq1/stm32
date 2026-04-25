#include "stm32f10x.h"                  // Device header

uint16_t AD_Vaule[4];       //这里不能删

/**
  * @brief  ADC初始化
  * @param  无
  * @retval 无
  */
void AD_Init(void)
{
    /* 开启时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    /* 配置ADC预分频器 */
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);       //72M / 6 = 12M < 14M
    
    /* GPIO初始化 */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;      //模拟输入模式，使GPIO口失效，防止输入输出对GPIO口产生干扰
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* 扫描ADC1通道 */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
    
    /* ADC初始化 */
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                      //开启连续模式
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                  //右对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;     //采用软件输入
    ADC_InitStructure.ADC_Mode =ADC_Mode_Independent ;                      //ADC独立使用
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;                            //开启扫描模式
    ADC_InitStructure.ADC_NbrOfChannel = 4;                                 //通道数目：在扫描模式下会用到4个通道
    ADC_Init(ADC1, &ADC_InitStructure);
    
    /* DMA初始化 */
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;                 //起始地址为寄存器ADC1_DR的地址
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;     //数据宽度为半字16位
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;                //关闭地址自增
    DMA_InitStructure.DMA_MemoryBaseAddr= (uint32_t)AD_Vaule;                       //起始地址通过数组AD_Vaule赋予
    DMA_InitStructure.DMA_MemoryDataSize= DMA_MemoryDataSize_HalfWord;              //数据宽度为半字16位
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                         //开启地址自增
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                              //设置外设寄存器为源
    DMA_InitStructure.DMA_BufferSize = 4;                                           //传输计数器的值设为4
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                                 //开启自动重装器
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                    //开启软件触发
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                             //设置优先级
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    
    /* DMA使能 */
    DMA_Cmd(DMA1_Channel1, ENABLE);
    
    /* ADC1的DMA通道激活 */
     ADC_DMACmd(ADC1, ENABLE);
     
    /* ADC触发 */
    ADC_Cmd(ADC1, ENABLE);
    
    /* ADC校准 */
    ADC_ResetCalibration(ADC1);                             //重置校准寄存器，将CR2_RSTCAL置1
    while (ADC_GetResetCalibrationStatus(ADC1) == SET);     //重复检测校准寄存器标志位，直至校准寄存器已初始化(CR2_RSTCAL置0)
    ADC_StartCalibration(ADC1);                             //开始校准，将CR2_CAL置1
    while (ADC_GetCalibrationStatus(ADC1));                 //重复检测校准寄存器标志位，直至校准完成(CR2_CAL置0)

    /* ADC软件触发 */
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

///**
//  * @brief  DMA更改传输计数器的值并使能，ADC软件触发
//  * @param  无。
//  * @retval 无
//  */
//void AD_GetVaule(void)
//{
//    /* 更改传输计数器的值并使能DMA */
//    DMA_Cmd(DMA1_Channel1, DISABLE);                        //DMA失能
//    DMA_SetCurrDataCounter(DMA1_Channel1, 4);               //更改传输计数器的值
//    DMA_Cmd(DMA1_Channel1, ENABLE);                         //DMA使能
//    
//    ADC_SoftwareStartConvCmd(ADC1, ENABLE);                 //软件触发
//    
//    /* 检测并清除标志位 */                                  //转运在转换之后
//    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);      //循环检测DMA1转运完成标志位，直至DMA1转运完成
//    DMA_ClearFlag(DMA1_FLAG_TC1); 
//} 
//也可以配置ACD和DMA都为单次模式，用主调函数中的while (1)实现连续获取并转运，但是更耗软件资源，性价比不高
