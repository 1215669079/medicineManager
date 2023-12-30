#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Login_username, SIGNAL(returnPressed()), this, SLOT(on_LoginButton_clicked()));
    connect(ui->Login_password, SIGNAL(returnPressed()), this, SLOT(on_LoginButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LoginButton_clicked()
{
    username = ui->Login_username->text();
    QString password = ui->Login_password->text();
    qDebug()<<"用户名："<<username<<"密码:"<<password;
    QSqlDatabase db;
    QSqlQuery query(db);
    query.exec("select ano,aname,apassword,manageauth,queryauth,browseauth,enterauth,deleteauth,alterauth,reportauth from agency");
    bool T1=false;
    while(query.next())
    {
        QString user = query.value(1).toString();
        QString pass = query.value(2).toString();
        qDebug() << user << pass <<query.value(1).toString()<<query.value(2).toString();
        if(username.compare(user)==0&&password.compare(pass)==0){
            manageauth = query.value(3).toString();
            queryauth = query.value(4).toString();
            browseauth = query.value(5).toString();
            enterauth = query.value(6).toString();
            deleteauth = query.value(7).toString();
            alterauth = query.value(8).toString();
            reportautth = query.value(9).toString();
            T1=true;
            this->hide();
            f=new function;
            f->show();
        }
    }
    if(T1==false)
        QMessageBox::information(this, "警告", "用户名或密码错误");
}

void MainWindow::on_remitButton_clicked()
{
    ui->Login_username->clear();
    ui->Login_password->clear();
}
