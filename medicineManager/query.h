#ifndef QUERY_H
#define QUERY_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class query;
}

class QSqlTableModel;

class query : public QWidget
{
    Q_OBJECT

public:
    explicit query(QWidget *parent = nullptr);
    ~query();

private slots:
    void on_cancelButton_clicked();

    void on_queryclient_pushButton_clicked();

    void on_querymedicine_pushButton_clicked();

    void on_queryorder_pushButton_clicked();

    void on_querypurchase_pushButton_clicked();

    void on_clear_client_pushButton_clicked();

    void on_clear_medicine_pushButton_clicked();

    void on_clear_order_pushButton_clicked();

    void on_clear_purchase_pushButton_clicked();

    void on_client_query_pushButton_clicked();

    void on_medicine_query_pushButton_clicked();

    void on_order_query_pushButton_clicked();

    void on_purchase_query_pushButton_clicked();

    void on_export_pushButton_clicked();

private:
    QSqlTableModel *model;
    Ui::query *ui;
};

#endif // QUERY_H
