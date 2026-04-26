#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

int main(void)
{
    OLED_Init();
    Serial_Init();
    
    Serial_SendByte('A');
    
    uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
    Serial_SendArray(MyArray, 4);
             
    Serial_SendString("\r\nNum1=");                
    //这里\r\n得一起用，作用是把光标移到下一行行首
    //\r是回车，作用是回到行首
    //\n是换行，把光标移到下一行的位置
    
    Serial_SendNumber(111, 3);

    /* printf重定向方法 */
    printf("\r\nNum2=%d", 222);
    
    /* sprintf打印到字符串方法 */
    char String[100];
    sprintf(String, "\r\nNum3=%d", 333);
    Serial_SendString(String);
    
    /* 封装办法 */
    Serial_Printf("\r\nNum4=%d", 444);
    Serial_Printf("\r\n");
    
	while (1)
	{
        
    }
}
