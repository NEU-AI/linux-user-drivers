// Copyright (c) 2014 Adafruit Industries
// Author: Tony DiCola

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// Simple fast memory-mapped GPIO library for the Beaglebone Black.
// Allows reading and writing GPIO at very high speeds, up to ~2.6mhz!

/*
  // Example usage:

  #include <stdio.h>
  #include "bbb_mmio.h"

  int main(int argc, char* argv[]) {
    // Get GPIO pin.
    // See the giant table of of pins in the system reference manual for details
    // on the base and number for a given GPIO:
    //  https://github.com/CircuitCo/BeagleBone-Black/blob/master/BBB_SRM.pdf?raw=true
    // Section 7 Connectors, table 12 shows P8_11 maps to GPIO1_13, so 1 is the
    // gpio base and 13 is the gpio number.
    gpio_t p8_11;
    if (bbb_mmio_get_gpio(1, 13, &p8_11) < 0) {
      printf("Couldn't get requested GPIO pin!\n");
      return 1;
    }
    // Set pin as output.
    bbb_mmio_set_output(p8_11);
    // Toggle the pin high and low as fast as possible.
    // This generates a signal at about 2.6mhz in my tests.
    // Each pulse high/low is only about 200 nanoseconds long!
    while (1) {
      bbb_mmio_set_high(p8_11);
      bbb_mmio_set_low(p8_11);
    }
    return 0;
  }

*/

#ifndef BBB_MMIO_H
#define BBB_MMIO_H
#include <stdint.h>
#include "gpio.h"
#define MMIO_SUCCESS 0
#define MMIO_ERROR_ARGUMENT -1
#define MMIO_ERROR_DEVMEM -2
#define MMIO_ERROR_MMAP -3

#define MMIO_OE_ADDR 0x134
#define MMIO_GPIO_DATAOUT 0x13C
#define MMIO_GPIO_DATAIN 0x138
#define MMIO_GPIO_CLEARDATAOUT 0x190
#define MMIO_GPIO_SETDATAOUT 0x194

#define GPIO_LENGTH 4096
#define GPIO1_ADDR 0x4804C000
#define GPIO2_ADDR 0x481AC000
#define GPIO3_ADDR 0x481AF000
#define GPIO6_BASE 0x20B0000

class GpioMMapIMX6: public Gpio
{
private:
    // Define struct to represent a GPIO pin
    //    based on its base memory address and number.
    volatile uint32_t* base; //一组的寄存器基地址
    unsigned char group;
    unsigned char number; //一组IO里面的位号
    int fd_mmap;

    // Store mapping of GPIO base number to GPIO address.
    const uint32_t gpio_addresses[7] = { GPIO1_ADDR,
                                          GPIO2_ADDR,
                                          GPIO3_ADDR,
                                          0,
                                          0,
                                          GPIO6_BASE,
                                          0
                                        };

    // Cache memory-mapped GPIO addresses.
    static uint32_t* gpio_base[7];
    static bool base_zeroed;
    GpioMMapIMX6();
    GpioMMapIMX6(unsigned id);

public:
    static GpioMMapIMX6* getGpio(unsigned id);
    int setDirection(enum direction dir){
        if(dir == Gpio::OUTPUT)
            base[1] |= (1 << number);
        else
            base[1] &= (0xFFFFFFFF ^ (1 << number));
        return 0;
    }

    int setValue(int value){
        if(value)
            base[0] |= 1 << number;
        else
            base[0] &= ~(1 << number);
        return 0;
    }

    int getValue() {
        return base[0] & (1 << number);
    }
};
#endif
