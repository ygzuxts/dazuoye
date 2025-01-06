#ifndef MEDICINEVIEW_H
#define MEDICINEVIEW_H

#include <QWidget>

namespace Ui {
class MedicineView;
}

class MedicineView : public QWidget
{
    Q_OBJECT

public:
    explicit MedicineView(QWidget *parent = nullptr);
    ~MedicineView();
public slots:
    void showInventoryWarning(const QList<QString> &lowInventoryItems);
private slots:
    void on_btSearch_clicked();

    void on_btAdd_clicked();

    void on_btDelet_clicked();

    void on_btEdit_clicked();

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

    void on_btImport_clicked();

    void on_btExport_clicked();
    void updatePageInfo(int currentPage, int totalPages);


private:
    Ui::MedicineView *ui;
signals:
    void gomedicineEditView(int idx);
};

#endif // MEDICINEVIEW_H
