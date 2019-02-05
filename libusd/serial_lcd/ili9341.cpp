#include "seriallcd.h"

Ili9341::Ili9341()
{

}

Ili9341::Ili9341(SpiCmdData *spi)
{
    this->spi = spi;
}

void Ili9341::changeToRGBMode()
{
    if(!this->spi)
        return;
    // cmd 40 # 0x28  display off
    // cmd 246 # 0xf6
    // data 1
    // data 0
    // data 6
    // cmd 41  # 0x29 display on
    spi->writeCommand(0x28);
    uint8_t p[] = {1,0,6};
    spi->writeCommand(0xf6,p,3);
    spi->writeCommand(0x29);
}
