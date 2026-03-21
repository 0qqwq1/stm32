void SystemInit(void){}

int main(void)
{
    unsigned int * led_clock  = (unsigned int*)(0x40021000 + 0x18);
    unsigned int * led_config = (unsigned int*)(0x40010800 + 0x00);
    unsigned int * led_open   = (unsigned int*)(0x40010800 + 0x0c);
    
    *led_clock  |= 0x4;
    *led_open   |= 0xE;
    *led_config |= 0x3330;
    *led_open   &= ~0xE;
    
    while (1);
}
