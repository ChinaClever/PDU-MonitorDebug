/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "test_corethread.h"

Test_CoreThread::Test_CoreThread(QObject *parent) : BaseThread(parent)
{

}

void Test_CoreThread::initFunSlot()
{
    Dev_SiRtu::bulid(this);
    Dev_IpRtu::bulid(this);
    Dev_IpSnmp::bulid(this);
    Test_NetWork::bulid(this);
    mYc = Yc_Obj::bulid(this);

    mCtrl = Test_SiThread::bulid(this);
    mAd = Ad_CoreThread::bulid(this);
    mSn = Sn_SerialNum::bulid(this);
}

bool Test_CoreThread::setDev()
{
    bool ret = true;
    if(mItem->modeId) {
        if(mPro->step > Test_Seting) ret = delay(6);
        else ret = Test_NetWork::bulid()->startProcess();
    } else {
        ret = mCtrl->setDev();
        if(mCfg->si_led) return ret;
    }

    if(ret) ret = mSn->snEnter();
    return ret;
}

bool Test_CoreThread::readDev()
{
    bool ret = true;
    Dev_Object *dev = Dev_IpRtu::bulid();
    if(mItem->modeId) {
        QString str = tr("Modbus RTU通讯 ");
        ret = dev->readPduData();
        if(ret) str += tr("正常"); else str += tr("错误");
        updatePro(str, ret);

        if(mCfg->ip_modbus) {
        } else {
            if(mPro->step >= Test_Seting) return ret;
            ret = Test_NetWork::bulid()->checkNet(); if(!ret) return ret;
            //str = tr("SNMP通讯 ");
            //Dev_IpSnmp *snmp = Dev_IpSnmp::bulid(); ret = snmp->readPduData();
            //if(!ret) {snmp->resetSnmp(); ret = snmp->readPduData();}
            //if(ret) str += tr("正常"); else str += tr("错误");
            //updatePro(str, ret, 1);
        }
    }

    return ret;
}

bool Test_CoreThread::checkDev()
{
    QString str = tr("设备类型验证");
    bool ret = mDt->devType == mItem->modeId ? true:false;
    if(ret) str += tr("正常"); else str += tr("错误");
    ret = updatePro(str, ret);
    if(ret) {
        if(mDt->devType) {
            if(mCfg->ip_ac == AC) {
                str = tr("设备相数验证");
                int lines = mCfg->ip_lines;
                ret = mDt->lines == lines ? true:false;
                if(ret) str += tr("正常"); else str += tr("错误");
                updatePro(str, ret);
            }

            str = tr("设备版本验证");
            if(mDt->version == mCfg->ip_version)
                ret = true;
            else if( IP_PDUV1_HUADA  == mCfg->ip_version)
                ret = true;
            else if( IP_PDUV3_EATON - 2  == mCfg->ip_version)
                ret = false;
            if(ret) str += tr("正常"); else str += tr("错误");
            updatePro(str, ret);
        }
    }

    return ret;
}

void Test_CoreThread::workResult()
{
    BaseLogs::bulid()->start();
    bool res = mYc->powerDown();
    QString str = tr("最终结果 ");
    if(mPro->result != Test_Fail) {
        str += tr("通过");
    } else {
        res = false;
        str += tr("失败");
    }

    updatePro(str, res, 2);
    mPro->step = Test_Over;
}


bool Test_CoreThread::initFun()
{
    updatePro(tr("即将开始"));
    bool ret = mYc->powerOn();
    if(ret) ret = setDev();
    if(ret) ret = readDev();
    if(ret && !mDt->devType) {
        ret = mCtrl->setAlarm();
    }

    return ret;
}


void Test_CoreThread::workDown()
{
    bool ret = checkDev();
    if(ret) ret = mAd->startAdjust();
    if(!mItem->modeId) {
        mCtrl->clearEle();
        Ad_Resulting::bulid(this)->initRtuThread();
    }

    for(int i=0; i<3; ++i) {
        if(mData->ele[i]) {
            QString e = QString::number(mData->ele[i]/COM_RATE_ELE,'f',2)+"kWh";
            QString str = tr("L%1 存在电能 %2").arg(i+1).arg(e);
            updatePro(str, false);
        }
    }
}

void Test_CoreThread::collectData()
{
    int cnt = 0;
    Dev_Object *dev = Dev_SiRtu::bulid();
    if(mItem->modeId) dev = Dev_IpRtu::bulid();

    while(mPro->step == Test_Collect) {
        bool ret = dev->readPduData();
        if(ret && (++cnt%30)) continue;
        QString str = tr("正在读取设备数据 %1").arg(cnt);
        if(!ret && (cnt>5)) str= tr("读取设备数据错误！");
        updatePro(str, ret, 2);
    }

    QString str = tr("读取设备数据停止！");
    updatePro(str);
}


void Test_CoreThread::run()
{

    if(mItem->aiMode == Test_Onebyone){
        mControlOp = Ctrl_ZpduThread::bulid();
        if(mControlOp){
            mControlOp->openAllSwitch();
            delay(5);
            mControlOp->openAllSwitch();
        }
    }
    if(isRun) return; else isRun = true;
    bool ret = initFun();
//    bool ret = mSn->snEnter();
//    if(ret) ret= readDev();
    if(ret) {
        switch (mPro->step) {
        case Test_Start: workDown(); break;
        case Test_Collect: collectData(); break;
        case Test_Ading: mAd->startAdjust(); break;
        case Test_vert: mAd->verifyResult(); break;
        }
    } else mPro->result = Test_Fail;

    workResult();
    isRun = false;
}
