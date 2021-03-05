#ifndef DEV_SICTRL_H
#define DEV_SICTRL_H

#include "dev_sirtu.h"

class Dev_SiCtrl : public Dev_Object
{
    Q_OBJECT
    explicit Dev_SiCtrl(QObject *parent = nullptr);
public:
    static Dev_SiCtrl *bulid(QObject *parent = nullptr);

    bool setDev();
    bool unClock();
    bool factorySet();

    bool setCurTh(int i);
    bool setVolTh(int i);

    bool setTem();
    bool setHum();

protected:
    bool writeReg(ushort reg, int i, sDataUnit &it, sUnitCfg &unit, int r=1);
    bool sentRtuCmd(ushort reg, ushort value);
};

#endif // DEV_SICTRL_H
