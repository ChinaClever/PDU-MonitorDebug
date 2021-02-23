#ifndef HOME_MAINWID_H
#define HOME_MAINWID_H

#include <QWidget>
#include "set_workwid.h"

namespace Ui {
class Set_MainWid;
}

class Set_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit Set_MainWid(QWidget *parent = nullptr);
    ~Set_MainWid();

signals:
    void startSig();

protected:
    void initWid();

private:
    Ui::Set_MainWid *ui;
    Set_IpWid *mIpWid;
    Set_SiWid *mSiWid;
    Set_WorkWid *mWorkWid;
};

#endif // HOME_MAINWID_H
