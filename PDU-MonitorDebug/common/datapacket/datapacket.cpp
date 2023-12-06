/*
 *
 *  Created on: 2020年10月1日
 *      Author: Lzy
 */
#include "datapacket.h"
#include "config.h"

sDataPacket::sDataPacket()
{
    dev = new sDevData;
    pro = new sProgress();
}


sDataPacket *sDataPacket::bulid()
{
    static sDataPacket* sington = nullptr;
    if(sington == nullptr)
        sington = new sDataPacket();
    return sington;
}

void sDataPacket::init()
{
    pro->step = 0;
    pro->result = 0;
    pro->pass.clear();
    pro->status.clear();
    dev->dt.sn.clear();
    dev->dt.dev_type.clear();

    pro->result = Test_Info;
    pro->startTime = QTime::currentTime();
    memset(&(dev->data),0,sizeof(sObjData));


    pro->softwareType = "PDU-MonitorDebug";
    pro->companyName = "clever";
    pro->protocolVersion = "V1.0";
    pro->testStartTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    pro->testEndTime.clear();
    pro->no.clear();
    pro->itemName.clear();
    pro->uploadPass.clear();
}
