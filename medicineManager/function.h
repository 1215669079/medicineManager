#ifndef FUNCTION_H
#define FUNCTION_H

#include <QWidget>

namespace Ui {
class function;
}

class function : public QWidget
{
    Q_OBJECT

public:
    explicit function(QWidget *parent = nullptr);
    ~function();

private slots:
    void on_queryButton_clicked();

    void on_enterButton_clicked();

    void on_usermanageButton_clicked();

    void on_browseButton_clicked();

    void on_logoutButton_clicked();

private:
    Ui::function *ui;
};

#endif // FUNCTION_H
