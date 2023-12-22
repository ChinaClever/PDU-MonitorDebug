#ifndef HOME_WORKWID_H
#define HOME_WORKWID_H

#include <QWidget>
#include "td_mainwid.h"
#include "test_corethread.h"
#include "udpsendsocket.h"///test//////////////////////////////////


namespace Ui {
class Home_WorkWid;
}

class Home_WorkWid : public QWidget, public BaseObject
{
    Q_OBJECT

public:
    explicit Home_WorkWid(QWidget *parent = nullptr);
    ~Home_WorkWid();

protected:
    void initLayout();
    void setTextColor();

    QString getTime();
    void updateWid();
    void updateTime();
    void updateResult();
    void updateCnt();

    bool initSerial();
    bool initWid();
    void insertText();

private slots:
    void timeoutDone();
    void initFunSlot();
    void on_startBtn_clicked();
    void on_upBtn_clicked();
    void on_downBtn_clicked();
    void insertTextSlot(QString  str , bool ret);
private:
    Ui::Home_WorkWid *ui;

    int mId;
    bool isCheck;
    QTimer *timer;
    Test_CoreThread *mCoreThread;
    UdpSendSocket *mSendUdp;///test//////////////////////////////////
};

#endif // HOME_WORKWID_H
