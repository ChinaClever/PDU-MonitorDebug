/*
 *
 *  Created on: 2020年10月1日
 *      Author: Lzy
 */
#include "ad_corethread.h"
#include "dblogs.h"
extern QString user_land_name();

Ad_CoreThread::Ad_CoreThread(QObject *parent) : BaseThread(parent)
{
    mLedSi = Ad_LedSi::bulid(this);
    mAdjust = Ad_Adjusting::bulid(this);
    mResult = Ad_Resulting::bulid(this);
}

Ad_CoreThread *Ad_CoreThread::bulid(QObject *parent)
{
    static Ad_CoreThread* sington = nullptr;
    if(sington == nullptr)
        sington = new Ad_CoreThread(parent);
    return sington;
}


bool Ad_CoreThread::workDown()
{
    bool ret = true;
    if(!mDt->devType && mCfg->si_led) {
        ret = mLedSi->startAdjust();
    } else {
        if(mItem->aiMode == Test_Onebyone)
            //ret = mAdjust->startAdjustOneByOne(mDt->lines);
        {
            mControlOp = Ctrl_ZpduThread::bulid();
            for(int i = 0 ; i < mDt->lines; i++){
                if(mControlOp){
                    mControlOp->openOnlySwitch(i);
                    mControlOp->delay(5);
                    mControlOp->openOnlySwitch(i);
                }
                else
                    return false;
                ret = mAdjust->sentCmdkPhase(i+1);
                sleep(35);
                if(ret){
                    ret = mAdjust->readData();
                }
                mResult->eachCurCheckInAdjusting(i , 6*100);
            }
        }
        else
            ret = mAdjust->startAdjust();
    }

    if(mPro->step == Test_vert) {
        if(mItem->aiMode == Test_Onebyone)
            ret = mResult->resEnterOneByOne();
        else
            ret = mResult->resEnter();
    } else if(mPro->step == Test_Over) {
        ret = mResult->initRtuThread();
    }

    return ret;
}



