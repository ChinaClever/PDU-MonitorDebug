#include "set_workwid.h"
#include "ui_set_workwid.h"

Set_WorkWid::Set_WorkWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set_WorkWid)
{
    ui->setupUi(this);
     mCnt = 0;
}

Set_WorkWid::~Set_WorkWid()
{
    delete ui;
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
//    ui->cntSpin->setEnabled(en);
//    ui->userEdit->setEnabled(en);
//    ui->startBtn->setDisabled(en);
    ui->typeComboBox->setDisabled(en);
//    mItem->cnt.cnt = ui->cntSpin->value();
//    if(mItem->user != ui->userEdit->text()) {
//        mItem->user = ui->userEdit->text();
//        sCount *cnt = &(mItem->cnt);
//        cnt->all = cnt->ok = cnt->err = 0;
//        Cfg::bulid()->writeCnt();
//    }

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
//    mItem->modeId = index;
//    initTypeComboBox();
//    Cfg::bulid()->writeCfgDev();
}
