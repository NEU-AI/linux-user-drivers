#ifndef SERIALLCD_H
#define SERIALLCD_H
#include "../spi/spi.h"

typedef struct {
    int x;
    int y;
    int w;
    int h;
}Rect;

class SerialLCD
{

public:
    SerialLCD();
//    uint8_t * readRect(Rect rect) = 0;
//    void writeRect(Rect rect, uint8_t * buffer) = 0;
};

class Ili9341 : public SerialLCD
{
private:
    SpiCmdData* spi;
    Ili9341();
public:
    Ili9341(SpiCmdData* spi);
    void changeToRGBMode();
    void changeToSerialMode();
};

class VirtualLCD : public SerialLCD
{
public:
    VirtualLCD();
};


#endif // SERIALLCD_H
