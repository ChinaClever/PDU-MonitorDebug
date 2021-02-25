/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "test_network.h"

Test_NetWork::Test_NetWork(QObject *parent) : BaseThread(parent)
{

}

Test_NetWork *Test_NetWork::bulid(QObject *parent)
{
    static Test_NetWork* sington = nullptr;
    if(sington == nullptr)
        sington = new Test_NetWork(parent);
    return sington;
}

void Test_NetWork::initFunSlot()
{    
    mProcess = new QProcess(this);
    mLogs = Test_Logs::bulid(this);
    mUdp = new UdpRecvSocket(this);
    mUdp->initSocket(10086);
    this->start();
}

bool Test_NetWork::checkNet()
{
    QString str = tr("检测设备网络");
    bool ret = cm_pingNet("192.168.1.163");
    if(ret) str += tr("正常"); else str += tr("错误");

    return updatePro(str, ret);
}

bool Test_NetWork::startProcess()
{
    QString exe = "pyweb_ctrlset_";
    if(MPDU == mItem->modeId) {
        exe += "mpdu.exe";
    } else exe += "ip.exe";

    mac = true;
    bool ret = checkNet();
    if(ret) {
        mProcess->start(exe);
        ret = mProcess->waitForFinished(120*1000);
        if(mac) updateMacAddr();
    }
    mProcess->close();

    return updatePro(tr("网页设置功能退出"), ret);
}


void Test_NetWork::updateMacAddr()
{
    if(mItem->mac.size() > 5) {
        mLogs->writeMac(mItem->mac);
        MacAddr *mac = MacAddr::bulid();
        mItem->mac = mac->macAdd(mItem->mac);
    }
}

void Test_NetWork::workDown()
{
    UdpBaseData *res = mUdp->getData();
    if(res) {
        QStringList list = QString(res->datagram).split(";");
        if(list.size() == 2) {
            QString str = list.first();
            bool pass = list.last().toInt();
            mLogs->updatePro(str, pass, 0);
        } else {
            if(QString(res->datagram).contains("MAC-1")) mac = false; else
                qDebug() <<"Test_NetWork workDown err" << list.size();
        }
        delete res;
    } else {
        msleep(1);
    }
}

void Test_NetWork::run()
{
    isRun = true;
    while (isRun) {
        workDown();
    }
}
