#ifndef TEST_LOGS_H
#define TEST_LOGS_H

#include "dbstates.h"
#include "baseobject.h"
#include "sn_serialnum.h"

class Test_Logs : public BaseThread
{
    Q_OBJECT
    explicit Test_Logs(QObject *parent = nullptr);
public:
    static Test_Logs *bulid(QObject *parent = nullptr);

    void saveLogs();
    void writeMac(const QString &mac){mMac=mac;}
    bool updatePro(const QString &str, bool pass=true, int sec=1);

protected:
    bool initItem(sStateItem &item);
    bool writeLog();
    void writeLogs();
    bool writeMac();
    bool appendLogItem(const QString &str, bool pass);

private:
    QString mMac;
    QList<sStateItem> mLogItems;
};

#endif // TEST_LOGS_H
