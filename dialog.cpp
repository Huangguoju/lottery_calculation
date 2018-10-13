#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    init();
}

Dialog::init()
{
    QDate curDate = QDate::currentDate();
    ui->deleteDateEdit->setDate(curDate);
    ui->deleteAllcheckBox->setChecked(false);
    ui->deleteAllcheckBox_2->setChecked(true);
    ui->deletePrimalDataBox->setChecked(false);
    return 0;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    QString user = ui->userEdit->text();
    QString pass = ui->passEdit->text();
    bool isDeleteAll = ui->deleteAllcheckBox->isChecked();
    bool isDeleteCount = ui->deleteAllcheckBox_2->isChecked();
    bool isPrimalData = ui->deletePrimalDataBox->isChecked();
    QDate date = ui->deleteDateEdit->date();
    QString datestr = date.toString("yyyy-MM-dd");
    QSqlQuery query;
    if(user == "admin" && pass == "123"){
        if(isDeleteAll){
            if(isDeleteCount)
                query.exec("delete from lottery");
            if(isPrimalData)
                query.exec("delete from primal_data");
        } else {
            if(isDeleteCount){
                QString str = QString("delete from lottery where RECORD_DATE = '%1'").arg(datestr);
                query.exec(str);
            }
            if(isPrimalData){
                QString str = QString("delete from primal_data where RECORD_DATE = '%1'").arg(datestr);
                query.exec(str);
            }
        }
        QMessageBox msgBox;
        msgBox.setText("The SQL has been deleted.  ");
        msgBox.exec();
    } else {
        QMessageBox msgBox;
        msgBox.setText("admin or password err .  ");
        msgBox.exec();
    }
}
