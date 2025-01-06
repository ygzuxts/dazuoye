#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QWidget>

namespace Ui {
class PatientView;
}

class PatientView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientView(QWidget *parent = nullptr);
    ~PatientView();

private slots:
    void on_btSearch_clicked();

    void on_btDelet_clicked();

    void on_btEdit_clicked();
    void on_btAdd_clicked();

    void on_btImport_clicked();

    void on_btExport_clicked();

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();
    void updatePageInfo(int currentPage, int totalPages);
signals:
    void goPatientEditView(int idx);
private:

    Ui::PatientView *ui;
};

#endif // PATIENTVIEW_H
