#ifndef HOME_WORKWID_H
#define HOME_WORKWID_H

#include "set_ipwid.h"

namespace Ui {
class Set_WorkWid;
}

class Set_WorkWid : public QWidget
{
    Q_OBJECT

public:
    explicit Set_WorkWid(QWidget *parent = nullptr);
    ~Set_WorkWid();


signals:
    void typeSig(int i);
    void enabledSig(bool en);

private slots:
    //void timeoutDone();
    //void initFunSlot();
    void saveFunSlot();
    void saveErrSlot();
    void on_setBtn_clicked();
    void on_typeComboBox_currentIndexChanged(int index);

public slots:
    void errSlot() {QTimer::singleShot(5,this,SLOT(saveErrSlot()));}

private:
    Ui::Set_WorkWid *ui;

    int mId, mCnt;
    QTimer *timer;
    sProgress *mPro;
    sCfgItem *mItem;
    sDataPacket *mPacket;
};

#endif // HOME_WORKWID_H
