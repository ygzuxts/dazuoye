#include "masterview.h"
#include "ui_masterview.h"
#include<Qdebug>
#include <QMessageBox>

#include"idatabase.h"
MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);
    goLoginView();

    IDatabase::getInstance();

}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    qDebug() << "gologinview";
    loginView = new LoginView(this);
    pushWidgetToStackView(loginView);
    connect(loginView, &LoginView::loginSuccess, this, [this](int level) {
        goWelcomView(level); // 跳转到 WelcomeView，并传递权限等级
    });
    connect(loginView, SIGNAL(goeditpassword()), this, SLOT(goeditpassword()));
}
void MasterView::goeditpassword()
{
    qDebug() << "goeditpassword";
    Editpassword = new editpassword(this);
    pushWidgetToStackView(Editpassword);
    connect(Editpassword, SIGNAL(goPerviousView()), this, SLOT(goPreviousView()));
}
void MasterView::goWelcomView(int level)
{
    qDebug() << "goWelcomView";
    welcomeView = new WelcomeView(this);
    welcomeView->setUserLevel(level);
    pushWidgetToStackView(welcomeView);
    connect(welcomeView, SIGNAL(Doctor()), this, SLOT(goDoctorView()));
    connect(welcomeView, SIGNAL(medicine()), this, SLOT(gomedicineView()));
    connect(welcomeView, SIGNAL(Patient()), this, SLOT(goPatientView()));
    connect(welcomeView, SIGNAL(Record()), this, SLOT(gorecord()));
}

void MasterView::goDoctorView()
{
    qDebug() << "goDoctorView";
    doctorView = new DoctorView(this);
    pushWidgetToStackView(doctorView);
    connect(doctorView, SIGNAL(godoctorEditView(int)), this, SLOT(godoctorEditView(int)));
}

void MasterView::gomedicineView()
{
    qDebug() << "gomedicineView";
    m_medicineView = new MedicineView(this);
    pushWidgetToStackView(m_medicineView);
    connect(m_medicineView, SIGNAL(gomedicineEditView(int)), this, SLOT(gomedicineEditView(int)));
}
void MasterView::gomedicineEditView(int rowNo)
{
    qDebug() << "gomedicineEditView";
    Medicineeditview = new medicineeditview(this, rowNo);
    pushWidgetToStackView(Medicineeditview);
    connect(Medicineeditview, SIGNAL(goPerviousView()), this, SLOT(goPreviousView()));
}

void MasterView::gorecord()
{
    qDebug() << "gorecord";
    record = new ReCord(this);
    pushWidgetToStackView(record);
    connect(record, SIGNAL(gorecordEditView(int)), this, SLOT(gorecordEditView(int)));
}
void MasterView::gorecordEditView(int rowNo)
{
    qDebug() << "gorecordEditView";
    recordeditview = new Recordeditview(this, rowNo);
    pushWidgetToStackView(recordeditview);
    connect(recordeditview, SIGNAL(goPerviousView()), this, SLOT(goPreviousView()));
}


void MasterView::goPatientView()
{
    qDebug() << "goPatientView";
    patientView = new PatientView(this);
    pushWidgetToStackView(patientView);
    connect(patientView, SIGNAL(goPatientEditView(int)), this, SLOT(goPatientEditView(int)));
}

void MasterView::goPatientEditView(int rowNo)
{
    qDebug() << "goPatientEditView";
    patientEditView = new PatientEditView(this, rowNo);
    pushWidgetToStackView(patientEditView);
    connect(patientEditView, SIGNAL(goPerviousView()), this, SLOT(goPreviousView()));
}

void MasterView::godoctorEditView(int rowNo)
{
    qDebug() << "godoctoreditview";
    m_doctoreditview = new doctoreditview(this, rowNo);
    pushWidgetToStackView(m_doctoreditview);
    connect(m_doctoreditview, SIGNAL(goPerviousView()), this, SLOT(goPreviousView()));
}


void MasterView::goPreviousView()
{
    int count = ui->stackedWidget->count();
    if (count > 1) {
        ui->stackedWidget->setCurrentIndex(count - 2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());
        QWidget *widget = ui->stackedWidget->widget(count - 1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }

}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1);
    ui->labelTitle->setText(widget->windowTitle());
}

void MasterView::on_btBack_clicked()
{
    goPreviousView();

}


void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count = ui->stackedWidget->count();
    if (count > 1) {
        ui->btBack->setEnabled(true);
    } else {
        ui->btBack->setEnabled(false);
    }
    QString title = ui->stackedWidget->currentWidget()->windowTitle();
    if (title == "欢迎") {
        ui->btLogout->setEnabled(true);
        ui->btBack->setEnabled(false);

    } else {
        ui->btLogout->setEnabled(false);
    }
}


void MasterView::on_btLogout_clicked()
{
    goPreviousView();

}

