#ifndef TEST_CORETHREAD_H
#define TEST_CORETHREAD_H
#include "yc_obj.h"
#include "test_sithread.h"
#include "ad_corethread.h"

class Test_CoreThread : public BaseThread
{
    Q_OBJECT
public:
    explicit Test_CoreThread(QObject *parent = nullptr);

protected:
    void run();
    bool setDev();
    bool readDev();
    void workDown();
    void workResult(bool res);

protected slots:
    void initFunSlot();

private:
    Yc_Obj *mYc;
    //Test_Logs *mLogs;
    Sn_SerialNum *mSn;
    Test_SiThread *mCtrl;
    Ad_CoreThread *mAd;
};

#endif // TEST_CORETHREAD_H
