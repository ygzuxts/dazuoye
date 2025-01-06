#ifndef RECORD_H
#define RECORD_H

#include <QWidget>

namespace Ui {
class ReCord;
}

class ReCord : public QWidget
{
    Q_OBJECT

public:
    explicit ReCord(QWidget *parent = nullptr);
    ~ReCord();

private:
    Ui::ReCord *ui;
signals:
    void gorecordEditView(int idx);
private slots:
    void on_btSearch_clicked();
    void on_btAdd_clicked();
    void on_btDelet_clicked();
    void on_btEdit_clicked();
    void on_btImport_clicked();
    void on_btExport_clicked();
    void on_btnPrevious_clicked();
    void on_btnNext_clicked();
    void updatePageInfo(int currentPage, int totalPages);
};

#endif // RECORD_H
