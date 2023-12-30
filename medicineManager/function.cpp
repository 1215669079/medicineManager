#include "function.h"
#include "ui_function.h"
#include "query.h"
#include "enter.h"
#include "browse.h"
#include "usermanage.h"
#include "mainwindow.h"

QString manageauth;
QString queryauth;
QString browseauth;
QString enterauth;
QString deleteauth;
QString alterauth;
QString reportautth;

function::function(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::function)
{
    ui->setupUi(this);
}

function::~function()
{
    delete ui;
}

void function::on_queryButton_clicked()
{
    if(queryauth == "有")
    {
        query *q = new query;
        this -> hide();
        q -> show();
    }
    else
    {
        QMessageBox::information(this, "警告", "没有权限");
    }
}

void function::on_enterButton_clicked()
{
    if(enterauth == "有")
    {
        enter *e = new enter;
        this -> hide();
        e -> show();
    }
    else
    {
        QMessageBox::information(this, "警告", "没有权限");
    }
}

void function::on_usermanageButton_clicked()
{
    if(manageauth == "有")
    {
        usermanage *u = new usermanage;
        this -> hide();
        u -> show();
    }
    else
    {
        QMessageBox::information(this, "警告", "没有权限");
    }
}

void function::on_browseButton_clicked()
{
    if(browseauth == "有")
    {
        browse *b = new browse;
        this -> hide();
        b -> show();
    }
    else
    {
        QMessageBox::information(this, "警告", "没有权限");
    }
}

void function::on_logoutButton_clicked()
{
    MainWindow *m = new MainWindow;
    this -> hide();
    m -> show();
}
