void SystemInit(void)
{
}

int main(void)
{
    unsigned int * led_rcc    = (unsigned int*)(0x40021000 + 0x18); //灯具时钟开关地址
    unsigned int * led_config = (unsigned int*)(0x40010800 + 0x00); //灯具配置端口的开关地址
    unsigned int * led_output = (unsigned int*)(0x40010800 + 0x0c); //灯具输出状态的开关地址

    /*
    位运算常用技巧
    |=  通常用来置1
    &=~ 通常用来复0
    */
    *led_rcc    |= 0x4;     //开启端口时钟
    *led_output |= 0xE;      //让端口引脚输出1，使得灯灭,调整实际默认状态
    *led_config |= 0x3330;   //配置端口引脚的模式
    //*led_output |= 0xE;      //让端口引脚输出1，使得灯灭
    *led_output &= ~0x2;     //让端口引脚输出0，使得灯亮
    //0xE与0xE取反值相与，结果为0
    
    while (1);
}
