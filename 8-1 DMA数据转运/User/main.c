/**
  ******************************************************************************
  * @file    main.c
  * @author  RAIN
  * @version V1.0
  * @date    2026/4/5
  * @brief   按键点灯
  ******************************************************************************
  * @attention
  *
  * 无。
  ******************************************************************************
  */
  
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MYDMA.h"

uint8_t DataA[] = {0x01, 0x02, 0x03, 0x04};
uint8_t DataB[] = {0, 0 ,0 ,0}; 

//外设寄存器的地址是固定的
//32位的系统地址都是32位的
int main(void)
{
    /* 外设初始化 */
    OLED_Init();
    MYDMA_Init((uint32_t)DataA, (uint32_t)DataB, 4);
    
    /* 显示初始值 */
    OLED_ShowString(1, 1, "DataA");
    OLED_ShowString(3, 1, "DataB");
    
    OLED_ShowHexNum(1, 8, (uint32_t)DataA, 8); 
    OLED_ShowHexNum(3, 8, (uint32_t)DataB, 8);
    
    for (uint8_t i = 0; i < 4; i++)
    {
        OLED_ShowHexNum(2, 1 + 3 * i, DataA[i], 2);
        OLED_ShowHexNum(4, 1 + 3 * i, DataB[i], 2);
    }

	while (1)
	{
        /* 转运前DataA自增并显示 */
        DataA[0]++;
        DataA[1]++;
        DataA[2]++;
        DataA[3]++;        
        
        for (uint8_t i = 0; i < 4; i++)
        {
            OLED_ShowHexNum(2, 1 + 3 * i, DataA[i], 2);
            OLED_ShowHexNum(4, 1 + 3 * i, DataB[i], 2);
        }
        
        Delay_ms(1000);
        
        /* 开始转运 */
        MYDMA_Transfer();
        
        /* 显示转运后结果 */
        for (uint8_t i = 0; i < 4; i++)
        {
            OLED_ShowHexNum(2, 1 + 3 * i, DataA[i], 2);
            OLED_ShowHexNum(4, 1 + 3 * i, DataB[i], 2);
        }
        
        Delay_ms(1000);
    }
}
