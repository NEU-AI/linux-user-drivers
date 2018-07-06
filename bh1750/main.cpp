#include "bh1750.h"
#include <unistd.h>
int main(void)
{
    BH1750 light;
    light.start();
    while(1)
    {
        sleep(1);
    }
}
