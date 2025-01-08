#include "editpassword.h"
#include "ui_editpassword.h"
#include <QMessageBox>   // 用于消息框
#include <QSqlQuery>
editpassword::editpassword(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::editpassword)
{
    ui->setupUi(this);
}

editpassword::~editpassword()
{
    delete ui;
}

void editpassword::on_btnconfirm_clicked()
{
    QString inputAccount = ui->inputUserName->text().trimmed(); // 输入账号
    QString newPassword = ui->inputUserPassword->text().trimmed();
    QString confirmPassword = ui->confirmpassword->text().trimmed();

    // 检查输入是否为空
    if (inputAccount.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "输入错误",
                             "<font size='10px' color='white'>请输入完整的账号和密码！</font>");
        return;
    }

    // 检查两次密码是否一致
    if (newPassword != confirmPassword) {
        QMessageBox::warning(this, "密码错误", "<font size='10px' color='white'>两次输入的密码不一致！</font>");
        return;
    }

    QSqlQuery query;
    QString epid;

    // 先从 user 表中查找 EPID
    query.prepare("SELECT EPID FROM user WHERE EPID = :epid");
    query.bindValue(":epid", inputAccount);
    if (query.exec() && query.first()) {
        // 在 user 表中找到，直接使用 EPID
        epid = query.value("EPID").toString();
    } else {
        // 如果没找到，再从 Doctor 表中查找 EMPLOYEE_NO
        query.prepare("SELECT EMPLOYEE_NO FROM Doctor WHERE PHONENUMBER = :phone");
        query.bindValue(":phone", inputAccount);
        if (query.exec() && query.first()) {
            // 在 Doctor 表中找到对应的 EMPLOYEE_NO
            epid = query.value("EMPLOYEE_NO").toString();
        } else {
            // 如果两个表都找不到，说明用户不存在
            QMessageBox::warning(this, "用户不存在",
                                 "<font size='10px' color='white'>未找到该用户，请检查账号！</font>");
            return;
        }
    }

    // 在 user 表中更新密码
    query.prepare("UPDATE user SET PASSWORD = :newPassword WHERE EPID = :epid");
    query.bindValue(":newPassword", newPassword);
    query.bindValue(":epid", epid);
    if (query.exec()) {
        QMessageBox::information(this, "修改成功", "<font size='10px' color='white'>密码已成功修改！</font>");
    } else {
        QMessageBox::critical(this, "修改失败",
                              "<font size='10px' color='white'>修改密码时发生错误，请稍后重试！</font>");
    }
    emit goPerviousView();
}


