//#include <QCoreApplication>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "dht_read.h"
#include "gpioclass.h"
int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);
//    DHT dht(77, DHT22);

//    printf("hello\n");
//    GPIOClass* gpio4 = new GPIOClass("80"); //create new GPIO object to be attached to  GPIO4
//    GPIOClass* gpio17 = new GPIOClass("162"); //create new GPIO object to be attached to  GPIO17

//    gpio4->export_gpio(); //export GPIO4
//    gpio17->export_gpio(); //export GPIO17

//    cout << " GPIO pins exported" << endl;

//    gpio17->setdir_gpio("in"); //GPIO4 set to output
//    gpio4->setdir_gpio("out"); // GPIO17 set to input

//    cout << " Set GPIO pin directions" << endl;
    //    for(int i=0;;i++)
    //    {
    //        usleep(500000);  // wait for 0.5 seconds
    //        if(i%2)
    //            gpio4->setval_gpio("1"); // turn LED ON
    //        else
    //            gpio4->setval_gpio("0"); // turn LED Off

    //    }
    //    return a.exec();

    float t, h;
    if(mmio_dht_read(22, 32*5+2, &t, &h)==0){
        cout << "temperature" << t
             << " humidity" << h << endl;
    }

}
