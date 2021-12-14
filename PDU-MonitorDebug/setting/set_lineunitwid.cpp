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
    this->mIndex = 0;
}

Set_LineUnitWid::~Set_LineUnitWid()
{
    delete ui;
}

void Set_LineUnitWid::init(sObjCfg *obj , int index)
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

    ui->fanTemMinSpin->setValue(obj->fantem.min);
    ui->fanTemMaxSpin->setValue(obj->fantem.max);
    ui->PWMMaxSpin->setValue(obj->pwm.max);

    bool res = true;
    mIndex = index;
    if(index == 6){
        res = false;
    }
    else{
        res = true;
    }
    ui->fanTemMinSpin->setHidden(res);
    ui->fanTemMaxSpin->setHidden(res);
    ui->PWMMaxSpin->setHidden(res);
    ui->label->setHidden(res);
    ui->label_2->setHidden(res);
    ui->label_3->setHidden(res);

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
    if(mIndex == 6){
        obj->fantem.min = ui->fanTemMinSpin->value();
        obj->fantem.max = ui->fanTemMaxSpin->value();
        obj->pwm.max = ui->PWMMaxSpin->value();
    }
}

void Set_LineUnitWid::changeIndex(int index)
{
    mIndex = index;
    bool res = true;
    if(index == 6){
        res = false;
    }
    else{
        res = true;
    }
    ui->fanTemMinSpin->setHidden(res);
    ui->fanTemMaxSpin->setHidden(res);
    ui->PWMMaxSpin->setHidden(res);
    ui->label->setHidden(res);
    ui->label_2->setHidden(res);
    ui->label_3->setHidden(res);
}
