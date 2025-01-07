#include "loginview.h"
#include "ui_loginview.h"
#include"idatabase.h"


LoginView::LoginView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_btSignin_clicked()
{
    QString status = IDatabase::getInstance().userLogin(ui->inputUserName->text(), ui->inputUserPassword->text());
    if (status == "Login ok") {
        int level = IDatabase::getInstance().getLastLoginLevel(); // 获取登录的权限等级
        emit loginSuccess(level); // 发出信号传递权限等级
    }
}


void LoginView::on_btEdit_clicked()
{
    emit goeditpassword();
}

