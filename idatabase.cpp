#include "idatabase.h"
#include<QDebug>
#include<QUuid>
#include<QMessageBox>
QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;

    // 查询密码和权限
    query.prepare(R"(
    SELECT user.PASSWORD, Doctor.LEVEL
    FROM user
    LEFT JOIN Doctor ON user.EPID = Doctor.EMPLOYEE_NO
    WHERE user.EPID = :account OR Doctor.PHONENUMBER = :account
    )");
    query.bindValue(":account", userName); // `userName` 可能是 EPID 或 PHONENUMBER
    query.exec();

    if (query.first() && query.value("PASSWORD").isValid()) {
        QString passwd = query.value("PASSWORD").toString();
        if (passwd == password) {
            lastLoginLevel = query.value("LEVEL").toInt();

            // 显示登录成功的消息
            QMessageBox msgBox;
            msgBox.setStyleSheet("QLabel { font-size: 20px; color: white; } QPushButton { font-size: 12px; }");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setWindowTitle("登录成功");
            msgBox.setText("登录成功！");
            msgBox.exec();

            return "Login ok";
        } else {
            qDebug() << "Wrong password";

            // 显示密码错误的消息
            QMessageBox msgBox;
            msgBox.setStyleSheet("QLabel { font-size: 20px; color: white; } QPushButton { font-size: 12px; }");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("登录失败");
            msgBox.setText("密码错误，请重试！");
            msgBox.exec();

            return "Wrong Password";
        }
    } else {
        qDebug() << "No such user";

        // 显示用户不存在的消息
        QMessageBox msgBox;
        msgBox.setStyleSheet("QLabel { font-size: 20px; color: white; } QPushButton { font-size: 12px; }");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("登录失败");
        msgBox.setText("用户不存在，请检查账号！");
        msgBox.exec();

        return "Wrong Username";
    }

    // 如果到达这里，表示登录失败
    QMessageBox msgBox;
    msgBox.setStyleSheet("QLabel { font-size: 20px; color: white; } QPushButton { font-size: 12px; }");
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("登录失败");
    msgBox.setText("登录失败，请重试！");
    msgBox.exec();

    return "Failed";
}



bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();
    return true;
}






bool IDatabase::subitPatientEdit()
{
    return patientTabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    return patientTabModel->revertAll();
}

int IDatabase::addNewPatient()
{
    patientTabModel->insertRow(patientTabModel->rowCount(),
                               QModelIndex());
    QModelIndex curIndex = patientTabModel->index(patientTabModel->rowCount() - 1, 1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = patientTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));

    patientTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

bool IDatabase::searchdoctor(QString filter)
{
    doctorTabModel->setFilter(filter);
    return doctorTabModel->select();
}

bool IDatabase::deleteCurrentdoctor()
{
    QModelIndex curIndex = thedoctorSelection->currentIndex();
    doctorTabModel->removeRow(curIndex.row());
    doctorTabModel->submitAll();
    doctorTabModel->select();
    return true;
}

bool IDatabase::subitdoctorEdit()
{
    return doctorTabModel->submitAll();
}

void IDatabase::revertdoctorEdit()
{
    return doctorTabModel->revertAll();
}

int IDatabase::addNewdoctor()
{
    doctorTabModel->insertRow(doctorTabModel->rowCount(),
                              QModelIndex());
    QModelIndex curIndex = doctorTabModel->index(doctorTabModel->rowCount() - 1, 1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = doctorTabModel->record(curRecNo);
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));
    doctorTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

bool IDatabase::searchmedicine(QString filter)
{
    medicineTabModel->setFilter(filter);
    return medicineTabModel->select();
}

bool IDatabase::deleteCurrentmedicine()
{
    QModelIndex curIndex = themedicineSelection->currentIndex();
    medicineTabModel->removeRow(curIndex.row());
    medicineTabModel->submitAll();
    medicineTabModel->select();
    return true;
}

bool IDatabase::subitrecordEdit()
{
    return recordTabModel->submitAll();
}

void IDatabase::revertrecordEdit()
{
    return recordTabModel->revertAll();
}

int IDatabase::addNewrecord()
{
    recordTabModel->insertRow(recordTabModel->rowCount(),
                              QModelIndex());
    QModelIndex curIndex = recordTabModel->index(recordTabModel->rowCount() - 1, 1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = recordTabModel->record(curRecNo);
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));
    recordTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

