#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

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
  * @brief  串口发送一个字节
  * @param  Byte：待输出的值
        取值范围为00~FF
  * @retval 无
  */
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART1, Byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);       //等待数据转运完成，防止数据覆盖
    //当USART_DR写入TSR时，TXE自动复位,表示正在转运，硬件置0无法被软件覆盖
}

/**
  * @brief  串口发送一个数组
  * @param  Array：待输出的数组
  * @param  Length：数组长度
  * @retval 无
  */
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
    uint16_t i;
    
    for (i = 0; i < Length; i++)
    {
        USART_SendData(USART1, Array[i]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

/**
  * @brief  串口发送一个字符串
  * @param  String：待输出的字符串
  * @retval 无
  */
void Serial_SendString(char *String)
{
    uint8_t i = 0;
    
    while (String[i] != '\0')
    {
        Serial_SendByte(String[i]);
        i++;
    }
}

/**
  * @brief  幂函数
  * @param  X：底数
  * @param  Y：指数
  * @retval 返回的结果
  */
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y--)
    {
        Result *= X;
    }
    return Result;
}

/**
  * @brief  串口发送一个十进制数字
  * @param  Number：待处理的十进制数字
  * @param  Length：数字位数
  * @retval 无
  */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + 0x30);
        //从高位到低位将要求的位除至个位，在对10求余
    }
}

/**
  * @brief  printf重定向到USART1
  * @param  无
  * @retval 无
  */
int fputc(int ch, FILE *f)
{
    Serial_SendByte(ch);
    return ch;
}

/**
  * @brief  sprintf方式封装
  * @param  无
  * @retval 无
  */
void Serial_Printf(char *format, ...)
{
    char String[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    Serial_SendString(String);
}
