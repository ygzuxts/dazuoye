#include "recordeditview.h"
#include "ui_recordeditview.h"
#include<QSqlTableModel>
#include"idatabase.h"
Recordeditview::Recordeditview(QWidget *parent, int index )
    : QWidget(parent)
    , ui(new Ui::Recordeditview)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().recordTabModel;
    dataMapper->setModel(IDatabase::getInstance().recordTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditPaName, tabModel->fieldIndex("PATIENTNAME"));
    dataMapper->addMapping(ui->dbEditDoName, tabModel->fieldIndex("DOCTORNAME"));
    dataMapper->addMapping(ui->dbEditMedicine, tabModel->fieldIndex("MEDICINE"));
    dataMapper->addMapping(ui->dbEditRseult, tabModel->fieldIndex("RESULT"));
    dataMapper->addMapping(ui->dateEdit, tabModel->fieldIndex("DATE"));

    dataMapper->setCurrentIndex(index);
}

Recordeditview::~Recordeditview()
{
    delete ui;
}

void Recordeditview::on_btnsave_4_clicked()
{
    IDatabase::getInstance().subitrecordEdit();
    emit goPerviousView();
}


void Recordeditview::on_btncancel_4_clicked()
{
    IDatabase::getInstance().revertrecordEdit();

    emit goPerviousView();
}

