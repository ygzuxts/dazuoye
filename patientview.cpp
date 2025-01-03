#include "patientview.h"
#include "ui_patientview.h"
#include"idatabase.h"
#include <QFileDialog>   // 用于文件选择对话框
#include <QMessageBox>   // 用于消息框
#include <QTextStream>   // 用于文件流操作
#include <QSqlRecord>    // 用于操作数据库记录
#include <QUuid>         // 用于生成唯一标识符
PatientView::PatientView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);       // 设置为按行选择
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);      // 设置为单选模式
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);        // 禁止编辑
    ui->tableView->setAlternatingRowColors(true);                             // 交替行颜色


    IDatabase &iDatabase = IDatabase::getInstance();
    if (iDatabase.initPatientModel()) {
        ui->tableView->setModel(iDatabase.patientTabModel);
        ui->tableView->setSelectionModel(iDatabase.thePatientSelection);
    }
}

PatientView::~PatientView()
{
    delete ui;
}

void PatientView::on_btSearch_clicked()
{
    QString filter = QString("name like '%%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchPatient(filter);
}


void PatientView::on_btDelet_clicked()
{
    IDatabase::getInstance().deleteCurrentPatient();
}


void PatientView::on_btEdit_clicked()
{
    QModelIndex curIndex =
        IDatabase::getInstance().thePatientSelection->currentIndex();
    emit goPatientEditView(curIndex.row());
}


void PatientView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewPatient();
    emit goPatientEditView(currow);
}


void PatientView::on_btImport_clicked()
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
    QSqlTableModel *model = iDatabase.patientTabModel;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() < 10) {
            qDebug() << "Invalid line: Not enough fields -" << line;
            continue; // 确保有足够的字段
        }

        // 插入新行
        int row = model->rowCount();
        model->insertRow(row);

        QSqlRecord record = model->record();
        record.setValue("ID", fields[0].trimmed());                 // 保留原始 ID
        record.setValue("ID_CARD", fields[1].trimmed());
        record.setValue("NAME", fields[2].trimmed());
        record.setValue("SEX", fields[3].trimmed());         // 性别转换为整数
        record.setValue("DOB", fields[4].trimmed());
        record.setValue("HEIGHT", fields[5].trimmed().toDouble());  // 身高转换为浮点数
        record.setValue("WEIGHT", fields[6].trimmed().toDouble());  // 体重转换为浮点数
        record.setValue("MOBILEPHONE", fields[7].trimmed());
        record.setValue("AGE", fields[8].trimmed().toInt());        // 年龄转换为整数
        record.setValue("CREATEDTIMESTAMP", fields[9].trimmed());

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

void PatientView::on_btExport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "选择保存路径", "", "CSV 文件 (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法创建文件！");
        return;
    }

    QTextStream out(&file);
    QSqlTableModel *model = IDatabase::getInstance().patientTabModel;

    // 写入表数据
    for (int i = 0; i < model->rowCount(); ++i) {
        QSqlRecord record = model->record(i);
        QString line = QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10")
                       .arg(record.value("ID").toString())
                       .arg(record.value("ID_CARD").toString())
                       .arg(record.value("NAME").toString())
                       .arg(record.value("SEX").toString())
                       .arg(record.value("DOB").toString())
                       .arg(record.value("HEIGHT").toDouble())
                       .arg(record.value("WEIGHT").toDouble())
                       .arg(record.value("MOBILEPHONE").toString())
                       .arg(record.value("AGE").toInt())
                       .arg(record.value("CREATEDTIMESTAMP").toString());
        out << line << "\n";
    }

    file.close();
    QMessageBox::information(this, "完成", "批量导出成功！");
}


