#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("medicinemanager");
    db.setUserName("root");
    db.setPassword("123456");

    if (!db.open()) {
         QMessageBox::critical(0, QObject::tr("无法打开数据库"),
             "无法创建数据库连接！", QMessageBox::Cancel);
         return false;
     }

    QSqlQuery query;

    // 使数据库支持中文
    query.exec("SET NAMES 'utf8'");
    return true;
}

#endif // CONNECTION_H
