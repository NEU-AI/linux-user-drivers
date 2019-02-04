#include "gpio.h"
#include "gpioclass.h"

Gpio::Gpio()
{
}

/**
 * @brief Gpio::getGpio
 * @param id
 * @param method 's'=/sys/class/gpio 'm'=memory map io
 * @return
 */
Gpio* Gpio::getGpio(unsigned id, char method)
{
    Gpio* ret = NULL;
    switch (method) {
    case 's':
        ret = GPIOClass::getGpio(id);
        break;
    case 'm':
        break;
    default:
        break;
    }
    return ret;
}
