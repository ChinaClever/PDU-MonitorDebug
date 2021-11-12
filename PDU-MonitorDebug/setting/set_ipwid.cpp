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
    groupBox_background_icon(this);
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
    int v = dt->ip_version-1; if(v) v = v - 1;
    ui->ipTypeBox->setCurrentIndex(v);
    on_ipTypeBox_currentIndexChanged(v);

    ui->lcdBox->setCurrentIndex(dt->ip_lcd);
    ui->logBox->setCurrentIndex(dt->log_en);
    ui->sBox->setCurrentIndex(dt->ip_standard);
    ui->lineBox->setCurrentIndex(dt->ip_lines);
    ui->ipModeBox->setCurrentIndex(dt->ip_modbus);
    ui->securityBox->setCurrentIndex(dt->security);
    ui->languageBox->setCurrentIndex(dt->ip_language);
    if(dt->ip_lines) dt->ip_ac = AC; else dt->ip_ac = DC;
    ui->InFirst->setText(dt->ip_inFirst);
    ui->InSecond->setText(dt->ip_inSecond);
    ui->OutFirst->setText(dt->ip_outFirst);
    ui->OutSecond->setText(dt->ip_outSecond);
}


void Set_IpWid::updateType()
{
    sTypeCfg *dt = &(mDev->cfg); //设备类型
    int v = ui->ipTypeBox->currentIndex()+1;
    if(v > 1) v = v + 1; dt->ip_version = v;

    dt->ip_lcd = ui->lcdBox->currentIndex();
    dt->ip_lines = ui->lineBox->currentIndex();
    dt->ip_modbus = ui->ipModeBox->currentIndex();
    dt->ip_standard = ui->sBox->currentIndex();
    dt->log_en = ui->logBox->currentIndex();
    dt->security = ui->securityBox->currentIndex();
    dt->ip_language = ui->languageBox->currentIndex();
    if(dt->ip_lines) dt->ip_ac = AC; else dt->ip_ac = DC;
    dt->ip_inFirst = ui->InFirst->text();
    dt->ip_inSecond = ui->InSecond->text();
    dt->ip_outFirst = ui->OutFirst->text();
    dt->ip_outSecond = ui->OutSecond->text();

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
    if(index == IP_PDUV3_EATON - 2)  res = false;
    ui->label->setHidden(res);
    ui->InFirst->setHidden(res);
    ui->InSecond->setHidden(res);
    ui->label_5->setHidden(res);
    ui->OutFirst->setHidden(res);
    ui->OutSecond->setHidden(res);

    res = true;
    if(index <= IP_PDUV3 - 2 || index == IP_PDUV3_EATON - 2)  res = false;
    ui->label_9->setHidden(res);
    ui->lcdBox->setHidden(res);


    res = false;
    if(index >= IP_PDUV3_C3 - 2)  res = true;
    ui->label_4->setHidden(res);
    ui->securityBox->setHidden(res);
    ui->label_8->setHidden(res);
    ui->sBox->setHidden(res);
    ui->label_3->setHidden(res);
    ui->ipModeBox->setHidden(res);
    ui->label_11->setHidden(res);
    ui->logBox->setHidden(res);

    res = true;
    if(index == IP_PDUV3 - 2)  res = false;
    ui->sBox->setHidden(res);
    ui->logBox->setHidden(res);
    ui->label_8->setHidden(res);
    ui->label_11->setHidden(res);
}
