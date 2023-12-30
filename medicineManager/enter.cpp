#include "enter.h"
#include "ui_enter.h"
#include "function.h"
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include "mainwindow.h"

QString username;

enter::enter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::enter)
{
    ui->setupUi(this);

    QSqlQueryModel *mnameModel = new QSqlQueryModel(this);
    mnameModel->setQuery("select mname from medicine");
    ui->omname_comboBox->setModel(mnameModel);
    ui->pmname_comboBox->setModel(mnameModel);

    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentDate = QDate::currentDate();
    ui->dateTimeEdit->setDate(currentTime.date());
    ui->dateTimeEdit->setTime(currentTime.time());
    ui->pdateTimeEdit->setDate(currentTime.date());
    ui->pdateTimeEdit->setTime(currentTime.time());
    ui->poutdateTimeEdit->setDate(currentDate.addYears(1));
    ui->poutdateTimeEdit->setTime(currentTime.time());

    model2 = new QStandardItemModel(this);
    model2->setColumnCount(2);
    model2->setHeaderData(0, Qt::Horizontal,tr("药品名称"));
    model2->setHeaderData(1, Qt::Horizontal,tr("数量"));
    ui->enterOrder_tableView->setModel(model2);

    ui->oamount_lineEdit->setText("0");
    ui->aname1_label->setText(QString("%1").arg(username));
    ui->paname1_label->setText(QString("%1").arg(username));

    model1 = new QStandardItemModel(this);
    model1->setColumnCount(2);
    model1->setHeaderData(0, Qt::Horizontal,tr("药品名称"));
    model1->setHeaderData(1, Qt::Horizontal,tr("数量"));
    ui->enterPurchase_tableView->setModel(model1);

    qDebug()<<username;
}

enter::~enter()
{
    delete ui;
}

void enter::on_cancelButton_clicked()
{
    function *f = new function;
    this -> hide();
    f -> show();
}

void enter::on_enterMedicineButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    on_clear_enterMedicinepushButton_clicked();
}

void enter::on_enterOrderButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    on_clear_enterOrder_pushButton_clicked();
}

void enter::on_enterPurchaseButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void enter::on_checkcname_pushButton_clicked()
{
    QString cname = ui->cname_lineEdit->text();
    qDebug() << cname;
    QSqlDatabase db;
    QSqlQuery query(db);
    query.exec("select cname,csex,cage,caddress,cphone,allergy,anamnesis,cremark from client");


    while(query.next())
    {
        QString name = query.value(0).toString();
        QString sex = query.value(1).toString();
        int age = query.value(2).toInt();
        QString address = query.value(3).toString();
        QString phone = query.value(4).toString();
        QString allergy = query.value(5).toString();
        QString anamnesis = query.value(6).toString();
        QString cremark = query.value(7).toString();
        qDebug() << name<<sex<<age<<address<<phone<<allergy<<anamnesis<<cremark;
        if(cname.compare(name)==0)
        {
            T1=true;
        }
        if(T1)
        {
            ui->csex_comboBox->setEditText(sex);
            ui->cage_spinBox->setValue(age);
            ui->caddress_lineEdit->setText(address);
            ui->cphone_lineEdit->setText(phone);
            ui->callergy_lineEdit->setText(allergy);
            ui->canamnesis_lineEdit->setText(anamnesis);
            ui->cremark_lineEdit->setText(cremark);
        }
    }
    if(!T1)
    {
        QMessageBox::warning(this,"警告","新顾客请添加");
    }
}

void enter::on_enteromname_pushButton_clicked()
{
    int row = model2->rowCount();  // 获取当前行数
    model2->insertRow(row);
    model2->setData(model2->index(row, 0), ui->omname_comboBox->currentText());
    model2->setData(model2->index(row, 1), ui->omname_num_spinBox->text());
    ui->enterOrder_tableView->update();

    QString mname = ui->omname_comboBox->currentText();
    QString mnum = ui->omname_num_spinBox->text();
    QSqlDatabase db;
    QSqlQuery query(db);
    query.exec(QString("select mname,mprice from medicine where mname = '%1';").arg(mname));
    query.next();
    double Price = query.value(1).toDouble();
    QString amount = ui->oamount_lineEdit->text();
    double amount1 = amount.toDouble();
    amount1 += Price * mnum.toDouble();
    ui->oamount_lineEdit->setText(QString::number(amount1));

    qDebug()<< ui->omname_comboBox->currentText() << ui->omname_num_spinBox->text()<<row<<Price;
}

