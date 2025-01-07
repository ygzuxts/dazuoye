#ifndef DOCTOREDITVIEW_H
#define DOCTOREDITVIEW_H

#include <QWidget>
#include<QDataWidgetMapper>
namespace Ui {
class doctoreditview;
}

class doctoreditview : public QWidget
{
    Q_OBJECT

public:
    explicit doctoreditview(QWidget *parent = nullptr, int index = 0);
    ~doctoreditview();

private slots:
    void on_btnsave_4_clicked();

    void on_btncancel_4_clicked();

private:
    Ui::doctoreditview *ui;
    QDataWidgetMapper *dataMapper;
    QString employeeNo;
signals:
    void goPerviousView();
};

#endif // DOCTOREDITVIEW_H
