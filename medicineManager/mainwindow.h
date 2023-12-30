#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPushButton>
#include <QRadioButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <function.h>
#include <QKeyEvent>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern QString username;
extern QString manageauth;
extern QString queryauth;
extern QString browseauth;
extern QString enterauth;
extern QString deleteauth;
extern QString alterauth;
extern QString reportautth;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_LoginButton_clicked();

    void on_remitButton_clicked();

private:
    Ui::MainWindow *ui;
    function *f;
};
#endif // MAINWINDOW_H
