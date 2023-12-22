#ifndef TEST_NETWORK_H
#define TEST_NETWORK_H
#include "baselogs.h"
#include "sn_serialnum.h"
#include "datapacket.h"
#include "json_pack.h"
#include "udprecvsocket.h"
class Test_NetWork : public BaseThread
{
    Q_OBJECT
    explicit Test_NetWork(QObject *parent = nullptr);
public:
    static Test_NetWork *bulid(QObject *parent = nullptr);

    bool startProcess();
    bool checkNet();

signals:
    void sendMACSig(QString str);

protected:
    void run();
    void workDown();
    void updateMacAddr(int step);

protected slots:
    void initFunSlot();

private:
    bool mac;
    QProcess *mProcess;
    sProgress *mPro;
    UdpRecvSocket *mUdp;
};

#endif // TEST_NETWORK_H
