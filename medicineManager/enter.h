#ifndef ENTER_H
#define ENTER_H

#include <QWidget>
#include <QSqlTableModel>
#include <QStandardItemModel>

class QSqlTableModel;

namespace Ui {
class enter;
}

class enter : public QWidget
{
    Q_OBJECT

public:
    explicit enter(QWidget *parent = nullptr);
    ~enter();

private slots:
    void on_cancelButton_clicked();

    void on_enterMedicineButton_clicked();

    void on_enterOrderButton_clicked();

    void on_enterPurchaseButton_clicked();

    void on_checkcname_pushButton_clicked();

    void on_enteromname_pushButton_clicked();

    void on_save_enterOrder_pushButton_clicked();

    void on_clear_enterOrder_pushButton_clicked();

    void on_save_enterMedicinepushButton_clicked();

    void on_pentermname_pushButton_clicked();

    void on_save_enterPurchase_pushButton_clicked();

    void on_clear_enterPurchase_pushButton_clicked();

    void on_clear_enterMedicinepushButton_clicked();

private:
    Ui::enter *ui;
    QStandardItemModel *model1;
    QStandardItemModel *model2;
    bool T1 = false;
};

#endif // ENTER_H
