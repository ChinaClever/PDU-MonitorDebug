/*
 *
 *  Created on: 2020年10月1日
 *      Author: Lzy
 */
#include "td_datatabwid.h"

Td_DataTabWid::Td_DataTabWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}

void Td_DataTabWid::initWid()
{
    QStringList header;
    QString title = tr("状态列表");
    header<<tr("开关") << tr("电流") << tr("电压") << tr("功率") << tr("电能") << tr("最终电流") << tr("最终功率")<< tr("结果");
    initTableWid(header, 3, title);
    sDevData *dev = sDataPacket::bulid()->getDev();
    mData = &(dev->data);
}


void Td_DataTabWid::appendItem(sObjData *unit)
{
    for(int i=0; i<unit->size; ++i) {
        QStringList listStr;
        double crate = 1.0;
        sDevData *dd = sDataPacket::bulid()->getDev();
        mSceen = &(dd->dt);
        if(mSceen->screen == 1) crate = 10.0;

        if(1 == unit->sw[i]) listStr << tr("开"); else listStr << tr("关");
        listStr << QString::number(unit->cur.value[i]/COM_RATE_CUR/crate,'f',2)+"A";

        if((dd->dt.devType == 0 && dd->cfg.si_version == 1 )|| (dd->dt.devType == 0 &&dd->cfg.si_version == 2)) crate = 10.0;//黑底白字和腾讯定制的电压四位有小数点
        listStr << QString::number(unit->vol.value[i]/COM_RATE_VOL/crate,'f',1)+"V";
        if((dd->dt.devType == 0 && dd->cfg.si_version == 1) || (dd->dt.devType == 0 && dd->cfg.si_version == 2)) crate = 1.0;//后面恢复进制，防止电流也缩小
        if(mSceen->screen == 1)
        {
            if(mSceen->devType == 0) listStr << QString::number(unit->pow[i]/COM_RATE_PF,'f',3)+"kW";
            else listStr << QString::number(unit->pow[i]/COM_RATE_POW,'f',3)+"kW";
        }
        else if(dd->dt.devType == 0 && dd->cfg.si_version == 2)//SI,BM黑底白字功率只有10倍
        {
            listStr << QString::number(unit->pow[i]/COM_RATE_ELE,'f',3)+"kW";
        }
        else
            listStr << QString::number(unit->pow[i]/COM_RATE_POW,'f',3)+"kW";
        listStr << QString::number(unit->ele[i]/COM_RATE_ELE,'f',2)+"kWh";
        if(unit->cured[i]) {
            listStr << QString::number(unit->cured[i]/COM_RATE_CUR/crate,'f',2)+"A";
        } else {
            listStr << "---";
        }

        if(unit->powed[i]) {
            if(mSceen->screen == 1)
            {
               if(mSceen->devType == 0) listStr << QString::number(unit->pow[i]/COM_RATE_PF,'f',3)+"kW";
               else listStr << QString::number(unit->pow[i]/COM_RATE_POW,'f',3)+"kW";
            }
            else if(dd->dt.devType == 0 && dd->cfg.si_version == 2)//SI,BM黑底白字功率只有10倍
            {
                listStr << QString::number(unit->pow[i]/COM_RATE_ELE,'f',3)+"kW";
            }
            else
                listStr << QString::number(unit->pow[i]/COM_RATE_POW,'f',3)+"kW";
        } else {
            listStr << "---";
        }

        switch (unit->status[i]) {
        case Test_Fail: listStr << "×"; break;
        case Test_Pass: listStr << "√"; break;
        default: listStr << " "; break;
        }

        setTableRow(i, listStr);
        if(unit->status[i] == Test_Fail) {
            setAlarmBackgroundColor(i);
        } else {
            setNormalBackgroundColor(i);
        }
    }
}

void Td_DataTabWid::timeoutDone()
{
    if(mData->size) {
        appendItem(mData);
    } else {
        clearTable();
    }
}
