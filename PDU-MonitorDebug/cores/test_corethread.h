#ifndef TEST_CORETHREAD_H
#define TEST_CORETHREAD_H
#include "yc_obj.h"
#include "test_sithread.h"
#include "ad_corethread.h"
#include "ctrl_zpduthread.h"
#include "udpsendsocket.h"

class Test_CoreThread : public BaseThread
{
    Q_OBJECT
public:
    explicit Test_CoreThread(QObject *parent = nullptr);

protected:
    void run();
    bool initFun();
    bool setDev();
    bool readDev();
    bool checkDev();
    void workDown();
    void collectData();
    void workResult();

protected slots:
    void initFunSlot();
    void getMacSlot(QString str);

private:
    Yc_Obj *mYc;
    Sn_SerialNum *mSn;
    Test_SiThread *mCtrl;
    Ad_CoreThread *mAd;
    Ctrl_ZpduThread *mControlOp;
    QString mMacStr;
    UdpSendSocket *mSendUdp;
};

#endif // TEST_CORETHREAD_H
