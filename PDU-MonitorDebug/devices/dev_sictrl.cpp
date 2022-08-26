/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dev_sictrl.h"

Dev_SiCtrl::Dev_SiCtrl(QObject *parent) : Dev_Object(parent)
{
}

Dev_SiCtrl *Dev_SiCtrl::bulid(QObject *parent)
{
    static Dev_SiCtrl* sington = nullptr;
    if(sington == nullptr)
        sington = new Dev_SiCtrl(parent);
    return sington;
}

bool Dev_SiCtrl::setCurTh(int i)
{
    bool ret = true;
    ushort reg = 0x1008 + 2*i;
    if(DC == mCfg->si_ac) reg = 0x1016;

    sUnitCfg *unit = &(mCfg->si_cfg.cur);
    ushort value = unit->max * 10;
    if(mDt->screen == 1) value *= 10;
    if((mCfg->si_lines == 2) && i) {
        if(value == 630&&value == 6300) value = (value/10 +1)/2 * 10; // 解决单项二路阈值问题
        else value /= 2;
    }

    if(mData->cur.max[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    value = unit->min * 10;
    if(mDt->screen == 1) value *= 10;
    if(mData->cur.min[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    return ret;
}

bool Dev_SiCtrl::setVolTh(int i)
{
    ushort reg = 0x1002 + 2*i;
    if(DC == mCfg->si_ac) reg = 0x1014;
    if(mDt->screen == 1)
        return writeReg(reg, i, mData->vol, mCfg->si_cfg.vol , 10);
    else
        return writeReg(reg, i, mData->vol, mCfg->si_cfg.vol );
}

bool Dev_SiCtrl::setTem()
{
    return writeReg(0x100E, 0, mData->tem, mCfg->si_cfg.tem);
}

bool Dev_SiCtrl::setHum()
{
    return writeReg(0x1010, 0, mData->hum, mCfg->si_cfg.hum);
}

bool Dev_SiCtrl::writeReg(ushort reg, int i, sDataUnit &it, sUnitCfg &unit, int r)
{
    bool ret = true;

    ushort value = unit.max * r;
    if(it.max[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    value = unit.min * r;
    if(it.min[i] != value) {
        ret = sentRtuCmd(reg++, value); if(!ret) return ret;
    } else reg++;

    return ret;
}


bool Dev_SiCtrl::unClock()
{    
    return sentRtuCmd(0x1048, 0x4A53);
}

bool Dev_SiCtrl::setDev()
{
    bool ret =  false;
    if(mCfg->si_lines == 2 && mDt->devType == 0 && mDt->screen == 1) sentRtuCmd(0x1049, 0x03);
    ret = sentRtuCmd(0x1049, mCfg->si_lines); ret = true;  //断码屏没有返回，上面命令默认都能成功
    if(ret) ret = sentRtuCmd(0x1051, mCfg->si_series);
    if(ret) ret = sentRtuCmd(0x1050, mCfg->si_version); //mCfg->si_standar

    return ret;
}

bool Dev_SiCtrl::clearEle()
{
    return sentRtuCmd(0x1013, 0x00F0); // 清除电能
}

bool Dev_SiCtrl::factorySet()
{
    bool ret = true;
    if(mCfg->si_standar) {
        ret = sentRtuCmd(0x1019, mCfg->si_standar);
    }

    return ret;
}

bool Dev_SiCtrl::setHorizontaOrVertical()
{
    bool ret = true;
    if(!mCfg->si_led) {
        ret = sentRtuCmd(0x1021, mCfg->si_horizontal);
    }

    return ret;
}

bool Dev_SiCtrl::sentRtuCmd(ushort reg, ushort value, uchar fn)
{
    bool ret = true;
    sRtuSetItem it;
    it.addr = mItem->addr;
    it.fn = fn;
    it.reg = reg;
    it.data = value;

    for(int i=0; i<3; ++i) {
        ret = mModbus->write(it);
        if(ret) break; else delay(2+i);
    }

    return ret;
}
