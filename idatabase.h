#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QtSql>
#include<QSqlDatabase>
#include<QDataWidgetMapper>
class IDatabase : public QObject
{
    Q_OBJECT
public:
    static IDatabase &getInstance()
    {
        static IDatabase    instance;

        return instance;
    }
    bool initPatientModel();
    QSqlTableModel *patientTabModel;
    QItemSelectionModel *thePatientSelection;

    bool initdoctorModel();
    QSqlTableModel *doctorTabModel;
    QItemSelectionModel *thedoctorSelection;

    bool initmedicineModel();
    QSqlTableModel *medicineTabModel;
    QItemSelectionModel *themedicineSelection;

    bool initrecordModel();
    QSqlTableModel *recordTabModel;
    QItemSelectionModel *therecordSelection;

    QString userLogin(QString userName, QString password);

    bool searchPatient(QString filter);
    bool deleteCurrentPatient();
    bool subitPatientEdit();
    void revertPatientEdit();
    int addNewPatient();

    bool searchdoctor(QString filter);
    bool deleteCurrentdoctor();
    bool subitdoctorEdit();
    void revertdoctorEdit();
    int addNewdoctor();

    bool searchmedicine(QString filter);
    bool deleteCurrentmedicine();
    bool subitmedicineEdit();
    void revertmedicineEdit();
    int addNewmedicine();

    bool searchrecord(QString filter);
    bool deleteCurrentrecord();
    bool subitrecordEdit();
    void revertrecordEdit();
    int addNewrecord();


    bool loadPatientPage();
    bool loaddoctorPage();
    bool loadmedicinePage();
    bool loadrecordPage();

    bool previousPage();
    bool nextPage();

    bool previousPage1();
    bool nextPage1();

    bool previousPage2();
    bool nextPage2();

    bool previousPage3();
    bool nextPage3();


    int currentPage = 0;
    int pageSize = 10;
    int totalRecords = 0;
    int totalPages = 0;
    void checkInventory();
    int getLastLoginLevel() const
    {
        return lastLoginLevel;
    }
private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const &)               = delete;
    void operator=(IDatabase const &)  = delete;

    QSqlDatabase database;
    void ininDatabase();
    int lastLoginLevel;


signals:

    void pageInfoUpdated(int currentPage, int totalPages);
    void inventoryWarning(const QList<QString> &lowInventoryItems);
};

#endif // IDATABASE_H
