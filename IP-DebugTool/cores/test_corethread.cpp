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
    mLogs = Test_Logs::bulid(this);
    mNet = Test_NetWork::bulid(this);
    mCtrl = Test_SiThread::bulid(this);
    mSn = Sn_SerialNum::bulid(this);
}



void Test_CoreThread::workResult(bool res)
{
//    if(mItem->enSn)
        mSn->snEnter();
    QString str = tr("最终结果");
    if(mPro->result != Test_Fail) {
        res = true;
        str += tr("通过");
    } else {
        res = false;
        str += tr("失败");
    }

    mLogs->updatePro(str, res);
    mLogs->saveLogs();
    mPro->step = Test_Over;
}

void Test_CoreThread::workDown()
{
    bool ret = Yc_Obj::bulid(this)->powerOn();

    ////////////

    if(mItem->modeId) {
        ret = mNet->startProcess();
    } else {
        ret = mCtrl->setDev();
    }

    workResult(ret);
}

void Test_CoreThread::run()
{
    if(isRun) return;
    isRun = true;

    workDown();
    isRun = false;
}
