#ifndef AD_RESULTING_H
#define AD_RESULTING_H

#include "ad_adjusting.h"
#include "dev_ipcfg.h"

class Ad_Resulting : public BaseThread
{
    Q_OBJECT
    explicit Ad_Resulting(QObject *parent = nullptr);
public:
    static Ad_Resulting *bulid(QObject *parent = nullptr);

    bool resEnter();
    Dev_Object *initThread();
    YC_StandSource *initStandSource();

protected:
    bool powErrRange(int exValue, int cur);
    bool curErrRange(int exValue, int cur);

    bool curRangeByID(int i, int exValue, int cnt);
    bool powRangeByID(int i, int exValue, int cnt);
    bool volErrRange();
    bool volErrRangeByID(int i);
    bool workDown(int exValue);

    bool eachCurCheck(int exValue, int cnt);
    bool eachCurEnter(int exValue);

    bool noLoadEnter();
    bool noLoadCurFun();
    bool noLoadCurCheck(int cnt);
    bool powerOn();

private:
    YC_StandSource *mSource;
    Dev_Object *mCollect;
};

#endif // AD_RESULTING_H
