#include "spi.h"


SpiMaster::SpiMaster()
{
}

uint8_t *SpiCmdData::to9bits(uint8_t add_bit, const uint8_t *from, unsigned length)
{
    unsigned add_length = length / 8 + ((length%8==0)?0:1);
    uint8_t * to = new uint8_t[length + add_length];
    memset(to,0,length+add_length);
    uint8_t * ret = to;
    for(unsigned i=0;i<length;i++)
    {
        int shift = i % 8;
        if(add_bit)
            *to |= 1 << (7-shift);
        if(shift == 7)
        {
            to++;
            *to = *from;
            to++;
            from++;
        }
        else
        {
            *to |= *from >> (shift+1);
            to++;
            *to |= *from << (7-shift);
            from++;
        }
    }
    return ret;
}

SpiCmdData::SpiCmdData()
{

}

SpiCmdData::SpiCmdData(int cmd_dat)
{

}

void SpiCmdData::writeCommand(uint8_t command, const uint8_t* buf, unsigned length)
{
    if(this->cmd_dat_pin)
    {

    }
    else // 9bits
    {
        SpiList list;

        SpiTransfer *cmd = new SpiTransfer;
        cmd->tx_buf = to9bits(0, &command, 1);
        cmd->rx_buf = NULL;
        cmd->bits_length = 9;
        list.append(cmd);

        SpiTransfer *parameters = new SpiTransfer;
        parameters->tx_buf = to9bits(1, buf, length);
        parameters->rx_buf = NULL;
        cmd->bits_length = 9*length;
        list.append(parameters);

        this->master->transfer(&list);

        delete cmd->tx_buf;
        delete parameters->tx_buf;
        delete cmd;
        delete parameters;
    }
}

void SpiCmdData::writeData(const uint8_t *buf, unsigned length)
{

}

void SpiDevice::setMaster(SpiMaster *value)
{
    master = value;
}
