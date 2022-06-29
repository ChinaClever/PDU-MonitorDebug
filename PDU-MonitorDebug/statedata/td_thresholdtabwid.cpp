/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "td_thresholdtabwid.h"

Td_ThresholdTabWid::Td_ThresholdTabWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}

void Td_ThresholdTabWid::initWid()
{
    QStringList header;
    QString title = tr("报警阈值");
    header << tr("项目") << tr("当前值") << tr("最小值") << tr("最大值");
    initTableWid(header, 6, title);
    sDevData *dev = sDataPacket::bulid()->getDev();
    mData = &(dev->data);
}

void Td_ThresholdTabWid::setDataUnit(int id, sDataUnit &unit)
{
    double rate = COM_RATE_CUR;
    QString suffix = "A";
    QString str = tr("电流");
    if(id < 3) {
        rate = 1;
        suffix = "V";
        str = tr("电压");
    }
    double crate = 1.0;
    sDevData *dev = sDataPacket::bulid()->getDev();
    mSceen = &(dev->dt);
    if(mSceen->screen == 1) crate = 10.0;
    if( mSceen->screen == 3 && dev->cfg.log_en  == 0 && dev->cfg.security  == 1) crate = 10.0;

    for(int i=0; i<unit.size; ++i) {
        QStringList listStr;

        listStr << str;
        if(str == tr("电压") && ((dev->dt.devType == 0 && dev->cfg.si_version == 1) || (dev->dt.devType == 0 && dev->cfg.si_version == 2))) crate = 10.0;//黑底白字和腾讯定制的电压四位有小数点
        listStr << QString::number(unit.value[i]/rate/crate,'f',2)+suffix;
        if(str == tr("电压") && ((dev->dt.devType == 0 && dev->cfg.si_version == 1) || (dev->dt.devType == 0 && dev->cfg.si_version == 2))) crate = 1.0;//后面恢复进制，防止电流也缩小
        listStr << QString::number(unit.min[i]/rate/crate,'f',2)+suffix;
        listStr << QString::number(unit.max[i]/rate/crate,'f',2)+suffix;
        setTableRow(id+i, listStr);

        if((unit.value[i] < unit.min[i]) || (unit.value[i] > unit.max[i])) {
            unit.alarm[i] = 2;
            setAlarmBackgroundColor(id+i);
        } else {
            unit.alarm[i] = 0;
            setNormalBackgroundColor(id+i);
        }
    }
}

void Td_ThresholdTabWid::appendItem(sObjData *dev)
{
    setDataUnit(0, dev->vol);
    setDataUnit(3, dev->cur);
}

void Td_ThresholdTabWid::timeoutDone()
{
    clearTable();
    if(mData->size) {
        appendItem(mData);
    }
}
