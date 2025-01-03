#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include<QSqlTableModel>
#include"idatabase.h"
doctoreditview::doctoreditview(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::doctoreditview)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().doctorTabModel;
    dataMapper->setModel(IDatabase::getInstance().doctorTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditDepartmentno, tabModel->fieldIndex("DEPARTMENT_ID"));
    dataMapper->addMapping(ui->dbEditemployeeno, tabModel->fieldIndex("EMPLOYEE_NO"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditcertificate, tabModel->fieldIndex("CERTIFICATE"));
    //dataMapper->addMapping(ui->dbEditMoblie, tabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->dbdateEditDOB, tabModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->dbComboSex, tabModel->fieldIndex("SEX"));
    // dataMapper->addMapping(ui->dbCreatedTimeStamp, tabModel->fieldIndex("CREATEDTIMESTAMP"));
    dataMapper->setCurrentIndex(index);
}

doctoreditview::~doctoreditview()
{
    delete ui;
}

void doctoreditview::on_btnsave_4_clicked()
{
    IDatabase::getInstance().subitdoctorEdit();
    emit goPerviousView();
}


void doctoreditview::on_btncancel_4_clicked()
{
    IDatabase::getInstance().revertdoctorEdit();

    emit goPerviousView();
}

