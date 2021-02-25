#ifndef AD_CORETHREAD_H
#define AD_CORETHREAD_H

#include "ad_resulting.h"

class Ad_CoreThread : public BaseThread
{
    Q_OBJECT
    explicit Ad_CoreThread(QObject *parent = nullptr);
public:
    static Ad_CoreThread *bulid(QObject *parent = nullptr);
    ~Ad_CoreThread();

    void startAdjust();
    void startCollect();
    void startResult();

protected:
    void run();
    bool initLedSi();
    bool initThread(int v);
    bool initSource();

    void writeLog();
    void workDown();
    void collectData();
    void verifyResult();
    bool readDevInfo();

private:
    bool isRun;
    Ad_Adjusting *mAdjust;
    Ad_Resulting *mResult;
    YC_StandSource *mSource;
    Ad_LedSi *mLedSi;
};

#endif // AD_CORETHREAD_H
