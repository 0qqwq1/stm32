#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData = 0;

int main(void)
{
    OLED_Init();
    Serial_Init();
    
    OLED_ShowString(1, 1, "RxData:");
    
	while (1)
	{
          /* 查询RXNE方式 */
//        if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
//        {
//            RxData = USART_ReceiveData(USART1);
//            OLED_ShowHexNum(1, 1, RxData, 2);
//        }
        
        /* RXNE中断方式 */
        if (Serial_GetRxFlag())
        {
            RxData = Serial_GetRxData();
            Serial_SendByte(RxData);
            OLED_ShowHexNum(1, 8, RxData, 2);
        }
    }
}
