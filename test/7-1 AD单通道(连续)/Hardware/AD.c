#include "stm32f10x.h"                  // Device header

/**
  * @brief  ADC初始化
  * @param  无
  * @retval 无
  */
void AD_Init(void)
{
    /* 开启ADC1、GPIOA的时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* 配置ADC预分频器 */
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);       //72M / 6 = 12M < 14M
    
    /* GPIO初始化 */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;      //模拟输入模式，使GPIO口失效，防止输入输出对GPIO口产生干扰
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* 通道选择 */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);     //选择ADC1，在序列1放入通道0，采样时间为55.5个周期
    
    /* ADC初始化 */
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;     //关闭连续模式
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;      //右对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;     //采用软件输入
    ADC_InitStructure.ADC_Mode =ADC_Mode_Independent ;      //ADC独立使用
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;       //关闭扫描模式
    ADC_InitStructure.ADC_NbrOfChannel = 1;     //通道数目：在扫描模式下会用到几个通道
    ADC_Init(ADC1, &ADC_InitStructure);
    
    //这里可以配置中断，模拟看门狗
    
    /* ADC触发 */
    ADC_Cmd(ADC1, ENABLE);
    
    /* ADC校准 */
    ADC_ResetCalibration(ADC1);     //重置校准寄存器，将CR2_RSTCAL置1
    while (ADC_GetResetCalibrationStatus(ADC1) == SET);     //重复检测校准寄存器标志位，直至校准寄存器已初始化(CR2_RSTCAL置0)
    ADC_StartCalibration(ADC1);     //开始校准，将CR2_CAL置1
    while (ADC_GetCalibrationStatus(ADC1));     //重复检测校准寄存器标志位，直至校准完成(CR2_CAL置0)
    
    /* 软件触发 */
     ADC_SoftwareStartConvCmd(ADC1, ENABLE);     
}

/**
  * @brief  ADC结果获取
  * @param  无
  * @retval ADC将模拟电压转换成的值(将模拟电压转化为代表比例关系的数字量)
  */
uint16_t AD_GetVaule(void)
{
    return ADC_GetConversionValue(ADC1);        //返回ADC得出值
}
