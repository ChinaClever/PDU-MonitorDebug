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

    bool res = true , secondflag = true;
    mIndex = index;
    if(index == IP_PDUV1_YIXIN-2){
        res = false;secondflag = false;
        ui->fanTemMinSpin->setValue(obj->fantem.min);
        ui->fanTemMaxSpin->setValue(obj->fantem.max);
        ui->fanTemMinSpin->setSuffix("℃");
        ui->fanTemMaxSpin->setSuffix("℃");
        ui->label->setText(tr("风扇曲线温度："));
    }
    else if(index == IP_PDUV3_SHATE-2){
        res = true;secondflag = false;
        ui->fanTemMinSpin->setValue(obj->loopcur.min);
        ui->fanTemMaxSpin->setValue(obj->loopcur.max);
        ui->fanTemMinSpin->setSuffix("A");
        ui->fanTemMaxSpin->setSuffix("A");
        ui->label->setText(tr("回路电流："));
    }
    else{
        res = true;secondflag = true;
    }
    ui->fanTemMinSpin->setHidden(secondflag);
    ui->fanTemMaxSpin->setHidden(secondflag);
    ui->PWMMaxSpin->setHidden(res);
    ui->label->setHidden(secondflag);
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
    if(mIndex == IP_PDUV1_YIXIN-2){
        obj->fantem.min = ui->fanTemMinSpin->value();
        obj->fantem.max = ui->fanTemMaxSpin->value();
        obj->pwm.max = ui->PWMMaxSpin->value();
    }else if(mIndex == IP_PDUV3_SHATE-2){
        obj->loopcur.min = ui->fanTemMinSpin->value();
        obj->loopcur.max = ui->fanTemMaxSpin->value();
    }
}

void Set_LineUnitWid::changeIndex(int index)
{
    mIndex = index;
    bool res = true,secondflag = true;
    if(index == IP_PDUV1_YIXIN-2){
        res = false;secondflag = false;
        ui->fanTemMinSpin->setValue(mDev->fantem.min);
        ui->fanTemMaxSpin->setValue(mDev->fantem.max);
        ui->fanTemMinSpin->setSuffix("℃");
        ui->fanTemMaxSpin->setSuffix("℃");
        ui->label->setText(tr("风扇曲线温度："));
    }else if(index == IP_PDUV3_SHATE-2){
        res = true;secondflag = false;
        ui->fanTemMinSpin->setValue(mDev->loopcur.min);
        ui->fanTemMaxSpin->setValue(mDev->loopcur.max);
        ui->fanTemMinSpin->setSuffix("A");
        ui->fanTemMaxSpin->setSuffix("A");
        ui->label->setText(tr("回路电流："));
    }
    else{
        res = true;secondflag = true;
    }
    ui->fanTemMinSpin->setHidden(secondflag);
    ui->fanTemMaxSpin->setHidden(secondflag);
    ui->PWMMaxSpin->setHidden(res);
    ui->label->setHidden(secondflag);
    ui->label_2->setHidden(res);
    ui->label_3->setHidden(res);
}