void enter::on_save_enterOrder_pushButton_clicked()
{
    QSqlQuery query;

    QDateTime currentTime = QDateTime::currentDateTime();
    QString cname = ui->cname_lineEdit->text();
    QString csex = ui->csex_comboBox->currentText();
    QString cage = ui->cage_spinBox->text();
    QString caddress = ui->caddress_lineEdit->text();
    QString cphone = ui->cphone_lineEdit->text();
    QString csymptom = ui->csymptom_lineEdit->text();
    QString mno;
    QString datetime = ui->dateTimeEdit->text();
    QString callergy = ui->callergy_lineEdit->text();
    QString canamnesis = ui->canamnesis_lineEdit->text();
    QString cremark = ui->cremark_lineEdit->text();
    QString allergy = ui->callergy_lineEdit->text();
    QString anamnesis = ui->canamnesis_lineEdit->text();
    QString oremark = ui->oremark_lineEdit->text();
    QString oamount = ui->oamount_lineEdit->text();
    // 获取整个表格的数据
    int rowCount = model2->rowCount();
    int columnCount = model2->columnCount();
    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < columnCount; ++column) {
            QStandardItem *item = model2->item(row, column);
            if (item) {
                QString data = item->text();  // 获取单元格的文本数据
                // 处理数据
                QString num;
                QString mname;
                mno += data;
                if(column % 2 != 0)
                {
                    mno += ";";
                    num = data;
                    bool rtn2 = query.exec(
                                QString("update medicine set inventory=inventory-%1 where mname='%2'")
                                .arg(num).arg(mname));
                    qDebug()<<rtn2;
                }
                else
                {
                    mno += "*";
                    mname = data;
                }
            }
        }
    }
    if(T1)
    {
        QSqlQuery query;
        bool rtn = query.exec(
                    QString("update client set csex='%1',cage=%2,caddress='%3',cphone='%4',csymptom='%5',mname='%6',aname='%7',cdate='%8',cremark='%9',allergy='%10',anamnesis='%11' where cname='%12'")
                    .arg(csex).arg(cage).arg(caddress).arg(cphone).arg(csymptom).arg(mno).arg(username).arg(datetime).arg(cremark).arg(allergy).arg(anamnesis).arg(cname));
        bool rtn1 = query.exec(
                    QString("insert into morder (cname,csymptom,aname,mname,odate,oremark,oamount) values('%1', '%2', '%3', '%4', '%5', '%6', %7)")
                    .arg(cname).arg(csymptom).arg(username).arg(mno).arg(datetime).arg(oremark).arg(oamount));

        if (rtn&&rtn1) {
            QMessageBox::information(this, tr("提示"), tr("购买成功！"), QMessageBox::Ok);
            on_clear_enterOrder_pushButton_clicked();
        } else {
            QMessageBox::information(this, tr("提示"), tr("购买失败，无法访问数据库！"), QMessageBox::Ok);
        }
        qDebug()<<rtn<<rtn1;
    }
    else
    {
        bool rtn = query.exec(
                    QString("insert into client (cname,csex,cage,caddress,cphone,csymptom,mname,aname,cdate,cremark,allergy,anamnesis) values('%1', '%2', %3, '%4', '%5', '%6', '%7','%8','%9','%10','%11','%12')")
                    .arg(cname).arg(csex).arg(cage).arg(caddress).arg(cphone).arg(csymptom).arg(mno).arg(username).arg(datetime).arg(cremark).arg(allergy).arg(anamnesis));
        bool rtn1 = query.exec(
                    QString("insert into morder (cname,csymptom,aname,mname,odate,oremark,oamount) values('%1', '%2', '%3', '%4', '%5', '%6', %7)")
                    .arg(cname).arg(csymptom).arg(username).arg(mno).arg(datetime).arg(oremark).arg(oamount));
        if (rtn&&rtn1) {
            QMessageBox::information(this, tr("提示"), tr("购买成功！"), QMessageBox::Ok);
            on_clear_enterOrder_pushButton_clicked();
        } else {
            QMessageBox::information(this, tr("提示"), tr("购买失败，无法访问数据库！"), QMessageBox::Ok);
        }
        qDebug()<<rtn<<rtn1;
    }
}

void enter::on_clear_enterOrder_pushButton_clicked()
{
    ui->cname_lineEdit->clear();
    ui->cage_spinBox->clear();
    ui->caddress_lineEdit->clear();
    ui->cphone_lineEdit->clear();
    ui->callergy_lineEdit->clear();
    ui->canamnesis_lineEdit->clear();
    ui->cremark_lineEdit->clear();
    ui->oremark_lineEdit->clear();
    ui->csymptom_lineEdit->clear();
    ui->oamount_lineEdit->setText("0");
    model2->removeRows(0, model2->rowCount());
    ui->enterOrder_tableView->update();
}