bool IDatabase::searchrecord(QString filter)
{
    recordTabModel->setFilter(filter);
    return recordTabModel->select();
}

bool IDatabase::deleteCurrentrecord()
{
    QModelIndex curIndex = therecordSelection->currentIndex();
    recordTabModel->removeRow(curIndex.row());
    recordTabModel->submitAll();
    recordTabModel->select();
    return true;
}


bool IDatabase::subitmedicineEdit()
{
    return medicineTabModel->submitAll();
}

void IDatabase::revertmedicineEdit()
{
    return medicineTabModel->revertAll();
}

int IDatabase::addNewmedicine()
{
    medicineTabModel->insertRow(medicineTabModel->rowCount(),
                                QModelIndex());
    QModelIndex curIndex = medicineTabModel->index(medicineTabModel->rowCount() - 1, 1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = medicineTabModel->record(curRecNo);
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));

    medicineTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    ininDatabase();
}

void IDatabase::ininDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile = QCoreApplication::applicationDirPath() + "/LABd.db";
    database.setDatabaseName(aFile);

    if (!database.open()) {
        qDebug() << "failed to open database";

    } else
        qDebug() << "open database successfully";
}

bool IDatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this, database);
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    patientTabModel->setSort(patientTabModel->fieldIndex("name"), Qt::AscendingOrder);
    if (!(patientTabModel->select()))
        return false;
    thePatientSelection = new QItemSelectionModel(patientTabModel);
    currentPage = 0;
    pageSize = 10; // 每页10条
    return loadPatientPage();
}
bool IDatabase::loadPatientPage()
{
    QString filter = QString("ROWID >= %1 AND ROWID < %2")
                     .arg(currentPage * pageSize + 1)
                     .arg((currentPage + 1) * pageSize + 1);

    patientTabModel->setFilter(filter);

    if (!patientTabModel->select()) {
        qDebug() << "Failed to load patient page:" << patientTabModel->lastError().text();
        return false;
    }

    // 更新总记录数和总页数
    QSqlQuery query(database);
    if (query.exec("SELECT COUNT(*) FROM patient") && query.next()) {
        totalRecords = query.value(0).toInt();
        totalPages = (totalRecords + pageSize - 1) / pageSize; // 向上取整
    }

    emit pageInfoUpdated(currentPage + 1, totalPages); // 发射信号更新 UI
    return true;
}

bool IDatabase::initrecordModel()
{
    recordTabModel = new QSqlTableModel(this, database);
    recordTabModel->setTable("record");
    recordTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    recordTabModel->setSort(recordTabModel->fieldIndex("id"), Qt::AscendingOrder);
    if (!(recordTabModel->select()))
        return false;
    therecordSelection = new QItemSelectionModel(recordTabModel);
    currentPage = 0;
    pageSize = 10; // 每页10条
    return loadrecordPage();
}
bool IDatabase::loadrecordPage()
{
    QString filter = QString("ROWID >= %1 AND ROWID < %2")
                     .arg(currentPage * pageSize + 1)
                     .arg((currentPage + 1) * pageSize + 1);

    recordTabModel->setFilter(filter);

    if (!recordTabModel->select()) {
        qDebug() << "Failed to load patient page:" << recordTabModel->lastError().text();
        return false;
    }

    // 更新总记录数和总页数
    QSqlQuery query(database);
    if (query.exec("SELECT COUNT(*) FROM record") && query.next()) {
        totalRecords = query.value(0).toInt();
        totalPages = (totalRecords + pageSize - 1) / pageSize; // 向上取整
    }

    emit pageInfoUpdated(currentPage + 1, totalPages); // 发射信号更新 UI
    return true;
}




bool IDatabase::loaddoctorPage()
{
    QString filter = QString("ROWID >= %1 AND ROWID < %2")
                     .arg(currentPage * pageSize + 1)
                     .arg((currentPage + 1) * pageSize + 1);

    doctorTabModel->setFilter(filter);

    if (!doctorTabModel->select()) {
        qDebug() << "Failed to load patient page:" << doctorTabModel->lastError().text();
        return false;
    }

    // 更新总记录数和总页数
    QSqlQuery query(database);
    query.exec("SELECT COUNT(*) FROM doctor");
    if (query.next()) {
        totalRecords = query.value(0).toInt();
        totalPages = (totalRecords + pageSize - 1) / pageSize; // 向上取整
    }

    emit pageInfoUpdated(currentPage + 1, totalPages);
    return true;
}

