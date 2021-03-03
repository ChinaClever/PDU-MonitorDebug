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


void Ad_CoreThread::startCollect()
{
    //    if(!isRun) {
    //        mItem->step = Test_Collect;
    //        start();
    //    }
}

void Ad_CoreThread::startResult()
{
    //    if(!isRun) {
    //        mItem->step = Test_vert;
    //        start();
    //    }
}

bool Ad_CoreThread::initThread(int v)
{
    bool ret = false;
    //    if(mCfg->si_led) {
    //        ret = initLedSi();
    //    } else {
    //        if(mSource){
    //            QString str = tr("给标准源上电中！");
    //            ret = mSource->setVol(v, 1);
    //            updatePro(str, ret, 3);

    //           // ret = mAutoID->readDevType();  ///===========
    //        }
    //    }

    return ret;
}

void Ad_CoreThread::collectData()
{
//    bool ret = initThread(220);
//    if(!ret){mItem->step = Test_End; return;}
//    Dev_Object *th = mResult->initThread();
//    while(mItem->step != Test_Over) {
//        QString str = tr("正在读取设备数据");
//        ret = th->readPduData();
//        if(ret) str += tr("正常");
//        else str += tr("错误！");
//        updatePro(str, ret, 1);
//    }
//    updatePro(tr("读取设备数据停止！"));
}

void Ad_CoreThread::verifyResult()
{
    bool ret = initThread(200);
    if(ret) mResult->resEnter();
}



bool Ad_CoreThread::initLedSi()
{
    bool ret = false;
    //    mDt->devType = SI_PDU;
    //    mDt->ac = mItem->si_ac;
    //    mDt->specs = Transformer;
    //    mDt->lines = mItem->si_line;
    //    mPacket->dev_type = tr("SI/BM数码管");

    //    mPacket->status = tr("已启动校准！连接标准源");
    //    mSource = mResult->initStandSource();
    //    if(mSource) {
    //        mPacket->status = tr("标准源上电中");
    //        ret = mSource->setVol(220, 0);
    //        if(AC == mDt->ac) {
    //            mPacket->status = tr("标准源设置电流！");
    //            if(ret) ret = mSource->setCur(60, 4);
    //        } } else return ret;

    //    Col_CoreThread *th = mResult->initThread();
    //    if(th && ret) {
    //        for(int i=0; i<5; i++) {
    //            mPacket->status = tr("读取设备数据");
    //            if(i) mPacket->status += tr(" %1").arg(i);
    //            ret = th->readPduData(); if(ret) break; else if(!delay(3)) break;
    //        }
    //    }

    //    if(ret) {
    //        if(mDt->lines == mItem->si_line) {
    //            mPacket->status = tr("等待设备稳定"); ret = delay(7);
    //        } else {
    //            mPacket->status = tr("设备相数不对 %1").arg(mDt->lines);
    //            mPacket->pass = Test_Fail; ret = false;
    //        }
    //    }

    return ret;
}

bool Ad_CoreThread::workDown()
{
    bool ret = true;
    //    if(mItem->si_led) {
    //        ret = initLedSi(); if(!ret) return;
    //        ret = mLedSi->startAdjust(mSource);
    //    } else {
    ret = mAdjust->startAdjust();
    //    }

    if(mItem->step == Test_vert) {
        ret = mResult->resEnter();
        //    } else if(mItem->step == Test_End) {
        //        Col_CoreThread *th = mResult->initThread();
        //        th->readPduData();
    }

    return ret;
}



