#ifndef SPI_H
#define SPI_H
#include <QVector>
#include <QLinkedList>
#include "../gpio/gpio.h"

typedef struct
{
    uint8_t *tx_buf, *rx_buf;
    unsigned bits_length;
}SpiTransfer;
typedef QLinkedList<SpiTransfer*> SpiList;
class SpiDevice;

class SpiMaster
{
private:
//    QVector<SpiDevice*> devices;
protected:
    SpiMaster();
public:
//    unsigned addDevice(SpiDevice* dev) = 0;
    virtual int addDevice(int cs, SpiDevice* dev)=0;
    void removeDevice(int cs);
    virtual int transfer(SpiList* buffer) = 0;
};

class BitBangSPI : public SpiMaster
{
private:
    struct device
    {
        Gpio * cs;
        SpiDevice * dev;
    };
    QVector<struct device*> devices;
    BitBangSPI();
    Gpio *clk, *mosi, *miso;
public:
    BitBangSPI(int clk, int mosi, int miso);
    int addDevice(int cs, SpiDevice* dev);
//    void removeDevice(int cs);
    int transfer(SpiList* buffer);
};

class SpiDevice
{
protected:
    SpiMaster * master = NULL;
//    unsigned id;
public:
//    SpiDevice();
////    virtual void selectChip() = 0;
//    void write();
//    void read();
//    int transfer();
    void setMaster(SpiMaster *value);
};

class SpiCmdData : public SpiDevice
{
private:
    Gpio * cmd_dat_pin = NULL;
    uint8_t* to9bits(uint8_t add_bit, const uint8_t* from, unsigned length);
public:
    SpiCmdData();
    SpiCmdData(int cmd_dat);
    void writeCommand(uint8_t command, const uint8_t* buf=NULL, unsigned length=0);
    void writeData(const uint8_t* buf, unsigned length);
};
#endif // SPI_H
