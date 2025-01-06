#include "medicineeditview.h"
#include "ui_medicineeditview.h"
#include<QSqlTableModel>
#include"idatabase.h"
medicineeditview::medicineeditview(QWidget *parent, int index )
    : QWidget(parent)
    , ui(new Ui::medicineeditview)
{
    ui->setupUi(this);
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().medicineTabModel;
    dataMapper->setModel(IDatabase::getInstance().medicineTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditDose, tabModel->fieldIndex("DOSE"));
    dataMapper->addMapping(ui->dbEditInventory, tabModel->fieldIndex("INVENTORY"));

    dataMapper->setCurrentIndex(index);
}

medicineeditview::~medicineeditview()
{
    delete ui;
}

void medicineeditview::on_btnsave_4_clicked()
{
    IDatabase::getInstance().subitmedicineEdit();
    emit goPerviousView();
}


void medicineeditview::on_btncancel_4_clicked()
{
    IDatabase::getInstance().revertmedicineEdit();

    emit goPerviousView();
}

