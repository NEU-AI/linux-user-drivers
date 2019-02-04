#ifndef GPIO_H
#define GPIO_H

#include "gpio_global.h"

class GPIOSHARED_EXPORT Gpio
{
protected:
    Gpio();
public:
    static Gpio* getGpio(unsigned id, char method='s');
    virtual int setDirection(char dir) = 0; // Set GPIO Direction, I/O
    virtual int setValue(int value) = 0; // Set GPIO Value (output pins)
    virtual int getValue() = 0; // Get GPIO Value (input/ output pins)
};



#endif // GPIO_H
