#include "browse.h"
#include "ui_browse.h"
#include "function.h"
//#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
// 在代码中使用QXlsx库
#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include <QFileDialog>
extern QString enterauth;
extern QString deleteauth;
extern QString alterauth;
extern QString reportautth;

browse::browse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::browse)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked); // 允许双击编辑
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // 允许整行选择
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
    model->select(); // 从表中获取数据
    ui->tableView->setModel(model); // 将model设置为TableView的Model
}

browse::~browse()
{
    delete ui;
}

void browse::on_cancleButton_clicked()
{
    function *f = new function;
    this -> hide();
    f -> show();
}

void browse::on_browseclient_pushButton_clicked()
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
    model->select(); // 从表中获取数据
    ui->tableView->setModel(model); // 将model设置为TableView的Model
}

void browse::on_browsemedicine_pushButton_clicked()
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
    model->select(); // 从表中获取数据
    ui->tableView->setModel(model); // 将model设置为TableView的Model
}

void browse::on_browseorder_pushButton_clicked()
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
    model->select(); // 从表中获取数据
    ui->tableView->setModel(model); // 将model设置为TableView的Model
}

void browse::on_browsepurchase_pushButton_clicked()
{
    model->setTable("purchase");
    model->setHeaderData(0, Qt::Horizontal,tr("编号"));
    model->setHeaderData(1, Qt::Horizontal,tr("入库药品"));
    model->setHeaderData(2, Qt::Horizontal,tr("入库时间"));
    model->setHeaderData(3, Qt::Horizontal,tr("过期时间"));
    model->setHeaderData(4, Qt::Horizontal,tr("经办人"));
    model->setHeaderData(5, Qt::Horizontal,tr("备注"));
    model->select(); // 从表中获取数据
    ui->tableView->setModel(model); // 将model设置为TableView的Model
}

void browse::on_save_pushButton_clicked()
{
    if(alterauth == "有")
    {
        model->database().transaction(); // 开启事务

        if (model->submitAll()) {
            model->database().commit(); // 提交事务
            QMessageBox::information(this, tr("提示"), tr("修改成功！"), QMessageBox::Ok);
        } else {
            model->database().rollback(); // 回滚事务
            //        QMessageBox::warning(this, tr("Table Model"), tr("数据库错误: %1").arg(model->lastError().text()));
            QMessageBox::information(this, tr("提示"), tr("修改失败，无法访问数据库！"), QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::information(this, "警告", "没有权限");
    }
}

void browse::on_del_pushButton_clicked()
{
    if(deleteauth == "有")
    {
        // 获取选中的行
        int curRow = ui->tableView->currentIndex().row();

        // 删除该行
        model->removeRow(curRow);
        int ok = QMessageBox::warning(this,tr("删除当前行!"),
                                      tr("你确定删除当前行吗？"), QMessageBox::Yes, QMessageBox::No);
        if(ok == QMessageBox::No)
        { // 如果不删除，则撤销
            model->revertAll();
        } else { // 否则提交，在数据库中删除该行
            model->submitAll();
        }
    }
    else
    {
        QMessageBox::information(this, "警告", "没有权限");
    }
}

void browse::on_enter_pushButton_clicked()
{
    if(enterauth == "有")
    {
        // 获得表的行数
        int rowNum = model->rowCount();
        int id = 10;

        // 添加一行
        model->insertRow(rowNum);
        model->setData(model->index(rowNum, 0), id);

        // 可以直接提交
        //model->submitAll();
    }
    else
    {
        QMessageBox::information(this, "警告", "没有权限");
    }
}

void browse::on_revert_pushButton_clicked()
{
    if(alterauth == "有")
    {
        model->revertAll();
    }
    else
    {
        QMessageBox::information(this, "警告", "没有权限");
    }
}

void browse::on_export_pushButton_clicked()
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
