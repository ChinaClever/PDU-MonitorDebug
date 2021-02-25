/*
 *
 *  Created on: 2020年10月1日
 *      Author: Lzy
 */
#include "ad_resulting.h"
#define AD_CUR_RATE 100

Ad_Resulting::Ad_Resulting(QObject *parent) : BaseThread(parent)
{
    //mSource =YC_Ac92b::bulid(this);
    mCollect= nullptr;
}

Ad_Resulting *Ad_Resulting::bulid(QObject *parent)
{
    static Ad_Resulting* sington = nullptr;
    if(sington == nullptr)
        sington = new Ad_Resulting(parent);
    return sington;
}

bool Ad_Resulting::curErrRange(int exValue, int cur)
{
    bool ret = false;
    int min = exValue - mItem->curErr * 10;
    int max = exValue + mItem->curErr * 10;

    if((cur >= min) && (cur <= max )) {
        ret =  true;
    }

    return ret;
}

bool Ad_Resulting::powErrRange(int exValue, int pow)
{
    bool ret = false;
    int err = exValue * mItem->powErr/1000.0;
    int min = exValue - err;
    int max = exValue + err;

    if((pow >= min) && (pow <= max )) {
        ret =  true;
    } else {
        qDebug() << "pow Err Range" << pow << exValue << err;
    }

    return ret;
}


bool Ad_Resulting::powRangeByID(int i, int exValue, int cnt)
{
    exValue = mItem->vol * exValue/AD_CUR_RATE;
    if(AC == mDt->ac) exValue *= 0.5;
    QString str = tr("期望功率%1kW 第%2位 功率").arg(exValue/1000.0).arg(i+1);
    bool ret = powErrRange(exValue, mData->pow[i]);
    mData->powed[i] = mData->pow[i];
    if(ret) {
        str += tr("正常");
    } else {
        if(cnt > 3) {
            str += tr("错误");
            mData->status[i] = Test_Fail;
        }
        ret = false;
    }

    return updatePro(str, ret, 0);
}

bool Ad_Resulting::curRangeByID(int i, int exValue, int cnt)
{
    int cur = mData->cur.value[i] * 10;
    if(mDt->lines == 2 &&i == 0) exValue *= 2;
    QString str = tr("期望电流%1A 第%2位 电流").arg(exValue/AD_CUR_RATE).arg(i+1);
    bool ret = curErrRange(exValue, cur);
    mData->cured[i] = mData->cur.value[i];
    if(ret) {
        // if(mItem->si_led) return ret;   ////===========
        ret = powRangeByID(i, exValue, cnt);
    } else {
        if(cnt > 2) {
            str += tr("错误");
            mData->status[i] = Test_Fail;
        }
        ret = false;
    }

    return updatePro(str, ret, 0);
}


bool Ad_Resulting::volErrRangeByID(int i)
{
    bool ret = true;
    int vol = mData->vol.value[i];
    int min = mItem->vol - mItem->volErr;
    int max = mItem->vol + mItem->volErr;
    QString str = tr("期望电压200V，实际电压%1V 第%2位 电压").arg(vol).arg(i+1);
    if((vol >= min) && (vol <= max)) {
        mData->status[i] = Test_Pass;
    } else {
        ret = false;
    }

    return updatePro(str, ret, 0);
}


bool Ad_Resulting::volErrRange()
{
    int k = 0;
    bool ret = mCollect->readPduData();
    for(int i=0; i<mData->size; ++i) {
        ret = volErrRangeByID(i);
        if(!ret) {
            if(k++ < 5){
                i = -1; delay(2);
                mCollect->readPduData();
            } else {
                ret = false;
                mData->status[i] = Test_Fail;
                QString str = tr("检测到电压 %1 错误").arg(i+1);
                updatePro(str, ret, 0); break;
            }
        }
    }

    return ret;
}


bool Ad_Resulting::eachCurCheck(int exValue, int cnt)
{
    bool res = true;
    for(int k=0; k<mData->size; ++k) {
        bool ret = curRangeByID(k, exValue, cnt);
        if(!ret) {res = false;return res;}
    }

    return res;
}

bool Ad_Resulting::eachCurEnter(int exValue)
{
    bool ret = true;
    for(int i=0; i<5; ++i) {
        double value = mItem->vol*exValue/AD_CUR_RATE/1000.0;
        if(AC == mDt->ac) value = value*0.5;
        QString str = tr("校验数据: 期望电流%1A 功率%2kW").arg(exValue/AD_CUR_RATE).arg(value);
        if(i) str += tr(" 第%1次").arg(i+1); else delay(4);

        updatePro(str, ret, 0);
        mCollect->readPduData();
        ret = eachCurCheck(exValue, i);
        if(ret) break; else if(!delay(3)) break;
    }

    return ret;
}


YC_StandSource *Ad_Resulting::initStandSource()
{
    if(DC == mDt->ac) {
        mSource = YC_Dc107::bulid(this);
    } else {
        mSource = YC_Ac92b::bulid(this);
    }

    QString str = tr("标准源通讯");
    bool ret = mSource->handShake();
    if(ret) str += tr("成功!"); else str += tr("失败!");
    updatePro(str, ret, 0);

    return mSource;
}

Dev_Object *Ad_Resulting::initThread()
{
    switch (mDt->devType) {
    case SI_PDU: mCollect = Dev_SiRtu::bulid(this); break;
    case IP_PDU: mCollect = Dev_IpRtu::bulid(this); break;
    default: mCollect = nullptr; break;
    }

    return mCollect;
}

bool Ad_Resulting::workDown(int exValue)
{
    return eachCurEnter(exValue);
}

bool Ad_Resulting::noLoadCurCheck(int cnt)
{
    bool res = true;
    for(int k=0; k<mData->size; ++k) {
        mData->powed[k] = mData->pow[k];
        mData->cured[k] = mData->cur.value[k];
        if(mData->cur.value[k] || mData->pow[k]) {
            res = false;
            if(cnt > 2) {
                mData->status[k] = Test_Fail;
                QString str = tr("空载校验:第%1位").arg(k+1);
                if(mData->cur.value[k]) str += tr("电流有底数");
                if(mData->pow[k]) str += tr(" 功率有底数");
                updatePro(str, res, 0);
            }
        } else {
            mData->status[k] = Test_Pass;
        }
    }

    return res;
}

bool Ad_Resulting::noLoadCurFun()
{
    bool ret = true;
    for(int i=0; i<5; ++i) {
        QString str = tr("空载校验: 第%2次检查").arg(i+1);
        updatePro(str, ret, 0);

        mCollect->readPduData();
        ret = noLoadCurCheck(i);
        if(ret) break; else if(!delay(3)) break;
    }

    return ret;
}

bool Ad_Resulting::noLoadEnter()
{
    QString str = tr("空载验证：设置空载电流");
    bool ret = mSource->setCur(0, 1);
    updatePro(str, ret, 3);

    if(ret) ret = noLoadCurFun();
    if(ret) ret = volErrRange();
    return ret;
}

bool Ad_Resulting::powerOn()
{
    bool ret = true;
    mItem->step = Test_vert;
    QString str = tr("自动验证开始");
    updatePro(str, ret, 0);
    ret = mSource->setVol(200, 0);
    ret = mSource->setCur(40, 2);
    str = tr("验证电流：期望电流4A");
    return updatePro(str, ret, 3);
}


bool Ad_Resulting::resEnter()
{
    bool ret = powerOn();
    if(ret) {
        ret = workDown(4*AD_CUR_RATE);
        if(ret) ret = noLoadEnter();
    }

    return ret;
}

