#include <stdio.h>
#define ON 1
#define OFF 0
int main(void)
{
    /*
    int led_config; //存储灯的模式等配置的容器名变量
    int led_enable; //生效配置的容器变量

    int led_1;
    int led_2;

    led_config = 6; //假设配置6号配置作为功能配置使用
    led_enable = 1; //生效配置

    led_1 = ON;
    led_2 = OFF;
    led_1 = OFF;
    */
    
    //以上变量都是自动存储
    //实际上内部寄存器/开关是有固定的地址，要以明确的地址进行编程赋值

    //利用指针访问明确地址
    //定义一些指针变量，指向对应地址

    int * led_config = (int*)0x100; //把0x100当作内存地址使用
    int * led_enable = (int*)0x200;

    int * led_1 = (int*)0x300;
    int * led_2 = (int*)0x400;
 
    //用*对地址进行读写

    *led_config = 6;
    *led_enable = 1;

    *led_1 = ON;
    *led_2 = OFF;
    *led_1 = OFF;

    //如何控制高低电平

    int * PA  = (int*)(0x40010800+0x00); // 因为int类型占用4字节，所以偏移下一位是0x04
    *PA = 1;

    return 0;
}