#include "set_workwid.h"
#include "ui_set_workwid.h"
#include "macaddr.h"

Set_WorkWid::Set_WorkWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set_WorkWid)
{
    ui->setupUi(this);
     QTimer::singleShot(450,this,SLOT(initFunSlot()));
}

Set_WorkWid::~Set_WorkWid()
{
    delete ui;
}

void Set_WorkWid::initFunSlot()
{
    mCnt = 0;
    initTypeComboBox();
    ui->userEdit->setText(mItem->user);
    ui->addrSpin->setValue(mItem->addr);
    ui->cntSpin->setValue(mItem->cnt.cnt);

    initMac();
    timer = new QTimer(this);
    timer->start(3*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
}


void Set_WorkWid::saveFunSlot()
{
    bool en = mCnt % 2;
    emit enabledSig(en);
    if(!en) Cfg::bulid()->writeCfgDev();
}

void Set_WorkWid::on_setBtn_clicked()
{
    QString str = tr("修改");
    bool en = ++mCnt % 2;
    if(en) str = tr("保存");

    ui->setBtn->setText(str);
    ui->cntSpin->setEnabled(en);
    ui->addrSpin->setEnabled(en);
    ui->userEdit->setEnabled(en);
    ui->typeComboBox->setDisabled(en);
    mItem->addr = ui->addrSpin->value();
    mItem->cnt.cnt = ui->cntSpin->value();
    if(mItem->user != ui->userEdit->text()) {
        mItem->user = ui->userEdit->text();
        sCount *cnt = &(mItem->cnt);
        cnt->all = cnt->ok = cnt->err = 0;
        Cfg::bulid()->writeCnt();
    }

    QTimer::singleShot(50,this,SLOT(saveFunSlot()));
}

void Set_WorkWid::saveErrSlot()
{
    mCnt = 1;
    emit enabledSig(true);
    ui->setBtn->setText(tr("保存"));
}


void Set_WorkWid::on_typeComboBox_currentIndexChanged(int index)
{
    mItem->modeId = index;
    initTypeComboBox();
    Cfg::bulid()->writeCfgDev();
}


void Set_WorkWid::initTypeComboBox()
{
    int index = mItem->modeId;
    emit typeSig(mItem->modeId);
    ui->typeComboBox->setCurrentIndex(index);
}


void Set_WorkWid::updateMac()
{
    int ret =  MacAddr::bulid()->macCnt(mItem->mac, mItem->endMac);
    ui->cntMacLab->setNum(ret);
}


void Set_WorkWid::initMac()
{   
    updateMac();
    ui->startMacLab->setText(mItem->startMac);
    ui->endMacLab->setText(mItem->endMac);
}


void Set_WorkWid::timeoutDone()
{
    updateMac();
}
