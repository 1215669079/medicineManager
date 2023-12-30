#include "query.h"
#include "ui_query.h"
#include "function.h"
#include <QtSql>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QMap>
#include <QString>
#include <QCompleter>
#include <QStringList>
// 在代码中使用QXlsx库
#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include <QFileDialog>

extern QString reportautth;

query::query(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::query)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked); // 允许双击编辑
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // 允许整行选择

    QSqlQueryModel *anameModel = new QSqlQueryModel(this);
    anameModel->setQuery("select aname from agency");
    ui->agency_comboBox->setModel(anameModel);
    ui->agency_comboBox_2->setModel(anameModel);

    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentDate = QDate::currentDate();
    ui->start_dateTimeEdit->setDate(currentDate.addMonths(-3));
    ui->start_dateTimeEdit->setTime(currentTime.time());
    ui->start_dateTimeEdit_1->setDate(currentDate.addMonths(-3));
    ui->start_dateTimeEdit_1->setTime(currentTime.time());
    ui->dead_dateTimeEdit->setDate(currentTime.date());
    ui->dead_dateTimeEdit->setTime(currentTime.time());
    ui->dead_dateTimeEdit_1->setDate(currentTime.date());
    ui->dead_dateTimeEdit_1->setTime(currentTime.time());

    ui->tableView->setModel(model);
}

query::~query()
{
    delete ui;
}

void query::on_cancelButton_clicked()
{
    function *f = new function;
    this -> hide();
    f -> show();
}

void query::on_queryclient_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    on_clear_client_pushButton_clicked();
}

void query::on_querymedicine_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    on_clear_medicine_pushButton_clicked();
}

void query::on_queryorder_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    on_clear_order_pushButton_clicked();
}

void query::on_querypurchase_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    on_clear_purchase_pushButton_clicked();
}

void query::on_clear_client_pushButton_clicked()
{
    ui->cname_lineEdit->clear();
    ui->caddress_lineEdit->clear();
    ui->cphone_lineEdit->clear();
    model->removeRows(0, model->rowCount());
    ui->tableView->update();
}

void query::on_clear_medicine_pushButton_clicked()
{
    ui->mdosageForm_lineEdit->clear();
    ui->menterprise_lineEdit->clear();
    ui->mspecification_lineEdit->clear();
    ui->mname_lineEdit->clear();
    model->removeRows(0, model->rowCount());
    ui->tableView->update();
}

void query::on_clear_order_pushButton_clicked()
{
    ui->cname_lineEdit_2->clear();
    model->removeRows(0, model->rowCount());
    ui->tableView->update();
}

void query::on_clear_purchase_pushButton_clicked()
{
    model->removeRows(0, model->rowCount());
    ui->tableView->update();
}

void query::on_client_query_pushButton_clicked()
{
    model->setTable("client");
    model->setHeaderData(0, Qt::Horizontal,tr("编号"));
    model->setHeaderData(1, Qt::Horizontal,tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal,tr("性别"));
    model->setHeaderData(3, Qt::Horizontal,tr("年龄"));
    model->setHeaderData(4, Qt::Horizontal,tr("住址"));
    model->setHeaderData(5, Qt::Horizontal,tr("电话"));
    model->setHeaderData(6, Qt::Horizontal,tr("症状"));
    model->setHeaderData(7, Qt::Horizontal,tr("已购药品"));
    model->setHeaderData(8, Qt::Horizontal,tr("过敏史"));
    model->setHeaderData(9, Qt::Horizontal,tr("既往病史"));
    model->setHeaderData(10, Qt::Horizontal,tr("录入日期"));
    model->setHeaderData(11, Qt::Horizontal,tr("经办人"));
    model->setHeaderData(12, Qt::Horizontal,tr("备注"));

    // 从文本框中获取条件
    QString cname = ui->cname_lineEdit->text();
    QString csex = ui->csex_comboBox->currentText();
    QString cphone = ui->cphone_lineEdit->text();
    QString caddress = ui->caddress_lineEdit->text();

    QString filter;
    if (!cname.isEmpty()) {
        filter += "cname = '" + cname + "'";
    }
    if (!csex.isEmpty()) {
        if (!filter.isEmpty()) {
            filter += " AND ";
        }
        filter += "csex = '" + csex + "'";
    }
    if (!cphone.isEmpty()) {
        if (!filter.isEmpty()) {
            filter += " AND ";
        }
        filter += "cphone = '" + cphone + "'";
    }
    if (!caddress.isEmpty()) {
        if (!filter.isEmpty()) {
            filter += " AND ";
        }
        filter += "caddress = '" + caddress + "'";
    }

    model->setFilter(filter);
    model->select();
    qDebug()<< model->filter();
}

