/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "set_ipwid.h"
#include "ui_set_ipwid.h"

Set_IpWid::Set_IpWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set_IpWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/back.jpg");
    mUnitWid = new Set_LineUnitWid(ui->groupBox);
    QTimer::singleShot(10,this,SLOT(initFunSlot()));
}

Set_IpWid::~Set_IpWid()
{
    delete ui;
}

void Set_IpWid::initFunSlot()
{
    this->setEnabled(false);
    mObj = Dev_IpCfg::bulid(this);
    mItem = Cfg::bulid()->item;
    mDev = mObj->getDev();
    mUnitWid->init(&(mDev->cfg.ip_cfg));
    initType();
}

void Set_IpWid::initType()
{
    sTypeCfg *dt = &(mDev->cfg); //设备类型
    int v = dt->ip_version-1; if(v) v = 1;
    ui->ipTypeBox->setCurrentIndex(v);
    on_ipTypeBox_currentIndexChanged(v);

    ui->logBox->setCurrentIndex(dt->log_en);
    ui->sBox->setCurrentIndex(dt->ip_standar);
    ui->lineBox->setCurrentIndex(dt->ip_lines);
    ui->ipModeBox->setCurrentIndex(dt->ip_modbus);
    ui->languageBox->setCurrentIndex(dt->ip_language);
}


void Set_IpWid::updateType()
{
    sTypeCfg *dt = &(mDev->cfg); //设备类型
    int v = ui->ipTypeBox->currentIndex()+1;
    if(v > 1) v = 3; dt->ip_version = v;

    dt->ip_lines = ui->lineBox->currentIndex();
    dt->ip_modbus = ui->ipModeBox->currentIndex();
    dt->ip_standar = ui->sBox->currentIndex();
    dt->log_en = ui->logBox->currentIndex();
    dt->ip_language = ui->languageBox->currentIndex();
}

bool Set_IpWid::inputCheck()
{


    return true;
}

bool Set_IpWid::dataSave()
{
    bool ret = inputCheck();
    if(ret) {
        updateType();
        mUnitWid->updateData();
    }

    return ret;
}

void Set_IpWid::enabledSlot(bool en)
{
    if(mItem->modeId != IP_PDU) return;

    this->setEnabled(en);
    if(!en) {
        en = dataSave();
        if(en) {
            mObj->save();
        } else {
            emit errSig();
        }
    }
}

void Set_IpWid::on_ipTypeBox_currentIndexChanged(int index)
{
    bool res = true;
    if(index)  res = false;

    ui->sBox->setHidden(res);
    ui->logBox->setHidden(res);
    ui->label_8->setHidden(res);
    ui->label_11->setHidden(res);
}
