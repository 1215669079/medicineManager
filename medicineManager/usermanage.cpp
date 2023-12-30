#include "usermanage.h"
#include "ui_usermanage.h"
#include "function.h"
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>
// 在代码中使用QXlsx库
#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include <QFileDialog>

usermanage::usermanage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usermanage)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked); // 允许双击编辑
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // 允许整行选择
    model->setTable("agency");
    model->setHeaderData(0, Qt::Horizontal,tr("编号"));
    model->setHeaderData(1, Qt::Horizontal,tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal,tr("性别"));
    model->setHeaderData(3, Qt::Horizontal,tr("电话"));
    model->setHeaderData(4, Qt::Horizontal,tr("密码"));
    model->setHeaderData(5, Qt::Horizontal,tr("备注"));
    model->setHeaderData(6, Qt::Horizontal,tr("管理权限"));
    model->setHeaderData(7, Qt::Horizontal,tr("查询权限"));
    model->setHeaderData(8, Qt::Horizontal,tr("浏览权限"));
    model->setHeaderData(9, Qt::Horizontal,tr("录入权限"));
    model->setHeaderData(10, Qt::Horizontal,tr("删除权限"));
    model->setHeaderData(11, Qt::Horizontal,tr("修改权限"));
    model->setHeaderData(12, Qt::Horizontal,tr("报表权限"));
    model->select(); // 从表中获取数据
    ui->tableView->setModel(model); // 将model设置为TableView的Model
}

usermanage::~usermanage()
{
    delete ui;
}

void usermanage::on_cancleButton_clicked()
{
    function *f = new function;
    this -> hide();
    f -> show();
}

void usermanage::on_export_pushButton_clicked()
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

void usermanage::on_enter_pushButton_clicked()
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

void usermanage::on_del_pushButton_clicked()
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

void usermanage::on_revert_pushButton_clicked()
{
    model->revertAll();
}

void usermanage::on_save_pushButton_clicked()
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
