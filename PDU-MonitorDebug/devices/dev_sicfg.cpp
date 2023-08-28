/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dev_sicfg.h"

Dev_SiCfg::Dev_SiCfg(QObject *parent) : Dev_Object(parent)
{
    initCfg();
}

Dev_SiCfg *Dev_SiCfg::bulid(QObject *parent)
{
    static Dev_SiCfg* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_SiCfg(parent);
    return sington;
}

void Dev_SiCfg::initType()
{
    sTypeCfg *ptr = mCfg;
    ptr->si_ac = read("si_ac", 1).toInt();
    ptr->si_led = read("si_led", 0).toInt();
    ptr->si_lines = read("si_lines", 1).toInt();
    ptr->si_series = read("si_series", 0).toInt();
    ptr->si_standar = read("si_standar", 0).toInt();
    ptr->si_version = read("si_version", 0).toInt();
}

void Dev_SiCfg::writeType()
{
    sTypeCfg *ptr = mCfg;
    write("si_ac", ptr->si_ac);
    write("si_lines", ptr->si_lines);
//    write("si_led", ptr->si_led);
    write("si_series", ptr->si_series);
    write("si_standar", ptr->si_standar);
    write("si_version", ptr->si_version);
}

void Dev_SiCfg::initData()
{
    sObjCfg *ptr = &(mCfg->si_cfg);
    initUnit("vol", ptr->vol);
    initUnit("cur", ptr->cur);

    initUnit("tem", ptr->tem);
    initUnit("hum", ptr->hum);
}

void Dev_SiCfg::writeData()
{
    sObjCfg *ptr = &(mCfg->si_cfg);
    writeUnit("vol", ptr->vol);
    writeUnit("cur", ptr->cur);

    writeUnit("tem", ptr->tem);
    writeUnit("hum", ptr->hum);
}

void Dev_SiCfg::initCfg()
{
    initType();
    initData();
}

void Dev_SiCfg::save()
{
    writeType();
    writeData();
}
