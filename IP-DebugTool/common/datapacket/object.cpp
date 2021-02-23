#include "object.h"

Object::Object(QObject *parent) : QThread(parent)
{
    QTimer::singleShot(850,this,SLOT(initFunSlot()));
    mPacket = sDataPacket::bulid();
    mItem = Cfg::bulid()->item;
    mPro = mPacket->getPro();
    mDev = mPacket->getDev();
    mCfg = &(mDev->cfg);
    mDt = &(mDev->dt);
}

void Object::initFunSlot()
{
    mModbus = Rtu_Modbus::bulid(this)->get();
}

bool Object::updatePro(const QString &str, bool pass, int sec)
{
    mPro->time = QTime::currentTime().toString("hh:mm:ss");
    mPro->pass = pass;
    mPro->status << str;
    if(pass) pass = delay(sec);
    else mPro->result = Test_Fail;

    return pass;
}

bool Object::delay(int s)
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
