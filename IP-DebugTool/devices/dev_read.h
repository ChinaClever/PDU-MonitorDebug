#ifndef DEV_READ_H
#define DEV_READ_H

#include "dev_ipcfg.h"

class Dev_Read : public BaseThread
{
    Q_OBJECT
    explicit Dev_Read(QObject *parent = nullptr);
public:
    static Dev_Read *bulid(QObject *parent = nullptr);
    bool readPduData();
};

#endif // DEV_READ_H
