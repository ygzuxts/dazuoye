#ifndef RECORDEDITVIEW_H
#define RECORDEDITVIEW_H

#include <QWidget>
#include<QDataWidgetMapper>
namespace Ui {
class Recordeditview;
}

class Recordeditview : public QWidget
{
    Q_OBJECT

public:
    explicit Recordeditview(QWidget *parent = nullptr, int index = 0);
    ~Recordeditview();

private slots:
    void on_btnsave_4_clicked();

    void on_btncancel_4_clicked();

private:
    Ui::Recordeditview *ui;
    QDataWidgetMapper *dataMapper;
signals:
    void goPerviousView();
};

#endif // RECORDEDITVIEW_H
