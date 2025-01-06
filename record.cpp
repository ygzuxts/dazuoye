#include "record.h"
#include "ui_record.h"
#include"idatabase.h"
#include <QFileDialog>   // 用于文件选择对话框
#include <QMessageBox>   // 用于消息框
#include <QTextStream>   // 用于文件流操作
#include <QSqlRecord>    // 用于操作数据库记录
#include <QUuid>         // 用于生成唯一标识符

ReCord::ReCord(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReCord)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);       // 设置为按行选择
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);      // 设置为单选模式
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);        // 禁止编辑
    ui->tableView->setAlternatingRowColors(true);                             // 交替行颜色


    IDatabase &iDatabase = IDatabase::getInstance();
    connect(&iDatabase, &IDatabase::pageInfoUpdated, this, &ReCord::updatePageInfo);
    if (iDatabase.initrecordModel()) {
        ui->tableView->setModel(iDatabase.recordTabModel);
        ui->tableView->setSelectionModel(iDatabase.therecordSelection);
        iDatabase.recordTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    }
}

ReCord::~ReCord()
{
    delete ui;
}

void ReCord::on_btSearch_clicked()
{
    QString filter = QString("ID like '%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchrecord(filter);
}


void ReCord::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewrecord();
    emit gorecordEditView(currow);
}


void ReCord::on_btDelet_clicked()
{
    IDatabase::getInstance().deleteCurrentrecord();
}


void ReCord::on_btEdit_clicked()
{
    QModelIndex curIndex =
        IDatabase::getInstance().therecordSelection->currentIndex();
    emit gorecordEditView(curIndex.row());
}


void ReCord::on_btImport_clicked()
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
    QSqlTableModel *model = iDatabase.recordTabModel;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() < 6) {
            qDebug() << "Invalid line: Not enough fields -" << line;
            continue; // 确保有足够的字段
        }

        // 插入新行
        int row = model->rowCount();
        model->insertRow(row);

        QSqlRecord record = model->record();
        record.setValue("ID", fields[0].trimmed());                 // 保留原始 ID
        record.setValue("PATIENTNAME", fields[1].trimmed());
        record.setValue("DOCTORNAME", fields[2].trimmed());
        record.setValue("RESULT", fields[3].trimmed());
        record.setValue("MEDICINE", fields[4].trimmed());
        record.setValue("DATE", fields[5].trimmed());
        // 级别转换为整数

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


void ReCord::on_btExport_clicked()
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
        QString line = QString("%1,%2,%3,%4,%5,%6")
                       .arg(record.value("ID").toString())
                       .arg(record.value("PATIENTNAME").toString())
                       .arg(record.value("DOCTORNAME").toString())
                       .arg(record.value("RESULT").toString())
                       .arg(record.value("MEDICINE").toString())
                       .arg(record.value("DATE").toString());

        out << line << "\n";
    }

    file.close();
    QMessageBox::information(this, "完成", "批量导出成功！");
}


void ReCord::on_btnPrevious_clicked()
{
    if (!IDatabase::getInstance().previousPage3()) {
        ui->btnPrevious->setEnabled(false);
    }
    ui->btnPrevious->setEnabled(true);
}


void ReCord::on_btnNext_clicked()
{
    if (!IDatabase::getInstance().nextPage3()) {
        ui->btnNext->setEnabled(false);
    }
    ui->btnNext->setEnabled(true);
}

void ReCord::updatePageInfo(int currentPage, int totalPages)
{
    ui->lblPageInfo->setText(QString("当前页: %1 / 总页数: %2").arg(currentPage).arg(totalPages));
}

