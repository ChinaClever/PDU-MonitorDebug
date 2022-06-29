/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "td_linetabwid.h"

Td_LineTabWid::Td_LineTabWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}

void Td_LineTabWid::initWid()
{
    QStringList header;
    QString title = tr("相数据列表");
    header << tr("开关") << tr("电流") << tr("电压") << tr("有功功率")  << tr("功率因数") << tr("电能");
    initTableWid(header, 3, title);

    sDevData *dev = sDataPacket::bulid()->getDev();
    mData = &(dev->data);
}


void Td_LineTabWid::appendItem(sObjData *dev)
{
    for(int i=0; i<dev->size; ++i) {
        QStringList listStr;

        double crate = 1.0;
        sDevData *dd = sDataPacket::bulid()->getDev();
        mSceen = &(dd->dt);
        if(mSceen->screen == 1) crate = 10.0;
        if( mSceen->screen == 3 && dd->cfg.log_en  == 0 && dd->cfg.security  == 1) crate = 10;

        if(1 == dev->sw[i]) listStr << tr("开"); else listStr << tr("关");
        listStr << QString::number(dev->cur.value[i]/COM_RATE_CUR/crate,'f',2)+"A";
        if((dd->dt.devType == 0 && dd->cfg.si_version == 1) || (dd->dt.devType == 0 && dd->cfg.si_version == 2)) crate = 10.0;//黑底白字和腾讯定制的电压四位有小数点
        listStr << QString::number(dev->vol.value[i]/COM_RATE_VOL/crate,'f',1)+"V";
        if((dd->dt.devType == 0 && dd->cfg.si_version == 1) || (dd->dt.devType == 0 && dd->cfg.si_version == 2)) crate = 1.0;//后面恢复进制，防止电流也缩小
        if(mSceen->screen == 1)
        {
            if(mSceen->devType == 0)listStr << QString::number(dev->pow[i]/COM_RATE_PF,'f',3)+"kW";
            else listStr << QString::number(dev->pow[i]/COM_RATE_POW,'f',3)+"kW";
        }
        else if(dd->dt.devType == 0 &&(dd->cfg.si_version == 1 || dd->cfg.si_version == 2) )//SI,BM黑底白字功率只有10倍
        {
            listStr << QString::number(dev->pow[i]/COM_RATE_ELE,'f',3)+"kW";
        }
        else//标准
            listStr << QString::number(dev->pow[i]/COM_RATE_POW,'f',3)+"kW";
        if(dd->dt.devType == 0 && dd->cfg.si_version == 2)//SI,BM黑底白字功率因数只有10倍
            listStr << QString::number(dev->pf[i]/COM_RATE_ELE,'f',2);
        else//标准
            listStr << QString::number(dev->pf[i]/COM_RATE_PF,'f',2);

        listStr << QString::number(dev->ele[i]/COM_RATE_ELE,'f',2)+"kWh";
        setTableRow(i, listStr);

        setItemColor(i, 1, dev->cur.status[i]);
        setItemColor(i, 2, dev->vol.status[i]);
        //setItemColor(i, 3, dev->powStatus[i]);
    }
}

void Td_LineTabWid::timeoutDone()
{
    clearTable();
    if(mData->size) {
        appendItem(mData);
    }
}
