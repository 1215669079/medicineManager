#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class usermanage;
}

class usermanage : public QWidget
{
    Q_OBJECT

public:
    explicit usermanage(QWidget *parent = nullptr);
    ~usermanage();

private slots:
    void on_cancleButton_clicked();

    void on_export_pushButton_clicked();

    void on_enter_pushButton_clicked();

    void on_del_pushButton_clicked();

    void on_revert_pushButton_clicked();

    void on_save_pushButton_clicked();

private:
    QSqlTableModel *model;
    Ui::usermanage *ui;
};

#endif // USERMANAGE_H
