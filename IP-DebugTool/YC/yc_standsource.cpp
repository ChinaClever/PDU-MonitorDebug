/*
 *
 *  Created on: 2020年10月1日
 *      Author: Lzy
 */
#include "yc_standsource.h"

YC_StandSource::YC_StandSource(QObject *parent) : Object(parent)
{
    mSerial = nullptr;
}

void YC_StandSource::initFunSlot()
{
    if(mItem->source) {
        mSerial = mItem->source;
    } else {
        QTimer::singleShot(350,this,SLOT(initFunSlot()));
    }
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


bool YC_StandSource::powerReset()
{
    powerDown();
    bool ret = delay(6);
    if(ret) {
        ret = setVol(220);
        if(ret) {
            ret = setCur(60);
        }
    }

    return ret;
}

