#ifndef DEV_IPSNMP_H
#define DEV_IPSNMP_H

#include "dev_sictrl.h"
#include "snmpclient.h"

class Dev_IpSnmp : public Object
{
    Q_OBJECT
    explicit Dev_IpSnmp(QObject *parent = nullptr);
public:
    static Dev_IpSnmp *bulid(QObject *parent = nullptr);
    bool readPduData();

protected:
    bool lineNumV3();
    bool devDataV3();
    bool devDataV1();
    int getItemByOid(const QString &oid, int id);

private:
    SnmpClient *mSnmp;
};

#endif // DEV_IPSNMP_H
