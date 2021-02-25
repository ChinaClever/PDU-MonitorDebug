#include "baseobject.h"


BaseObject::BaseObject()
{
    mModbus = nullptr;
    mPacket = sDataPacket::bulid();
    mItem = Cfg::bulid()->item;
    mPro = mPacket->getPro();
    mDev = mPacket->getDev();
    mData = &(mDev->data);
    mCfg = &(mDev->cfg);
    mDt = &(mDev->dt);
}

BaseThread::BaseThread(QObject *parent) : QThread(parent)
{
    isRun = false;
    QTimer::singleShot(850,this,SLOT(initFunSlot()));
}

BaseThread::~BaseThread()
{
    isRun = false;
    wait();
}

void BaseThread::initFunSlot()
{
    mModbus = Rtu_Modbus::bulid(this)->get();
    if(!mModbus) QTimer::singleShot(350,this,SLOT(initFunSlot()));
}

bool BaseThread::updatePro(const QString &str, bool pass, int sec)
{
    mPro->time = QTime::currentTime().toString("hh:mm:ss");
    mPro->pass << pass;
    mPro->status << str;
    if(pass) pass = delay(sec);
    else mPro->result = Test_Fail;

    return pass;
}

bool BaseThread::mdelay(int s)
{
    bool ret = true;
    for(int i=0; i<s; ++i) {
        if((mPro->step < Test_Over)  || (mPro->step > Test_End)){
            QThread::msleep(100);
        } else {
            ret = false;
            break;
        }
    }

    return ret;
}
