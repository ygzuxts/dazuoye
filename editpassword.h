#ifndef EDITPASSWORD_H
#define EDITPASSWORD_H

#include <QWidget>

namespace Ui {
class editpassword;
}

class editpassword : public QWidget
{
    Q_OBJECT

public:
    explicit editpassword(QWidget *parent = nullptr);
    ~editpassword();
    void changePassword();
private:
    Ui::editpassword *ui;
signals:
    void goPerviousView();
private slots:
    void on_btnconfirm_clicked();
};

#endif // EDITPASSWORD_H
