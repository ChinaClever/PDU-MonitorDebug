#ifndef UDPSENDSOCKET_H
#define UDPSENDSOCKET_H

#include <QObject>
#include <QtCore>
#include <QtNetwork>
#include "json_pack.h"
#include "baseobject.h"

class UdpSendSocket : public  BaseThread//QThread
{
    Q_OBJECT
public:
    explicit UdpSendSocket(QObject *parent = 0);
    ~UdpSendSocket();

    bool initSocket(int port);
    int dataSend(void);
    // BaseThread *mlogs;
protected:


signals:

public slots:
    bool dataReceivedSlot(void);
private:
    bool isRun;
    bool mRet;
    QUdpSocket *mUdpSocket;
    UdpSendSocket *mSendUdp;
    sDataPacket *mPacket;

};

#endif // UDPSENDSOCKET_H
