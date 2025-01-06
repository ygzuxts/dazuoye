#include "medicineview.h"
#include "ui_medicineview.h"
#include"masterview.h"
#include"idatabase.h"
#include <QFileDialog>   // 用于文件选择对话框
#include <QMessageBox>   // 用于消息框
#include <QTextStream>   // 用于文件流操作
#include <QSqlRecord>    // 用于操作数据库记录
#include <QUuid>         // 用于生成唯一标识符
MedicineView::MedicineView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MedicineView)
{
    ui->setupUi(this);


    // 设置表格属性
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);       // 按行选择
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);      // 单选模式
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);        // 禁止编辑
    ui->tableView->setAlternatingRowColors(true);                             // 交替行颜色

    IDatabase &iDatabase = IDatabase::getInstance();
    bool connected = connect(&iDatabase, &IDatabase::inventoryWarning, this, &MedicineView::showInventoryWarning);
    connect(&iDatabase, &IDatabase::pageInfoUpdated, this, &MedicineView::updatePageInfo);
    qDebug() << "Signal-slot connection status:" << connected;
    // 初始化模型
    if (iDatabase.initmedicineModel()) {
        ui->tableView->setModel(iDatabase.medicineTabModel);
        ui->tableView->setSelectionModel(iDatabase.themedicineSelection);
        iDatabase.medicineTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    }

    // 连接信号槽


    // 连接库存警告信号槽



}




MedicineView::~MedicineView()
{
    qDebug() << "MedicineView destroyed";
    delete ui;
}

void MedicineView::on_btSearch_clicked()
{
    QString filter = QString("NAME like '%%1%'").arg(ui->txtSearch->text());
    IDatabase::getInstance().searchdoctor(filter);
}


void MedicineView::on_btAdd_clicked()
{
    int currow = IDatabase::getInstance().addNewmedicine();
    emit gomedicineEditView(currow);
}


void MedicineView::on_btDelet_clicked()
{
    IDatabase::getInstance().deleteCurrentmedicine();
}


void MedicineView::on_btEdit_clicked()
{
    QModelIndex curIndex =
        IDatabase::getInstance().themedicineSelection->currentIndex();
    emit gomedicineEditView(curIndex.row());
}


void MedicineView::on_btnPrevious_clicked()
{
    if (!IDatabase::getInstance().previousPage2()) {
        ui->btnPrevious->setEnabled(false);
    }
    ui->btnPrevious->setEnabled(true);
}


void MedicineView::on_btnNext_clicked()
{
    if (!IDatabase::getInstance().nextPage2()) {
        ui->btnNext->setEnabled(false);
    }
    ui->btnNext->setEnabled(true);
}


void MedicineView::on_btImport_clicked()
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
    QSqlTableModel *model = iDatabase.medicineTabModel;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() < 4) {
            qDebug() << "Invalid line: Not enough fields -" << line;
            continue; // 确保有足够的字段
        }

        // 插入新行
        int row = model->rowCount();
        model->insertRow(row);

        QSqlRecord record = model->record();
        record.setValue("ID", fields[0].trimmed());                 // 保留原始 ID
        record.setValue("NAME", fields[1].trimmed());
        record.setValue("DOSE", fields[2].trimmed());
        record.setValue("INVENTORY", fields[3].trimmed());
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


void MedicineView::on_btExport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "选择保存路径", "", "CSV 文件 (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法创建文件！");
        return;
    }

    QTextStream out(&file);
    QSqlTableModel *model = IDatabase::getInstance().medicineTabModel;

    // 写入表数据
    for (int i = 0; i < model->rowCount(); ++i) {
        QSqlRecord record = model->record(i);
        QString line = QString("%1,%2,%3,%4")
                       .arg(record.value("ID").toString())
                       .arg(record.value("NAME").toString())
                       .arg(record.value("DOSE").toString())
                       .arg(record.value("INVENTORY").toString());

        out << line << "\n";
    }

    file.close();
    QMessageBox::information(this, "完成", "批量导出成功！");
}
void MedicineView::updatePageInfo(int currentPage, int totalPages)
{
    ui->lblPageInfo->setText(QString("当前页: %1 / 总页数: %2").arg(currentPage).arg(totalPages));
}

void MedicineView::showInventoryWarning(const QList<QString> &lowInventoryItems)
{
    qDebug() << "showInventoryWarning triggered";

    QString message;
    for (const QString &item : lowInventoryItems) {
        message += item + "\n";
    }

    qDebug() << "Message to display:" << message; // 输出调试信息

    // 显示警告框
    QMessageBox::warning(this, "库存警告", "以下药品库存不足:\n" + message);
}
