/* test_struct.c -- 对结构体的测试 */
#include <stdio.h>
 
typedef struct
{
    char x;
    int y;
    float z;
} StructName_t;

int main(void)
{
/**
 * 结构体变量名不会自动转换为地址。要获得结构体的首地址，必须使用 & 运算符；
 * 变量名不能使用->，加上&也不行，c->y，&c->y都是错误的；
 * 指针名可以使用->，例如p->x，但p.y错误；
 * &p->y 取的是成员 y 的地址&y,故&c->y错误；
 * ->的优先级高于强制转换和&。
 **/
//  struct {char x; int y; float z;} c;
    StructName_t c;         //结构体变量
    StructName_t *p = &c;   //指向StructName_t首位的指针

//  c.x = 'a';
    p->x = 'a'; 
    c.y = 12;
    c.z = 1.2;

    printf("c.x = %c\n", c.x);
    printf("c.y = %d\n", c.y);
    printf("c.z = %.2f\n", c.z);
 
    return 0;
}