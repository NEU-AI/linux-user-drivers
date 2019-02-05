#ifndef GPIO_H
#define GPIO_H



class Gpio
{
protected:
    Gpio();
public:
    enum access_method {SYS_CLASS, MMAP};
    enum direction {INPUT, OUTPUT};
    static Gpio* getGpio(unsigned id, enum access_method method = SYS_CLASS);
    virtual int setDirection(enum direction dir) = 0; // Set GPIO Direction, I/O
    virtual int setValue(int value) = 0; // Set GPIO Value (output pins)
    virtual int getValue() = 0; // Get GPIO Value (input/ output pins)
};



#endif // GPIO_H