void query::on_medicine_query_pushButton_clicked()
{
    model->setTable("medicine");
    model->setHeaderData(0, Qt::Horizontal,tr("编号"));
    model->setHeaderData(1, Qt::Horizontal,tr("名称"));
    model->setHeaderData(2, Qt::Horizontal,tr("服用方法"));
    model->setHeaderData(3, Qt::Horizontal,tr("功效"));
    model->setHeaderData(4, Qt::Horizontal,tr("剂型"));
    model->setHeaderData(5, Qt::Horizontal,tr("类型"));
    model->setHeaderData(6, Qt::Horizontal,tr("规格"));
    model->setHeaderData(7, Qt::Horizontal,tr("生产企业"));
    model->setHeaderData(8, Qt::Horizontal,tr("售价"));
    model->setHeaderData(9, Qt::Horizontal,tr("库存"));
    model->setHeaderData(10, Qt::Horizontal,tr("备注"));

    // 从文本框中获取条件
    QString mdosageForm = ui->mdosageForm_lineEdit->text();
    QString menterprise = ui->menterprise_lineEdit->text();
    QString mspecification = ui->mspecification_lineEdit->text();
    QString mname = ui->mname_lineEdit->text();
    QString mmode = ui->mmode_comboBox->currentText();
    QString mtype = ui->mtype_comboBox->currentText();

    QString filter;
    if (!mdosageForm.isEmpty()) {
        filter += "dosageform = '" + mdosageForm + "'";
    }
    if (!menterprise.isEmpty()) {
        if (!filter.isEmpty()) {
            filter += " AND ";
        }
        filter += "enterprise = '" + menterprise + "'";
    }
    if (!mspecification.isEmpty()) {
        if (!filter.isEmpty()) {
            filter += " AND ";
        }
        filter += "specification = '" + mspecification + "'";
    }
    if (!mname.isEmpty()) {
        if (!filter.isEmpty()) {
            filter += " AND ";
        }
        filter += "mname = '" + mname + "'";
    }
    if (!mmode.isEmpty()) {
        if (!filter.isEmpty()) {
            filter += " AND ";
        }
        filter += "mmode = '" + mmode + "'";
    }
    if (!mtype.isEmpty()) {
        if (!filter.isEmpty()) {
            filter += " AND ";
        }
        filter += "type = '" + mtype + "'";
    }

    model->setFilter(filter);
    model->select();
    qDebug()<< model->filter();
}

