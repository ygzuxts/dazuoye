#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>

namespace Ui {
class WelcomeView;
}

class WelcomeView : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeView(QWidget *parent = nullptr);
    ~WelcomeView();
    void setUserLevel(int level);
private slots:
    void on_btDoctor_clicked();

    void on_btDepartment_clicked();

    void on_btPatient_clicked();

    void on_btMedicine_clicked();

    void on_btRecord_clicked();

signals:
    void Doctor();
    void Department();
    void Patient();
    void medicine();
    void Record();
private:
    Ui::WelcomeView *ui;
};

#endif // WELCOMEVIEW_H
