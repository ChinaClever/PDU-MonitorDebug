#include "dev_read.h"

Dev_Read::Dev_Read(QObject *parent) : BaseThread(parent)
{
    Dev_SiRtu::bulid(this);
    Dev_IpRtu::bulid(this);
    Dev_IpSnmp::bulid(this);
}

Dev_Read *Dev_Read::bulid(QObject *parent)
{
    static Dev_Read* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_Read(parent);
    return sington;
}

bool Dev_Read::readPduData()
{
    Dev_Object *dev = Dev_IpRtu::bulid();
    if(mItem->modeId) {
        QString str = tr("SNMP通讯");
        bool ret = Dev_IpSnmp::bulid()->readPduData();
        if(ret) str += tr("正常"); else str += tr("错误");
        updatePro(str, ret);
    } else {
        dev = Dev_SiRtu::bulid();
    }

    QString str = tr("读取设备数据");
    bool ret = dev->readPduData();
    if(ret) str += tr("正常"); else str += tr("错误");
    return updatePro(str, ret);
}
