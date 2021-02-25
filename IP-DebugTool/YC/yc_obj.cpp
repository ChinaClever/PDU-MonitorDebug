#include "yc_obj.h"

Yc_Obj::Yc_Obj(QObject *parent) : BaseThread(parent)
{
    mAc = YC_Ac92b::bulid(this);
    mDc = YC_Dc107::bulid(this);
}


Yc_Obj *Yc_Obj::bulid(QObject *parent)
{
    static Yc_Obj* sington = nullptr;
    if(sington == nullptr)
        sington = new Yc_Obj(parent);
    return sington;
}

YC_StandSource *Yc_Obj::get()
{
    YC_StandSource *yc = mAc;
    if(mItem->modeId) {
        if(mCfg->ip_ac == DC) yc = mDc;
    } else {
        if(mCfg->si_ac == DC) yc = mDc;
    }

    return yc;
}

bool Yc_Obj::powerOn()
{
    YC_StandSource *yc = get();
    QString str = tr("标准源上电");
    bool ret = yc->handShake();
    if(ret) {
        ret = yc->powerOn();
    } else {
         str += tr("失败");
    }

    return updatePro(str, ret);
}

void Yc_Obj::powerDown()
{
    YC_StandSource *yc = get();
    return yc->powerDown();
}

bool Yc_Obj::setCur(int v, int sec)
{
    YC_StandSource *yc = get();
    return yc->setCur(v, sec);
}

bool Yc_Obj::setVol(int v, int sec)
{
    YC_StandSource *yc = get();
    return yc->setVol(v, sec);
}
