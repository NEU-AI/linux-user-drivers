#include "spi.h"

BitBangSPI::BitBangSPI(int clk, int mosi, int miso)
{
    //todo: 构造以下对象有可能失败
    this->clk = Gpio::getGpio(clk);
    this->clk->setDirection(Gpio::OUTPUT);
    this->mosi = Gpio::getGpio(mosi);
    this->mosi->setDirection(Gpio::OUTPUT);
    this->miso = Gpio::getGpio(miso);
    this->miso->setDirection(Gpio::OUTPUT);
}

int BitBangSPI::addDevice(int cs, SpiDevice *dev)
{
    struct device *d = new struct device;
    d->cs = Gpio::getGpio(cs);
    d->cs->setDirection(Gpio::OUTPUT);
    d->dev = dev;
    dev->setMaster(this);
    devices.append(d);
    return devices.length() - 1;
}

int BitBangSPI::transfer(SpiList* buffer)
{
    return 0;
}
