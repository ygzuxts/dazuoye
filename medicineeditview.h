#ifndef MEDICINEEDITVIEW_H
#define MEDICINEEDITVIEW_H

#include <QWidget>
#include<QDataWidgetMapper>

namespace Ui {
class medicineeditview;
}

class medicineeditview : public QWidget
{
    Q_OBJECT

public:
    explicit medicineeditview(QWidget *parent = nullptr, int index = 0);
    ~medicineeditview();

private slots:
    void on_btnsave_4_clicked();

    void on_btncancel_4_clicked();

private:
    Ui::medicineeditview *ui;
    QDataWidgetMapper *dataMapper;
signals:
    void goPerviousView();
};

#endif // MEDICINEEDITVIEW_H
