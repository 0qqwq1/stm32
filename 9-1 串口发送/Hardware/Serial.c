#include "stm32f10x.h"                  // Device header

/**
  * @brief  串口初始化
  * @param  无
  * @retval 无
  */
void Serial_Init(void)
{
    /* 开启时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* GPIO初始化 */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //选择复用推挽模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //PA9是USART1_TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //选择上拉输入模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;          //PA10是USART1_RX
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* USART初始化 */
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;                                          //配置波特率为9600Hz
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;     //不启用硬件流
    USART_InitStructure.USART_Mode = USART_Mode_Tx;                                     //配置输出模式(如果两个模式都使用就用|隔开)
    USART_InitStructure.USART_Parity = USART_Parity_No;                                 //不启用校验位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                              //配置停止位为1位
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                         //配置数据帧为8位
    USART_Init(USART1, &USART_InitStructure);
    
    //如果要输入需要以RXNE为标志位配置中断和NVIC
    
    /* USART初始化 */
    USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  USART1输出
  * @param  Byte：将要输出的值
        取值范围为00~FF
  * @retval 无
  */
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART1, Byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);       //等待数据转运完成，防止数据覆盖
    //当USART_DR写入TSR时，TXE自动复位,表示正在转运，硬件置0无法被软件覆盖
}
