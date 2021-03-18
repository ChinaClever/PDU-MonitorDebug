/*
 *
 *  Created on: 2020年10月1日
 *      Author: Lzy
 */
#include "yc_standsource.h"

YC_StandSource::YC_StandSource(QObject *parent) : BaseThread(parent)
{
    mSerial = nullptr;
}

void YC_StandSource::initFunSlot()
{
    mSerial = mItem->source;
    if(!mSerial) QTimer::singleShot(350,this,SLOT(initFunSlot()));
}

bool YC_StandSource::setBaudRate(qint32 baudRate)
{
    bool ret = false;
    if(mSerial) {
        ret = mSerial->setBaudRate(baudRate);
    }
    return ret;
}

bool YC_StandSource::write(QByteArray &array)
{
    bool ret = false;
    if(mSerial) {
        array.append(0x0D);
        ret = serialWrite(array);
    }

    return ret;
}


bool YC_StandSource::powerOn(int v)
{
    bool ret = setVol(220);
    if(ret) ret = setCur(v);

    return ret;
}

void YC_StandSource::powerDown()
{
    setCur(0);
    setVol(0);
    initFun();
}

bool YC_StandSource::powerReset()
{
    powerDown();
    bool ret = delay(6);
    if(ret) {
       ret = powerOn();
    }

    return ret;
}

