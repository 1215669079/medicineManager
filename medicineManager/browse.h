#ifndef BROWSE_H
#define BROWSE_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class browse;
}
class QSqlTableModel;

class browse : public QWidget
{
    Q_OBJECT

public:
    explicit browse(QWidget *parent = nullptr);
    ~browse();

private slots:
    void on_cancleButton_clicked();

    void on_browseclient_pushButton_clicked();

    void on_browsemedicine_pushButton_clicked();

    void on_browseorder_pushButton_clicked();

    void on_browsepurchase_pushButton_clicked();

    void on_save_pushButton_clicked();

    void on_del_pushButton_clicked();

    void on_enter_pushButton_clicked();

    void on_revert_pushButton_clicked();

    void on_export_pushButton_clicked();

private:
    QSqlTableModel *model;
    Ui::browse *ui;
};

#endif // BROWSE_H
