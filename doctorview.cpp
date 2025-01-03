#include "doctorview.h"
#include "ui_doctorview.h"
#include"idatabase.h"
#include <QFileDialog>   // 用于文件选择对话框
#include <QMessageBox>   // 用于消息框
#include <QTextStream>   // 用于文件流操作
#include <QSqlRecord>    // 用于操作数据库记录
#include <QUuid>         // 用于生成唯一标识符

DoctorView::DoctorView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DoctorView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);       // 设置为按行选择
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);      // 设置为单选模式
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);        // 禁止编辑
    ui->tableView->setAlternatingRowColors(true);                             // 交替行颜色


    IDatabase &iDatabase = IDatabase::getInstance();
    if (iDatabase.initdoctorModel()) {
        ui->tableView->setModel(iDatabase.doctorTabModel);
        ui->tableView->setSelectionModel(iDatabase.thedoctorSelection);
        iDatabase.doctorTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    }
}

DoctorView::~DoctorView()
{
    delete ui;
}

void DoctorView::on_btSearch_clicked()
{
    QString filter = QString("EMPLOYEE_NO like '%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchdoctor(filter);
}


void DoctorView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewdoctor();
    emit godoctorEditView(currow);
}


void DoctorView::on_btDelet_clicked()
{
    IDatabase::getInstance().deleteCurrentdoctor();
}


void DoctorView::on_btEdit_clicked()
{
    QModelIndex curIndex =
        IDatabase::getInstance().thedoctorSelection->currentIndex();
    emit godoctorEditView(curIndex.row());
}


void DoctorView::on_btImport_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择批量导入文件", "", "CSV 文件 (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开文件！");
        return;
    }

    QTextStream in(&file);
    IDatabase &iDatabase = IDatabase::getInstance();
    QSqlTableModel *model = iDatabase.doctorTabModel;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() < 8) {
            qDebug() << "Invalid line: Not enough fields -" << line;
            continue; // 确保有足够的字段
        }

        // 插入新行
        int row = model->rowCount();
        model->insertRow(row);

        QSqlRecord record = model->record();
        record.setValue("ID", fields[0].trimmed());                 // 保留原始 ID
        record.setValue("EMPLOYEE_NO", fields[1].trimmed());
        record.setValue("DEPARTMENT_ID", fields[2].trimmed());
        record.setValue("CERTIFICATE", fields[3].trimmed());
        record.setValue("NAME", fields[4].trimmed());
        record.setValue("SEX", fields[5].trimmed());
        record.setValue("DOB", fields[6].trimmed());
        record.setValue("LEVEL", fields[7].trimmed().toInt());      // 级别转换为整数

        if (!model->setRecord(row, record)) {
            qDebug() << "SetRecord error:" << model->lastError().text();
        }
    }


    // 提交所有更改
    if (model->submitAll()) {
        QMessageBox::information(this, "完成", "批量导入成功！");
    } else {
        qDebug() << "SubmitAll error:" << model->lastError().text();
        QMessageBox::warning(this, "错误", "提交数据失败: " + model->lastError().text());
    }

    file.close();
}

void DoctorView::on_btExport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "选择保存路径", "", "CSV 文件 (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法创建文件！");
        return;
    }

    QTextStream out(&file);
    QSqlTableModel *model = IDatabase::getInstance().doctorTabModel;

    // 写入表数据
    for (int i = 0; i < model->rowCount(); ++i) {
        QSqlRecord record = model->record(i);
        QString line = QString("%1,%2,%3,%4,%5,%6,%7,%8")
                       .arg(record.value("ID").toString())
                       .arg(record.value("EMPLOYEE_NO").toString())
                       .arg(record.value("DEPARTMENT_ID").toString())
                       .arg(record.value("CERTIFICATE").toString())
                       .arg(record.value("NAME").toString())
                       .arg(record.value("SEX").toString())
                       .arg(record.value("DOB").toString())
                       .arg(record.value("LEVEL").toInt());
        out << line << "\n";
    }

    file.close();
    QMessageBox::information(this, "完成", "批量导出成功！");
}










