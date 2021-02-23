/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "set_mainwid.h"
#include "ui_set_mainwid.h"

Set_MainWid::Set_MainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set_MainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    initWid();
}

Set_MainWid::~Set_MainWid()
{
    delete ui;
}


void Set_MainWid::initWid()
{
    ui->tabWidget->tabBar()->hide();
    mWorkWid = new Set_WorkWid(ui->workWid);
    connect(mWorkWid, SIGNAL(typeSig(int)), ui->tabWidget, SLOT(setCurrentIndex(int)));
   // connect(mWorkWid, SIGNAL(startSig()), this, SIGNAL(startSig()));

    mSiWid = new Set_SiWid(ui->tabWidget);
    ui->tabWidget->addTab(mSiWid, tr("SI-PDU参数设置"));
    connect(mSiWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mSiWid, SLOT(enabledSlot(bool)));

    mIpWid = new Set_IpWid(ui->tabWidget);
    ui->tabWidget->addTab(mIpWid, tr("IP-PDU参数设置"));
    connect(mIpWid, SIGNAL(errSig()), mWorkWid, SLOT(errSlot()));
    connect(mWorkWid, SIGNAL(enabledSig(bool)), mIpWid, SLOT(enabledSlot(bool)));
}
