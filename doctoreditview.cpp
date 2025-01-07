#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include<QSqlTableModel>
#include"idatabase.h"
#include <QMessageBox>   // 用于消息框
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
    dataMapper->addMapping(ui->dblevel, tabModel->fieldIndex("LEVEL"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditcertificate, tabModel->fieldIndex("CERTIFICATE"));
    //dataMapper->addMapping(ui->dbEditMoblie, tabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->dbdateEditDOB, tabModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->dbComboSex, tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dbPhonenumber, tabModel->fieldIndex("PHONENUMBER"));
    // dataMapper->addMapping(ui->dbCreatedTimeStamp, tabModel->fieldIndex("CREATEDTIMESTAMP"));
    dataMapper->setCurrentIndex(index);
}

doctoreditview::~doctoreditview()
{
    delete ui;
}

void doctoreditview::on_btnsave_4_clicked()
{
    employeeNo = ui->dbEditemployeeno->text();
    qDebug() << employeeNo;
    if (IDatabase::getInstance().subitdoctorEdit()) {

        // 插入到 user 表
        if (!employeeNo.isEmpty()) {
            QSqlQuery query;
            query.prepare(R"(
                INSERT OR IGNORE INTO user (EPID, PASSWORD) VALUES (:EPID, :PASSWORD)
            )");
            query.bindValue(":EPID", employeeNo);
            query.bindValue(":PASSWORD", "123456");

            if (!query.exec()) {
                qDebug() << "Failed to insert into user table:" << query.lastError().text();
            } else {
                qDebug() << "Successfully added to user table: EPID =" << employeeNo;
            }

            // 给 Doctor 表插入默认 LEVEL = 1
            QSqlQuery doctorQuery;
            doctorQuery.prepare(R"(
                INSERT OR REPLACE INTO Doctor (EMPLOYEE_NO, LEVEL)
                VALUES (:EMPLOYEE_NO, 1)
            )");
            doctorQuery.bindValue(":EMPLOYEE_NO", employeeNo);

            if (!doctorQuery.exec()) {
                qDebug() << "Failed to insert into Doctor table:" << doctorQuery.lastError().text();
            } else {
                qDebug() << "Successfully added to Doctor table with LEVEL = 1 for EMPLOYEE_NO =" << employeeNo;
            }

        } else {
            qDebug() << "EMPLOYEE_NO is empty, skipping user table update.";
        }

        // 返回到上一个视图
        emit goPerviousView();
    } else {
        QMessageBox::warning(this, "外键约束", "员工号和电话号码不可重复");
    }
}



void doctoreditview::on_btncancel_4_clicked()
{
    IDatabase::getInstance().revertdoctorEdit();

    emit goPerviousView();
}

