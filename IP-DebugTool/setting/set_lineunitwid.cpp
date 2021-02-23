/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "set_lineunitwid.h"
#include "ui_set_lineunitwid.h"

Set_LineUnitWid::Set_LineUnitWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set_LineUnitWid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addWidget(this);
}

Set_LineUnitWid::~Set_LineUnitWid()
{
    delete ui;
}

void Set_LineUnitWid::init(sObjCfg *obj)
{
    mDev = obj;
    ui->curMinSpin->setValue(obj->cur.min);
    ui->curMaxSpin->setValue(obj->cur.max);
    ui->volMinSpin->setValue(obj->vol.min);
    ui->volMaxSpin->setValue(obj->vol.max);

    ui->temMinSpin->setValue(obj->tem.min);
    ui->temMaxSpin->setValue(obj->tem.max);
    ui->humMinSpin->setValue(obj->hum.min);
    ui->humMaxSpin->setValue(obj->hum.max);
}

void Set_LineUnitWid::updateData()
{
    sObjCfg *obj = mDev;
    obj->cur.min = ui->curMinSpin->value();
    obj->cur.max = ui->curMaxSpin->value();
    obj->vol.min = ui->volMinSpin->value();
    obj->vol.max = ui->volMaxSpin->value();

    obj->tem.min = ui->temMinSpin->value();
    obj->tem.max = ui->temMaxSpin->value();
    obj->hum.min = ui->humMinSpin->value();
    obj->hum.max = ui->humMaxSpin->value();
}
