#include "masterview.h"
#include "ui_masterview.h"
#include<Qdebug>

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    goLoginView();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    qDebug() << "gologinview";
    loginView = new LoginView(this);
    ui->stackedWidget->addWidget(loginView);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1);
    ui->labelTitle->setText(loginView->windowTitle());
}

void MasterView::goWelcomView()
{
    qDebug() << "gologinview";
    welcomeView = new WelcomeView(this);
    ui->stackedWidget->addWidget(loginView);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1);
    ui->labelTitle->setText(loginView->windowTitle());
}

void MasterView::goDoctorView()
{

}

void MasterView::goDepartmentView()
{

}

void MasterView::goPatientView()
{

}

void MasterView::goPatientEditView()
{

}

void MasterView::goPreviousView()
{

}
