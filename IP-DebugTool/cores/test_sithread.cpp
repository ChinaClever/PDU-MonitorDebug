/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "test_sithread.h"

Test_SiThread::Test_SiThread(QObject *parent) : BaseThread(parent)
{

}

void Test_SiThread::initFunSlot()
{
    mRtu = Dev_SiRtu::bulid(this);
    mCtrl = Dev_SiCtrl::bulid(this);
    mLogs = Test_Logs::bulid(this);
    mDev = Dev_SiCfg::bulid(this)->getDev();
    mDt = &(mDev->dt);
}

Test_SiThread *Test_SiThread::bulid(QObject *parent)
{
    static Test_SiThread* sington = nullptr;
    if(sington == nullptr)
        sington = new Test_SiThread(parent);
    return sington;
}


bool Test_SiThread::curAlarmWrite(int i)
{
    QString str = tr("电流报警阈值 L%1 写入").arg(i+1);
    bool ret = mCtrl->setCurTh(i);
    if(ret) str += tr("正常");
    else str += tr("错误");

    return mLogs->updatePro(str, ret);
}

bool Test_SiThread::volAlarmWrite(int i)
{
    QString str = tr("电压报警阈值 L%1 写入").arg(i+1);
    bool ret = mCtrl->setVolTh(i);
    if(ret) str += tr("正常");
    else str += tr("错误");

    return mLogs->updatePro(str, ret);
}

bool Test_SiThread::envAlarmWrite()
{
    QString str = tr("温度报警阈值写入");
    bool ret = mCtrl->setTem();
    if(ret) str += tr("正常");
    else str += tr("错误");
    ret = mLogs->updatePro(str, ret);

    str = tr("湿度报警阈值写入");
    ret = mCtrl->setHum();
    if(ret) str += tr("正常");
    else str += tr("错误");
    return  mLogs->updatePro(str, ret);
}

bool Test_SiThread::writeAlarmTh()
{
    bool ret = true;
    int size = mDev->data.size;

    for(int i=0; i<size; ++i) {
        ret = curAlarmWrite(i); if(!ret) break;
        ret = volAlarmWrite(i); if(!ret) break;
    }

    return ret;
}

bool Test_SiThread::setAlarm()
{
    bool ret  = writeAlarmTh();
    if(ret) ret = envAlarmWrite();

    return ret;
}

bool Test_SiThread::clearEle()
{
    QString str = tr("清除设备电能");
    bool ret = mCtrl->factorySet();
    if(ret) {
        str += tr("正常");
    } else {
        str += tr("错误");
    }

    return  mLogs->updatePro(str, ret);
}

bool Test_SiThread::readDev()
{
    bool ret = true;
    QString str = tr("开始读取设备信息");
    for(int i=0; i<5; ++i) {
        ret = mRtu->readPduData(); if(ret) break;
        Rtu_Modbus::bulid(this)->get()->changeBaudRate();
    }
    if(ret) str += tr("正常"); else str += tr("错误");
    return  mLogs->updatePro(str, ret);
}

bool Test_SiThread::checkLine()
{
    bool ret = readDev();
    if(ret) {
        int line = 3;
        switch (mDev->dt.lines) {
        case 0:  line = 1; break;
        case 1: line = 1; break;
        case 2:  line = 3;  break;
        }

        if(line != mDev->data.size) {
            ret = false;
            mLogs->updatePro(tr("单相两路需先切换至“一路”，再切换到单相交流或者直流"), ret);
        }
    }

    return ret;
}

bool Test_SiThread::setData()
{
    QString str = tr("解锁设备");
    bool ret = mCtrl->unClock();
    if(ret) str += tr("成功"); else str += tr("错误");
    ret = mLogs->updatePro(str, ret);
    if(ret) {
        str = tr("设备配置信息写入");
        ret = mCtrl->setDev();
        if(ret) str += tr("正常"); else str += tr("错误");
        ret = mLogs->updatePro(str, ret);
    }

    return  ret;
}


bool Test_SiThread::setDev()
{
    bool ret = readDev();
    if(ret) ret = setData();
    if(ret) ret = setAlarm();
    if(ret) ret = clearEle();

   // if(ret) {
        // ret = checkLine();
     //   ret = setAlarm();
     //   if(ret) ret = clearEle();
   // }

    return ret;
}
