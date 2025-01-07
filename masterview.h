#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include"loginview.h"
#include"doctorview.h"
#include"patienteditview.h"
#include"patientview.h"
#include"welcomeview.h"
#include"doctoreditview.h"
#include"medicineview.h"
#include"medicineeditview.h"
#include"record.h"
#include"recordeditview.h"
#include"editpassword.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MasterView;
}
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

public slots:
    void goLoginView();
    void goWelcomView(int level);
    void goDoctorView();
    void gomedicineView();
    void goPatientView();
    void goPatientEditView(int rowNo);
    void godoctorEditView(int rowNo);
    void goPreviousView();
    void gomedicineEditView(int rowNo);
    void gorecord();
    void gorecordEditView(int rowNo);
    void goeditpassword();

private slots:
    void on_btBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btLogout_clicked();

private:
    void pushWidgetToStackView(QWidget *widget);
    Ui::MasterView *ui;

    WelcomeView *welcomeView;
    DoctorView *doctorView;
    PatientView *patientView;
    MedicineView *m_medicineView;
    LoginView *loginView;
    PatientEditView  *patientEditView;
    doctoreditview *m_doctoreditview;
    medicineeditview *Medicineeditview;
    ReCord *record;
    Recordeditview *recordeditview;
    editpassword *Editpassword;
};
#endif // MASTERVIEW_H
