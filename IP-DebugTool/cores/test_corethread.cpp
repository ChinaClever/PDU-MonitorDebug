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
    //mLogs = Test_Logs::bulid(this);

    mCtrl = Test_SiThread::bulid(this);
    mAd = Ad_CoreThread::bulid(this);
    mSn = Sn_SerialNum::bulid(this);
}

bool Test_CoreThread::setDev()
{
    bool ret = true;
    mPro->step = Test_Seting;
    if(mItem->modeId) {
        ret = Test_NetWork::bulid()->startProcess();
    } else {
        ret = mCtrl->setDev();
        if(mCfg->si_led) {

            //return ret;
        }
    }

    return mSn->snEnter();
}

bool Test_CoreThread::readDev()
{
    Dev_Object *dev = Dev_IpRtu::bulid();
    if(mItem->modeId) {
        QString str = tr("SNMP通讯");
        bool ret = Dev_IpSnmp::bulid()->readPduData();
        if(ret) str += tr("正常"); else str += tr("错误");
        updatePro(str, ret, 1);
    } else {
        dev = Dev_SiRtu::bulid();
    }

    QString str = tr("读取设备数据");
    bool ret = dev->readPduData();
    if(ret) str += tr("正常"); else str += tr("错误");
    return updatePro(str, ret);
}

bool Test_CoreThread::checkDev()
{
    QString str = tr("设备类型验证");
    bool ret = mDt->devType == mItem->modeId ? true:false;
    if(ret) str += tr("正常"); else str += tr("错误");
    ret = updatePro(str, ret);
    if(ret) {
        if(mDt->devType) {
            str = tr("设备相数验证");
            int lines = mCfg->ip_lines;
            ret = mDt->lines == lines ? true:false;
            if(ret) str += tr("正常"); else str += tr("错误");
            updatePro(str, ret);

            str = tr("设备版本验证");
            ret = mDt->version == mCfg->ip_version ? true:false;
            if(ret) str += tr("正常"); else str += tr("错误");
            updatePro(str, ret);
        }
    }

    return ret;
}

void Test_CoreThread::workResult(bool res)
{
    //    if(mItem->enSn)
    //   mSn->snEnter();
    QString str = tr("最终结果");
    if(mPro->result != Test_Fail) {
        res = true;
        str += tr("通过");
    } else {
        res = false;
        str += tr("失败");
    }

    mYc->powerDown();
    //mLogs->updatePro(str, res);
    // mLogs->saveLogs();
    mPro->step = Test_Over;
}

void Test_CoreThread::workDown()
{
    bool ret = mYc->powerOn();
    if(ret) ret = setDev();
    if(ret) ret = readDev();
    if(ret) ret = checkDev();
    if(ret) ret = mAd->startAdjust();


    workResult(ret);
}

void Test_CoreThread::run()
{
    if(isRun) return; else isRun = true;
    updatePro(tr("即将开始"));
    workDown();
    isRun = false;
}
