#ifndef DEV_OBJECT_H
#define DEV_OBJECT_H

#include "object.h"

class Dev_Object : public Object
{
    Q_OBJECT
public:
    explicit Dev_Object(QObject *parent = nullptr);
    sDevData *getDev() {return mDev;}

    virtual void save(){}
    virtual bool readPduData() {return true;}

protected:
    virtual QString cfgGroup(){return "siCfg";}
    void initUnit(const QString& prefix, sUnitCfg &unit, int f=0);
    void writeUnit(const QString& prefix, sUnitCfg &unit, int f=0);

    void write(const QString &key, const QVariant& v);
    QVariant read(const QString &key, const QVariant &v = QVariant());

    uchar *toInt(uchar *ptr, int line, uint *value);
    uchar *toChar(uchar *ptr, int line, uchar *value);
    uchar *toShort(uchar *ptr, int line, ushort *value);

    ushort getShort(uchar *ptr);
    uchar *getShort(uchar *ptr, int line, uchar *value);
    uchar *toOutputEle(uchar *ptr, int line, uint *value);
    uchar *toThreshold(uchar *ptr, int line, sDataUnit &unit);
    uchar *toEnvTh(uchar *ptr, sDataUnit &unit);
};

#endif // DEV_OBJECT_H
