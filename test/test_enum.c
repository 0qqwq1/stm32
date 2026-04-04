/* test_enum.c -- 对枚举的测试 */
#include <stdio.h>

//类似宏定义的集合
//如果赋值按照顺序累加，那后面的赋值可以省略;
//这种自动赋值类似数组，也是从已有的值往下累加;
//a是1，b就是2；e是8,f就是9;
typedef enum
{
    Monday = 1,
    Tuesday,
    Wednesday,
} WEEK_t;

int main(void)
{
    WEEK_t week;

    //引用时只能写在枚举中被定义的变量
    week = Monday;      // week = 1
    week = (WEEK_t)1;   // 不能直接写week = 1,但可以进行强制转换；

    return 0;
}