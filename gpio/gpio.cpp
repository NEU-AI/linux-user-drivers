#include "gpio.h"
#include "gpioclass.h"
#include "mmio.h"

Gpio::Gpio()
{
}

/**
 * @brief Gpio::getGpio
 * @param id
 * @param method
 * @return
 */
Gpio* Gpio::getGpio(unsigned id, enum access_method method)
{
    Gpio* ret = NULL;
    switch (method) {
    case SYS_CLASS:
        ret = GPIOClass::getGpio(id);
        break;
    case MMAP:
        ret = GpioMMapIMX6::getGpio(id);
        break;
    default:
        break;
    }
    return ret;
}
