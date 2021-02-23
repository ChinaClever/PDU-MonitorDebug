#ifndef OBJECTTHREAD_H
#define OBJECTTHREAD_H

#include "datapacket.h"
#include "rtu_modbus.h"

class Object : public QThread
{
    Q_OBJECT
public:
    explicit Object(QObject *parent = nullptr);

    void init() {mPacket->init();}
    bool updatePro(const QString &str, bool pass=true, int sec=1);
    bool delay(int s=1);

protected slots:
    virtual void initFunSlot();

protected:
    sDevType *mDt;
    sTypeCfg *mCfg;
    sDevData *mDev;
    RtuRw *mModbus;
    sCfgItem *mItem;
    sProgress *mPro;
    sDataPacket *mPacket;
};

#endif // OBJECTTHREAD_H
