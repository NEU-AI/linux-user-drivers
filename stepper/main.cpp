#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "gpio.h"

Gpio *io[4];
void stop()
{
    for(int i=0;i<4;i++){
        io[i]->setValue(0);
    }
}

void output(uint8_t value)
{
    for(int i=0;i<4;i++){
        io[i]->setValue(value & 1);
        value = value >> 1;
    }
    usleep(3e3);
    stop();
    usleep(2e3);
}
/******************************************
*  标题:  步进电机试验五（正转一圈 反转一圈）	  *
*    通过本例程了解步进马达使用及驱动程序编写	  *
*    单双八拍工作方式：                      *
*    A-AB-B-BC-C-CD-D-DA                  *
*******************************************/

//unsigned char FFW[8]={0xfe,0xfc,0xfd,0xf9,0xfb,0xf3,0xf7,0xf6}; //反转
uint8_t FFW[8]={0x1,0x3,0x2,0x6,0x4,0xc,0x8,0x9};
//unsigned char FFZ[8]={0xf6,0xf7,0xf3,0xfb,0xf9,0xfd,0xfc,0xfe}; //正转
uint8_t FFZ[8]={0x9,0x8,0xc,0x4,0x6,0x2,0x3,0x1};
unsigned int  K = 0;

/**********************
*     步进电机驱动	  *
***********************/
void motor_ffw(int dir)
{
//    unsigned char i;
//    unsigned int  j;
    unsigned char *f = (dir > 0?FFW:FFZ);
    for (int j=0; j<64*8; j++)         //转1*n圈
    {
        for (K=0; K<8; K++)       //一个周期转??度
        {
            output(f[K]);  //取数据
//            usleep(5000);      //调节转速
        }
    }
}

int main()
{
    unsigned io_number[] = {91,90,9,162};
    for(int i=0;i<4;i++){
        io[i] = Gpio::getGpio(io_number[i]);
        io[i]->setDirection('o');
    }

    stop();

//    GPIOClass pwm("83");
//    pwm.export_gpio();
//    pwm.setdir_gpio("out");
//    for(int i=0;i<1e4;i++){
//        pwm.setval_gpio("1");
//        pwm.setval_gpio("0");
//    }
//    for(int i=0;i<1000;i++)
//    {
        motor_ffw(1);
//        motor_ffw(-1);
//    }
//    output(0xf);
    return 0;
}