void query::on_order_query_pushButton_clicked()
{
    model->setTable("morder");
    model->setHeaderData(0, Qt::Horizontal,tr("编号"));
    model->setHeaderData(1, Qt::Horizontal,tr("顾客姓名"));
    model->setHeaderData(2, Qt::Horizontal,tr("症状"));
    model->setHeaderData(3, Qt::Horizontal,tr("已购药品"));
    model->setHeaderData(4, Qt::Horizontal,tr("合计"));
    model->setHeaderData(5, Qt::Horizontal,tr("购买时间"));
    model->setHeaderData(6, Qt::Horizontal,tr("经办人"));
    model->setHeaderData(7, Qt::Horizontal,tr("备注"));

    // 从文本框中获取条件
    QString cname = ui->cname_lineEdit_2->text();
    QString aname = ui->agency_comboBox->currentText();
    QString startTime = ui->start_dateTimeEdit->text();
    QString endTime = ui->dead_dateTimeEdit->text();

    // 构建时间间隔条件
    QString timeFilter;
    if (!startTime.isEmpty() && !endTime.isEmpty()) {
        timeFilter = "odate >= '" + startTime + "' AND odate <= '" + endTime + "'";
    }

    QString otherFilters;
    if (!cname.isEmpty()) {
        otherFilters += "cname = '" + cname + "'";
    }
    if (!aname.isEmpty()) {
        if (!otherFilters.isEmpty()) {
            otherFilters += " AND ";
        }
        otherFilters += "aname = '" + aname + "'";
    }

    // 合并时间间隔条件和其他条件
    QString filter;
    if (!timeFilter.isEmpty()) {
        filter += timeFilter;
    }
    if (!timeFilter.isEmpty() && !otherFilters.isEmpty()) {
        filter += " AND ";
    }
    if (!otherFilters.isEmpty()) {
        filter += otherFilters;
    }

    model->setFilter(filter);
    model->select();
    qDebug()<< model->filter();
}

void query::on_purchase_query_pushButton_clicked()
{
    model->setTable("purchase");
    model->setHeaderData(0, Qt::Horizontal,tr("编号"));
    model->setHeaderData(1, Qt::Horizontal,tr("入库药品"));
    model->setHeaderData(2, Qt::Horizontal,tr("入库时间"));
    model->setHeaderData(3, Qt::Horizontal,tr("过期时间"));
    model->setHeaderData(4, Qt::Horizontal,tr("经办人"));
    model->setHeaderData(5, Qt::Horizontal,tr("备注"));

    // 从文本框中获取条件
    QString aname = ui->agency_comboBox_2->currentText();
    QString startTime = ui->start_dateTimeEdit->text();
    QString endTime = ui->dead_dateTimeEdit->text();

    // 构建时间间隔条件
    QString timeFilter;
    if (!startTime.isEmpty() && !endTime.isEmpty()) {
        timeFilter = "pdate >= '" + startTime + "' AND pdate <= '" + endTime + "'";
    }

    QString otherFilters;
    if (!aname.isEmpty()) {
        if (!otherFilters.isEmpty()) {
            otherFilters += " AND ";
        }
        otherFilters += "aname = '" + aname + "'";
    }

    // 合并时间间隔条件和其他条件
    QString filter;
    if (!timeFilter.isEmpty()) {
        filter += timeFilter;
    }
    if (!timeFilter.isEmpty() && !otherFilters.isEmpty()) {
        filter += " AND ";
    }
    if (!otherFilters.isEmpty()) {
        filter += otherFilters;
    }

    model->setFilter(filter);
    model->select();
    qDebug()<< model->filter();
}

void query::on_export_pushButton_clicked()
{
    if(reportautth == "有")
    {
        // 获取用户选择的文件路径和文件名
        QString filePath = QFileDialog::getSaveFileName(this, "保存文件", "", "Excel Files (*.xlsx)");

        if (!filePath.isEmpty()) {
            // 创建一个QXlsx::Document对象
            QXlsx::Document xlsx;

            // 获取TableView中的数据模型
            QAbstractItemModel *model = ui->tableView->model();

            // 设置工作表标题行（表头数据）
            for (int column = 0; column < model->columnCount(); ++column) {
                xlsx.write(1, column + 1, model->headerData(column, Qt::Horizontal).toString());
            }

            // 将数据写入Excel文件
            for (int row = 0; row < model->rowCount(); ++row) {
                for (int column = 0; column < model->columnCount(); ++column) {
                    QModelIndex index = model->index(row, column);
                    xlsx.write(row + 2, column + 1, index.data().toString());
                }
            }

            // 保存Excel文件
            xlsx.saveAs(filePath);
        }
    }
    else
    {
        QMessageBox::information(this, "警告", "没有权限");
    }
}