bool IDatabase::loadmedicinePage()
{
    QString filter = QString("ROWID >= %1 AND ROWID < %2")
                     .arg(currentPage * pageSize + 1)
                     .arg((currentPage + 1) * pageSize + 1);
    medicineTabModel->setFilter(filter);

    if (!medicineTabModel->select()) {
        qDebug() << "Failed to load patient page:" << medicineTabModel->lastError().text();
        return false;
    }

    // 更新总记录数和总页数
    QSqlQuery query(database);
    query.exec("SELECT COUNT(*) FROM medicine");
    if (query.next()) {
        totalRecords = query.value(0).toInt();
        totalPages = (totalRecords + pageSize - 1) / pageSize; // 向上取整
    }

    emit pageInfoUpdated(currentPage + 1, totalPages);
    return true;
}

bool IDatabase::initdoctorModel()
{
    doctorTabModel = new QSqlTableModel(this, database);
    doctorTabModel->setTable("doctor");
    doctorTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    doctorTabModel->setSort(doctorTabModel->fieldIndex("name"), Qt::AscendingOrder);
    if (!(doctorTabModel->select()))
        return false;
    thedoctorSelection = new QItemSelectionModel(doctorTabModel);
    currentPage = 0;
    pageSize = 10; // 每页10条
    return loaddoctorPage();
}

bool IDatabase::initmedicineModel()
{
    // 创建并初始化 QSqlTableModel
    medicineTabModel = new QSqlTableModel(this, database);
    medicineTabModel->setTable("medicine");
    medicineTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    medicineTabModel->setSort(medicineTabModel->fieldIndex("name"), Qt::AscendingOrder);

    // 检查数据表是否成功加载
    if (!medicineTabModel->select())
        return false;

    // 创建选择模型
    themedicineSelection = new QItemSelectionModel(medicineTabModel);

    // 检查库存
    checkInventory();

    // 初始化分页
    currentPage = 0;
    pageSize = 10; // 每页10条

    return loadmedicinePage();
}

bool IDatabase::nextPage()
{
    if (currentPage + 1 >= totalPages) {
        return false; // 当前页已是最后一页
    }

    ++currentPage;
    return loadPatientPage();
}

bool IDatabase::previousPage()
{
    if (currentPage > 0) {
        currentPage--;
        return loadPatientPage();
    }
    return false;
}
bool IDatabase::nextPage1()
{
    if (currentPage + 1 >= totalPages) {
        return false; // 当前页已是最后一页
    }

    ++currentPage;
    return loaddoctorPage();
}

bool IDatabase::previousPage2()
{
    if (currentPage > 0) {
        currentPage--;
        return loadmedicinePage();
    }
    return false;
}

bool IDatabase::nextPage2()
{
    if (currentPage + 1 >= totalPages) {
        return false; // 当前页已是最后一页
    }

    ++currentPage;
    return loadmedicinePage();
}

bool IDatabase::previousPage3()
{
    if (currentPage > 0) {
        currentPage--;
        return loadrecordPage();
    }
    return false;
}

bool IDatabase::nextPage3()
{
    if (currentPage + 1 >= totalPages) {
        return false; // 当前页已是最后一页
    }

    ++currentPage;
    return loadrecordPage();
}

void IDatabase::checkInventory()
{
    QList<QString> lowInventoryItems;

    for (int row = 0; row < medicineTabModel->rowCount(); ++row) {
        QModelIndex index = medicineTabModel->index(row, medicineTabModel->fieldIndex("inventory"));
        int inventory = medicineTabModel->data(index).toInt();

        if (inventory < 10) { // 库存不足
            QModelIndex nameIndex = medicineTabModel->index(row, medicineTabModel->fieldIndex("name"));
            QString medicineName = medicineTabModel->data(nameIndex).toString();
            lowInventoryItems.append(medicineName);
        }
    }

    if (!lowInventoryItems.isEmpty()) {
        qDebug() << "Low inventory items:" << lowInventoryItems; // 调试输出
        emit inventoryWarning(lowInventoryItems);
    } else {
        qDebug() << "All inventory levels are sufficient.";
    }
}



bool IDatabase::previousPage1()
{
    if (currentPage > 0) {
        currentPage--;
        return loaddoctorPage();
    }
    return false;
}
