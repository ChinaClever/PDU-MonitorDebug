#ifndef STANDARDSOURCE_H
#define STANDARDSOURCE_H

#include "baseobject.h"

class YC_StandSource : public BaseThread
{
    Q_OBJECT
protected:
    explicit YC_StandSource(QObject *parent = nullptr);
public:
    virtual bool powerOn(int v=60);  // 上电
    virtual void powerDown(); // 下电
    virtual bool powerReset(); //

    virtual bool setCur(int v, int sec=0)=0;
    virtual bool setVol(int v, int sec=0)=0;
    virtual bool handShake()=0;
    int acOrDc;

protected:
    virtual void initFun(){}
    bool write(QByteArray &array);
    bool setBaudRate(qint32 baudRate);
    virtual bool serialWrite(const QByteArray &array)=0;

protected slots:
    void initFunSlot();

protected:
    SerialPort *mSerial;
};

#endif // STANDARDSOURCE_H
