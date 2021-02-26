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
    Dev_Read::bulid(this);
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

            return ret;
        }
    }

    return mSn->snEnter();
}

bool Test_CoreThread::readDev()
{
    Dev_Read *dev = Dev_Read::bulid();
    return dev->readPduData();
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
