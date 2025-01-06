#include "welcomeview.h"
#include "ui_welcomeview.h"
#include<QDebug>
WelcomeView::WelcomeView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeView)
{
    qDebug() << "creat WelcomView";
    ui->setupUi(this);
}

WelcomeView::~WelcomeView()
{
    qDebug() << "destory WelcomView";
    delete ui;
}



void WelcomeView::on_btDoctor_clicked()
{
    emit Doctor();
}


void WelcomeView::on_btDepartment_clicked()
{
    emit Department();
}


void WelcomeView::on_btPatient_clicked()
{
    emit Patient();
}


void WelcomeView::on_btMedicine_clicked()
{
    emit medicine();
}


void WelcomeView::on_btRecord_clicked()
{
    emit Record();
}

