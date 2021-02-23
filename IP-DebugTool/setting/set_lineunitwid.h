#ifndef HOME_THUNITWID_H
#define HOME_THUNITWID_H

#include <QWidget>
#include "common.h"
#include "dev_ipcfg.h"

namespace Ui {
class Set_LineUnitWid;
}

class Set_LineUnitWid : public QWidget
{
    Q_OBJECT

public:
    explicit Set_LineUnitWid(QWidget *parent = nullptr);
    ~Set_LineUnitWid();

    void updateData();
    void init(sObjCfg *obj);

private:
    Ui::Set_LineUnitWid *ui;
    sObjCfg *mDev;
};

#endif // HOME_THUNITWID_H