void enter::on_save_enterMedicinepushButton_clicked()
{
    QString mname = ui->mname_lineEdit->text();
    QString mmode = ui->mmode_comboBox->currentText();
    QString mefficacy = ui->mefficacy_lineEdit->text();
    QString mdosageForm = ui->mdosageForm_lineEdit->text();
    QString type = ui->mtype_comboBox->currentText();
    QString mspecification = ui->mspecification_lineEdit->text();
    QString menterprise = ui->menterprise_lineEdit->text();
    QString mprice = ui->mprice_spinBox->text();
    QString minventory = ui->minventory_spinBox->text();
    QString mremark = ui->mremark_lineEdit->text();

    QSqlDatabase db;
    QSqlQuery query(db);

    bool rtn = query.exec(
                QString("insert into medicine (mname,mmode,mefficacy,dosageform,type,specification,enterprise,mprice,inventory,mremark) values( '%1', '%2', '%3', '%4', '%5', '%6', '%7', %8, %9, '%10')")
                .arg(mname).arg(mmode).arg(mefficacy).arg(mdosageForm).arg(type).arg(mspecification).arg(menterprise).arg(mprice).arg(minventory).arg(mremark));

    if (rtn) {
        QMessageBox::information(this, tr("提示"), tr("录入成功！"), QMessageBox::Ok);
        on_clear_enterMedicinepushButton_clicked();
    } else {
        QMessageBox::information(this, tr("提示"), tr("录入失败，无法访问数据库！"), QMessageBox::Ok);
        qDebug()<<query.lastError().text()<<mremark;
    }
}

void enter::on_clear_enterMedicinepushButton_clicked()
{
    ui->mname_lineEdit->clear();
    ui->mefficacy_lineEdit->clear();
    ui->mdosageForm_lineEdit->clear();
    ui->mspecification_lineEdit->clear();
    ui->menterprise_lineEdit->clear();
    ui->mprice_spinBox->setValue(0);
    ui->minventory_spinBox->setValue(0);
    ui->mremark_lineEdit->clear();
}

void enter::on_pentermname_pushButton_clicked()
{
    int row = model1->rowCount();  // 获取当前行数
    model1->insertRow(row);
    model1->setData(model1->index(row, 0), ui->pmname_comboBox->currentText());
    model1->setData(model1->index(row, 1), ui->pmnum_spinBox->text());
    ui->enterPurchase_tableView->update();
}

void enter::on_save_enterPurchase_pushButton_clicked()
{
    QSqlQuery query;
qDebug()<<123456;
    QString premark = ui->premark_lineEdit->text();
    QString pdateTime = ui->pdateTimeEdit->text();
    QString poutdateTime = ui->poutdateTimeEdit->text();
    QString mno;

    // 获取整个表格的数据
    int rowCount = model1->rowCount();
    int columnCount = model1->columnCount();
    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < columnCount; ++column) {
            QStandardItem *item = model1->item(row, column);
            if (item) {
                QString data = item->text();  // 获取单元格的文本数据
                // 处理数据
                QString num;
                QString mname;
                mno += data;
                if(column % 2 != 0)
                {
                    mno += ";";
                    num = data;
                    bool rtn2 = query.exec(
                                QString("update medicine set inventory=inventory+%1 where mname='%2'")
                                .arg(num).arg(mname));
                    qDebug()<<rtn2;
                }
                else
                {
                    mno += "*";
                    mname = data;
                }
            }
        }
    }
    bool rtn = query.exec(
                QString("insert into purchase (mname,pdate,poutdate,aname,premark) values('%1', '%2', '%3', '%4', '%5')")
                .arg(mno).arg(pdateTime).arg(poutdateTime).arg(username).arg(premark));

    if (rtn) {
        QMessageBox::information(this, tr("提示"), tr("购买成功！"), QMessageBox::Ok);
        on_clear_enterPurchase_pushButton_clicked();
    } else {
        QMessageBox::information(this, tr("提示"), tr("购买失败，无法访问数据库！"), QMessageBox::Ok);
    }
    qDebug()<<rtn;
}

void enter::on_clear_enterPurchase_pushButton_clicked()
{
    ui->premark_lineEdit->clear();
    ui->pmnum_spinBox->setValue(0);

    model1->removeRows(0, model1->rowCount());
    ui->enterPurchase_tableView->update();
}


