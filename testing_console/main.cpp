#include <QCoreApplication>
#include "spi/spi.h"
#include "serial_lcd/seriallcd.h"

void testing_ili9341()
{
    // dout="gpio66/value"
    // cs="gpio69/value"
    // clk="gpio70/value"
    SpiMaster *spi = new BitBangSPI(70,66,-1);
    SpiCmdData *dev = new SpiCmdData();
    int id = spi->addDevice(69, dev);
    Ili9341 * lcd = new Ili9341(dev);
    lcd->changeToRGBMode();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
