#include "welcomeview.h"
#include "ui_welcomeview.h"
#include<QDebug>
#include"idatabase.h"
#include <QFileDialog>   // 用于文件选择对话框

#include <QTextStream>   // 用于文件流操作
#include <QSqlRecord>    // 用于操作数据库记录
#include <QUuid>         // 用于生成唯一标识符

WelcomeView::WelcomeView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeView)
{
    qDebug() << "creat WelcomView";
    ui->setupUi(this);
    IDatabase &db = IDatabase::getInstance();
    connect(&db, SIGNAL(loginSuccessful(int)), this, SLOT(handleLogin(int)));
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

void WelcomeView::setUserLevel(int level)
{
    qDebug() << "User Level in WelcomeView:" << level;

    if (level == 1) {
        ui->btPatient->hide();
        ui->btDoctor->hide();
        ui->btMedicine->hide();
    } else if (level == 2) {
        ui->btDoctor->hide();
        ui->btPatient->show();
        ui->btMedicine->show();
    } else if (level == 3) {
        ui->btPatient->show();
        ui->btDoctor->show();
        ui->btMedicine->show();
    }
}


