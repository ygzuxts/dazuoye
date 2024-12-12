#include "patienteditview.h"
#include "ui_patienteditview.h"
#include<QSqlTableModel>
#include"idatabase.h"
PatientEditView::PatientEditView(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().patientTabModel;
    dataMapper->setModel(IDatabase::getInstance().patientTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditIDCard, tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->dbSpinHeight, tabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->dbSpinWeight, tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->dbEditMoblie, tabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->dbdateEditDOB, tabModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->dbComboSex, tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dbCreatedTimeStamp, tabModel->fieldIndex("CREATEDTIMESTAMP"));
    dataMapper->setCurrentIndex(index);


}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_btncancel_clicked()
{
    IDatabase::getInstance().revertPatientEdit();
    emit goPerviousView();
}


void PatientEditView::on_btnsave_clicked()
{
    IDatabase::getInstance().subitPatientEdit();

    emit goPerviousView();
}

