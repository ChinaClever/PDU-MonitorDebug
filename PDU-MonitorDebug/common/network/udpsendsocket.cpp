/*
 * UdpSendSocket.cpp
 * UDP 接收套接字
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "udpsendsocket.h"


/**
 * @brief 构造函数
 * @param parent
 */
UdpSendSocket::UdpSendSocket(QObject *parent) : BaseThread(parent)
{    
    isRun=false;
    mUdpSocket = NULL;
}

UdpSendSocket::~UdpSendSocket()
{
    isRun=false;
    wait();

    delete mUdpSocket;
}

/**
 * @brief 初始化套接字
 * @return 端口号
 */
bool UdpSendSocket::initSocket(int port)
{
    // mlogs->init();
    mUdpSocket = new QUdpSocket(this);
    bool ret = mUdpSocket->bind(QHostAddress::AnyIPv4, port);
    if(ret) {
        connect(mUdpSocket,SIGNAL(readyRead()),this,SLOT(dataReceivedSlot())); // 数据接收
        // start(); // 启动接收线程
    } else
        qDebug() << "udp socket create err" << port;

    return ret;
}

bool UdpSendSocket::dataReceivedSlot(void)
{
    // sProgress *mPro = sDataPacket::bulid()->getPro();
    mRet = false;
    int ret = 0;
    // int cnt = 1;
    mPacket = sDataPacket::bulid();
    mPacket->init();
    QString str = "接收成功";
    while(mUdpSocket->hasPendingDatagrams()) // 是否有数据可读
    {
        QByteArray data;
        data.resize(mUdpSocket->pendingDatagramSize());
        mUdpSocket->readDatagram(data.data() , data.size());
        qDebug()<<" readDatagram  "<<data;
        if(data.size()) {
            mRet = true;
            if(QString::compare(data,"1")==0)//接收成功
            {
                qDebug() << "1-----udp socket create err";

                ret = 1;
                str = "接收成功";
            }
            else{   //未接收到
                qDebug() << "2-----udp socket create err";
                ret = 0;
                dataSend();
                // cnt++;
                str = "接收失败";
            }
            qDebug() << "2-----udp socket create err";
           updatePro(str, ret);
            qDebug() << "3-----udp socket create err";
        }
    }

    return mRet;
}
/**
 * @brief 读取socket数据
 * @return
 */
int UdpSendSocket::dataSend(void)
{   
    QJsonObject obj;
    QByteArray ba;
    Json_Pack::bulid()->getJson(obj , ba);
    int ret = mUdpSocket->writeDatagram(ba , QHostAddress::LocalHost , 20011);
    qDebug() << "4-----udp socket create err";
    // if(ret > 0) mUdpSocket->flush(); msleep(100);
    mUdpSocket->flush();
    for(int i = 0 ; i < 10 ; i++){
        sleep(1);
        if( mRet ) {
            ret = 1;
            break;
        }
        else ret = 0;
    }
    qDebug() << "5-----udp socket create err";
    mRet = false;
    return ret;
}
