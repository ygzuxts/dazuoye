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
    QString userLogin(QString userName, QString password);

    bool searchPatient(QString filter);
    bool deleteCurrentPatient();
    bool subitPatientEdit();
    void revertPatientEdit();
    int addNewPatient();
private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const &)               = delete;
    void operator=(IDatabase const &)  = delete;

    QSqlDatabase database;
    void ininDatabase();



signals:
};

#endif // IDATABASE_H
