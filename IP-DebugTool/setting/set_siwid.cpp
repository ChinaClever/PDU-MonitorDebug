/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "set_siwid.h"
#include "ui_set_siwid.h"

Set_SiWid::Set_SiWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set_SiWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    mUnitWid = new Set_LineUnitWid(ui->groupBox);
    QTimer::singleShot(13,this,SLOT(initFunSlot()));
}

Set_SiWid::~Set_SiWid()
{
    delete ui;
}


void Set_SiWid::initFunSlot()
{
    this->setEnabled(false);
    mObj = Dev_SiCfg::bulid(this);
    mItem = Cfg::bulid()->item;
    mDev = mObj->getDev();
    mUnitWid->init(&(mDev->cfg.si_cfg));
    initType();
}

void Set_SiWid::initType()
{
    sTypeCfg *cfg = &(mDev->cfg); //设备类型
    int v = cfg->si_lines;
    ui->lineBox->setCurrentIndex(v);
    ui->sBox->setCurrentIndex(cfg->si_standar);
    ui->curBox->setCurrentIndex(cfg->si_series);
}

void Set_SiWid::updateType()
{
    sTypeCfg *cfg = &(mDev->cfg);
    cfg->si_led = ui->ledCheck->isChecked()?1:0;
    cfg->si_lines = ui->lineBox->currentIndex();
    cfg->si_standar = ui->sBox->currentIndex();
    cfg->si_series = ui->curBox->currentIndex();
    if(cfg->si_lines) {
        cfg->si_ac = AC;
    } else {
        cfg->si_ac = DC;
    }
}

bool Set_SiWid::inputCheck()
{
    return true;
}

bool Set_SiWid::dataSave()
{
    bool ret = inputCheck();
    if(ret) {
        updateType();
        mUnitWid->updateData();
    }

    return ret;
}

void Set_SiWid::enabledSlot(bool en)
{
    if(mItem->modeId != SI_PDU) return;

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
