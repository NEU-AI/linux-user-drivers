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
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "mmio.h"
bool GpioMMapIMX6::base_zeroed=false;
uint32_t* GpioMMapIMX6::gpio_base[7]={NULL};
GpioMMapIMX6::GpioMMapIMX6(unsigned id)
{
    if(!base_zeroed){
        memset(gpio_base,0,sizeof(gpio_base));
        base_zeroed = true;
    }
    this->group = id / 32;
    this->number = id % 32;

    // Validate input parameters.
    if (this->group > 7) {
        return;//MMIO_ERROR_ARGUMENT;
    }
    if (number > 31) {
        return;//MMIO_ERROR_ARGUMENT;
    }
    // Map GPIO memory if its hasn't been mapped already.
    if (gpio_base[group] == NULL) {
        int fd = open("/dev/mem", O_RDWR | O_SYNC);
        if (fd == -1) {
            // Error opening /dev/mem.  Probably not running as root.
            return;//MMIO_ERROR_DEVMEM;
        }
        fd_mmap = fd;
        // Map GPIO memory to location in process space.
        gpio_base[group] = (uint32_t*)mmap(NULL, GPIO_LENGTH,
                 PROT_READ | PROT_WRITE, MAP_SHARED,
                 fd, gpio_addresses[group]);
        if (gpio_base[group] == MAP_FAILED) {
            // Don't save the result if the memory mapping failed.
            gpio_base[group] = NULL;
            return;//MMIO_ERROR_MMAP;
        }
    }
    // Initialize and set GPIO fields.
    this->base = gpio_base[group];
}

GpioMMapIMX6 *GpioMMapIMX6::getGpio(unsigned id)
{
    return new GpioMMapIMX6(id);
}




