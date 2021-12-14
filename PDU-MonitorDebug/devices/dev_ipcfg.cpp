/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dev_ipcfg.h"

Dev_IpCfg::Dev_IpCfg(QObject *parent) : Dev_Object(parent)
{
    initCfg();
}


Dev_IpCfg *Dev_IpCfg::bulid(QObject *parent)
{
    static Dev_IpCfg* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_IpCfg(parent);
    return sington;
}


void Dev_IpCfg::initType()
{
    sTypeCfg *ptr = mCfg;
    ptr->ip_ac = read("ip_ac", 1).toInt();
    ptr->ip_version = read("ip_version", 1).toInt();
    ptr->ip_lines = read("ip_lines", 1).toInt();
    ptr->ip_standard = read("ip_standard", 0).toInt();

    ptr->ip_language = read("ip_language", 1).toInt();
    ptr->ip_modbus = read("ip_modbus", 0).toInt();
    ptr->security = read("security", 0).toInt();
    ptr->log_en = read("log_en", 0).toInt();
    ptr->ip_lcd = read("ip_lcd", 0).toInt();
    ptr->ip_inFirst = read("ip_inFirst", "IEC309").toString();
    ptr->ip_inSecond = read("ip_inSecond", "18A").toString();
    ptr->ip_outFirst = read("ip_outFirst", "20xC13").toString();
    ptr->ip_outSecond = read("ip_outSecond", "4xC19").toString();
}

void Dev_IpCfg::writeType()
{
    sTypeCfg *ptr = mCfg;
    write("ip_ac", ptr->ip_ac);
    write("ip_version", ptr->ip_version);
    write("ip_lines", ptr->ip_lines);
    write("ip_standard", ptr->ip_standard);

    write("ip_language", ptr->ip_language);
    write("ip_modbus", ptr->ip_modbus);
    write("security", ptr->security);
    write("log_en", ptr->log_en);
    write("ip_lcd", ptr->ip_lcd);
    write("ip_inFirst", ptr->ip_inFirst);
    write("ip_inSecond", ptr->ip_inSecond);
    write("ip_outFirst", ptr->ip_outFirst);
    write("ip_outSecond", ptr->ip_outSecond);
}

void Dev_IpCfg::initData()
{
    sObjCfg *ptr = &(mCfg->ip_cfg);
    initUnit("vol", ptr->vol);
    initUnit("cur", ptr->cur);

    initUnit("tem", ptr->tem);
    initUnit("hum", ptr->hum);
    initFanTemUnit("fantem", ptr->fantem);
    initFanTemUnit("pwm", ptr->pwm);
}

void Dev_IpCfg::writeData()
{
    sObjCfg *ptr = &(mCfg->ip_cfg);
    writeUnit("vol", ptr->vol);
    writeUnit("cur", ptr->cur);

    writeUnit("tem", ptr->tem);
    writeUnit("hum", ptr->hum);

    writeFanTemUnit("fantem", ptr->fantem);
    writeFanTemUnit("pwm", ptr->pwm);
}

void Dev_IpCfg::initCfg()
{
    initType();
    initData();
}

void Dev_IpCfg::save()
{
    writeType();
    writeData();
}
