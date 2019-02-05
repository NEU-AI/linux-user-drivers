#include "bh1750.h"

BH1750::BH1750()
{

}
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "../gpio/gpio.h"

void delay_IIC()
{
    usleep(10);
}

Gpio *sda, *scl;

void iic_byte_write(uint8_t data)
{//向IIC总线写入一个字节的数据函数
    sda->setDirection(Gpio::OUTPUT);
//    printf("w");
    for(int i=0;i<8;i++)//有8位数据
    {
        sda->setValue(data&0x80);//写最高位的数据
        delay_IIC();
        scl->setValue(1); //拉高时钟线，将数写入到设备中。
        delay_IIC();
        scl->setValue(0);//拉低时钟线，允许改变数据线的状态
        delay_IIC();
        data=data<<1;//数据左移一位，把次高位放在最高位,为写入次高位做准备
    }
    usleep(50);
//    printf("\n");
}

uint8_t iic_byte_read()
{
    //从IIC总线读取一个字节的数据函数
    unsigned char i;
    unsigned char Data;       //定义一个缓冲寄存器。
    sda->setDirection(Gpio::INPUT);
//    printf("r");
    for(i=0;i<8;i++)//有8位数据
    {
        scl->setValue(1);//拉高时钟线，为读取下一位数据做准备。
        delay_IIC();
        Data=Data<<1;//将缓冲字节的数据左移一位，准备读取数据。
        delay_IIC();
        if(sda->getValue()){ //如果数据线为高平电平。
            Data=Data|0x1;//则给缓冲字节的最低位写1。
//            printf("1");
        }
        scl->setValue(0);//拉低时钟线，为读取下一位数据做准备。
        delay_IIC();
    }
//    printf("\n");
    return Data;//返回读取的一个字节数据。
}

void iic_start()  //iic起始信号
{
    sda->setDirection(Gpio::OUTPUT);
    sda->setValue(1);//拉高数据线
    scl->setValue(1);//拉高时钟线
    delay_IIC();
    sda->setValue(0);//在时钟线为高电平时，拉低数据线，产生起始信号。
    delay_IIC();
    scl->setValue(0);//拉低时钟线
//    printf("start\n");
}

uint8_t iic_wait_ack()       //等待从机应答
{
    uint8_t ack=0;//定义一个位变量，来暂存应答状态。
    sda->setDirection(Gpio::INPUT);
//    IIC_SDA=1;//释放数据总线，准备接收应答信号。
    delay_IIC();
    scl->setValue(1);//拉高时钟线。
    delay_IIC();
    if(sda->getValue()){
        ack=1;//读取应答信号的状态。
//        printf("no-ack\n");
    }
    delay_IIC();
    scl->setValue(0);//拉低时钟线。
    delay_IIC();
    return ack;//返回应答信号的状态，0表示应答，1表示非应答。
}

uint8_t iic_ack_slave(int ack)       //应答从机
{
    sda->setDirection(Gpio::OUTPUT);
//    IIC_SDA=1;//释放数据总线，准备接收应答信号。
    if(ack){
        sda->setValue(0);
//        printf("read ack\n");
    }else{
        sda->setValue(1);
//        printf("read !ack\n");
    }
    delay_IIC();
    scl->setValue(1);//拉高时钟线。
    delay_IIC();
    scl->setValue(0);//拉低时钟线。
    delay_IIC();
    return ack;//返回应答信号的状态，0表示应答，1表示非应答。
}

void iic_stop() //iic停止信号
{
    sda->setDirection(Gpio::OUTPUT);
    sda->setValue(0);//拉低数据线
    delay_IIC();
    scl->setValue(1);//拉高时钟线。
    delay_IIC();
    sda->setValue(1);//时钟时线为高电平时，拉高数据线，产生停止信号。
    delay_IIC();
//    printf("stop\n");
}

void iic_init()
{
    sda = Gpio::getGpio(6);
    scl = Gpio::getGpio(5);
    scl->setDirection(Gpio::OUTPUT);
}



/*************************************************************/

#define BHAddWrite     0x46      //从机地址+最后写方向位
#define BHAddRead      0x47      //从机地址+最后读方向位
#define BHPowDown      0x00      //关闭模块
#define BHPowOn        0x01      //打开模块等待测量指令
#define BHReset        0x07      //重置数据寄存器值在PowerOn模式下有效
#define BHModeH1       0x10      //高分辨率 单位1lx 测量时间120ms
#define BHModeH2       0x11      //高分辨率模式2 单位0.5lx 测量时间120ms
#define BHModeL        0x13      //低分辨率 单位4lx 测量时间16ms
#define BHSigModeH     0x20      //一次高分辨率 测量 测量后模块转到 PowerDown模式
#define BHSigModeH2    0x21      //同上类似
#define BHSigModeL     0x23      // 上类似
/*************************************************************/
void bh_data_send(uint8_t command)
{
    do{
        iic_start();                      //iic起始信号
        iic_byte_write(BHAddWrite);       //发送器件地址
    }while(iic_wait_ack());           //等待从机应答
    iic_byte_write(command);          //发送指令
    iic_wait_ack();                   //等待从机应答
    iic_stop();                       //iic停止信号
}

uint16_t bh_data_read(void)
{
    uint16_t buf;
    iic_start();                       //iic起始信号
    iic_byte_write(BHAddRead);         //发送器件地址+读标志位
    iic_wait_ack();                     //等待从机应答
    buf=iic_byte_read();
    iic_ack_slave(1);
    buf=buf<<8;                //读取并保存高八位数据
    buf=iic_byte_read();      //读取并保存第八位数据
    iic_ack_slave(0);
    iic_stop();                        //发送停止信号
    return buf;
}


void BH1750::run()
{
    float datalx;
    iic_init();

    bh_data_send(BHPowOn);    //发送启动命令
    bh_data_send(BHReset);    //清除寄存器内容
    bh_data_send(BHModeH1);   //设置高精度模式

    msleep(180);            //设置完成后要有一段延迟，手册上说最大180ms就可以了

    while(1)
    {
        datalx = bh_data_read()/1.2; //根据手册读取的数据除以1.2就得到单位位lx的光强度检测值。
        printf ("light %f\n",datalx);
        msleep(777);
    }
}
