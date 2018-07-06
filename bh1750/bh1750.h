#ifndef BH1750_H
#define BH1750_H
#include <QThread>

class BH1750: public QThread
{
public:
    BH1750();
    void run();
};

#endif // BH1750_H
