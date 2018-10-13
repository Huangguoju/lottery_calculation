#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableView>
#include <QDateEdit>
#include <Qpainter>
#include <dialog.h>

#if 1
QString create_sql = "create table lottery (id int primary key, name varchar(30), age int)";
QString select_max_sql = "select max(id) from lottery";
QString insert_sql = "insert into lottery values (?, ?, ?)";
QString update_sql = "update lottery set name = :name where id = :id";
QString select_sql = "select id, name from lottery";
QString select_all_sql = "select * from lottery";
QString delete_sql = "delete from lottery where id = ?";
QString clear_sql = "delete from lottery";
#endif



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    initdata();
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::init()
{
    QLabel_Red_list << ui->label_red1 << ui->label_red2 << ui->label_red3 << ui->label_red4 << ui->label_red5 \
                << ui->label_red6 << ui->label_red7 << ui->label_red8 << ui->label_red9 << ui->label_red10 \
                << ui->label_red11 << ui->label_red12 << ui->label_red13 << ui->label_red14 << ui->label_red15 \
                << ui->label_red16 << ui->label_red17 << ui->label_red18 << ui->label_red19 << ui->label_red20 \
                << ui->label_red21 << ui->label_red22 << ui->label_red23 << ui->label_red24 << ui->label_red25 \
                << ui->label_red26 << ui->label_red27 << ui->label_red28 << ui->label_red29 << ui->label_red30 \
                << ui->label_red31 << ui->label_red32 << ui->label_red33 ;

    QLabel_Blue_list << ui->label_blue1 << ui->label_blue2 << ui->label_blue3 << ui->label_blue4 << ui->label_blue5 \
                << ui->label_blue6 << ui->label_blue7 << ui->label_blue8 << ui->label_blue9 << ui->label_blue10 \
                << ui->label_blue11 << ui->label_blue12 << ui->label_blue13 << ui->label_blue14 << ui->label_blue15 \
                << ui->label_blue16 ;

    QRegExp regx("[0-9]+$");
    QValidator *validator;
    validator = new QRegExpValidator(regx, ui->lineEdit );
    ui->lineEdit->setValidator( validator );

    validator = new QRegExpValidator(regx, ui->lineEdit_2 );
    ui->lineEdit_2->setValidator( validator );

    validator = new QRegExpValidator(regx, ui->lineEdit_redTip );
    ui->lineEdit_redTip->setValidator( validator );
    validator = new QRegExpValidator(regx, ui->lineEdit_redTip1 );
    ui->lineEdit_redTip1->setValidator( validator );
    validator = new QRegExpValidator(regx, ui->lineEdit_blueTip );
    ui->lineEdit_blueTip->setValidator( validator );
    validator = new QRegExpValidator(regx, ui->lineEdit_blueTip1 );
    ui->lineEdit_blueTip1->setValidator( validator );

    curDate = QDate::currentDate();
    ui->dateEdit->setDate(curDate);
    ui->dateEdit_2->setDate(curDate);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("acidalia");
    db.setDatabaseName("custom.db");
    db.setUserName("admin");
    db.setPassword("123");
    db.open();

    QSqlQuery query;
    //query.exec(clear_sql);
    query.exec("CREATE TABLE IF NOT EXISTS lottery(       \
        ID INTEGER PRIMARY KEY  NOT NULL,   \
        NUM                     INTEGER,    \
        NUM_COUNT               INTEGER,    \
        COLOR                   TEXT,       \
        INPUT_COUNT             INTEGER,     \
        RECORD_DATE             TEXT    );");

    query.exec("CREATE TABLE IF NOT EXISTS primal_data(       \
        ID INTEGER PRIMARY KEY  NOT NULL,   \
        RED_ONE                 INTEGER,    \
        RED_TWO                 INTEGER,    \
        RED_THREE               INTEGER,    \
        RED_FOUR                INTEGER,    \
        RED_FIVE                INTEGER,    \
        RED_SIX                 INTEGER,    \
        BLUE                    INTEGER,    \
        INPUT_COUNT             INTEGER,     \
        RECORD_DATE             TEXT    );");
}

void MainWindow::initdata()
{

    for(int i = 0; i < 33; i++){

        QLabel_Red_list[i]->setText("0");
        QLabel_Red_list[i]->setStyleSheet("color:black;");
        red_count[i] = 0;
    }

    for(int i = 0; i < 16; i++){

        QLabel_Blue_list[i]->setText("0");
        QLabel_Blue_list[i]->setStyleSheet("color:black;");
        blue_count[i] = 0;
    }

    ui->label_last_num->setText("0");
    last_num = 0;

    ui->comboBox->setCurrentIndex(0);

    input_count = 0;

    ui->lineEdit_redTip->setText("0");
    ui->lineEdit_redTip1->setText("0");
    ui->lineEdit_blueTip->setText("0");
    ui->lineEdit_blueTip1->setText("0");

    refresh();



    memset(primal_red, 0, 128);
    memset(primal_blue, 0, 128);
    primalRedCount = 0;
    primalBlueCount = 0;

#if 0

    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("lottery");
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->select();

    //ID, NUM(1), NUM_COUNT, COLOR, INPUT_COUNT, RECORD_DATE(5)
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM_COUNT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("COLOR"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("INPUT_COUNT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("RECORD_DATE"));

    QTableView *view = new QTableView;
    view->setModel(model);
    view->hideColumn(0); // don't show the ID
    view->resize(700, 500);
    view->setWindowTitle("Table View");

    view->show();
#endif

}

//保存数据
void MainWindow::on_saveDataButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("The SQL will modified.");
    msgBox.setInformativeText("你确定要保存数据吗?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    if(msgBox.exec() != QMessageBox::Save)
        return;

    QSqlQuery query;
    QDate date = ui->dateEdit->date();
    QString datestr = date.toString("yyyy-MM-dd");

    //QTime    tmpTime;
    //tmpTime.start();

    db.transaction();
    for(int i = 0; i < 33; i++){

        QString str = QString("insert into lottery (NUM, NUM_COUNT, COLOR, INPUT_COUNT, RECORD_DATE) \
                            VALUES (%1, %2, '%3', %4, '%5');").arg(i).arg(red_count[i]).arg("red").arg(input_count).arg(datestr);

        query.exec(str);
    }
    for(int i = 0; i < 16; i++){

        QString str = QString("insert into lottery (NUM, NUM_COUNT, COLOR, INPUT_COUNT, RECORD_DATE) \
                            VALUES (%1, %2, '%3', %4, '%5');").arg(i).arg(blue_count[i]).arg("blue").arg(input_count).arg(datestr);
        query.exec(str);
    }
    db.commit();
    //QTime    tmpTime;
    //tmpTime.start();
    //qDebug() <<"10000条数据耗时："<<tmpTime.elapsed()<<"ms"<<endl;
    QMessageBox msgBox1;
    msgBox1.setText("数据保存成功 !!!.  ");
    msgBox1.exec();
    initdata();
}

//查询数据
void MainWindow::on_queryDataButton_clicked()
{
    QDate date = ui->dateEdit->date();
    QString startDate = date.toString("yyyy-MM-dd");
    QDate date1 = ui->dateEdit_2->date();
    QString endDate = date1.toString("yyyy-MM-dd");

    for(int i = 0; i < 33; i++){
        QLabel_Red_list[i]->setText("0");
        QLabel_Red_list[i]->setStyleSheet("color:black;");
        red_count[i] = 0;
    }

    for(int i = 0; i < 16; i++){
        QLabel_Blue_list[i]->setText("0");
        QLabel_Blue_list[i]->setStyleSheet("color:black;");
        blue_count[i] = 0;
    }
    input_count = 0;
    ui->label_last_num_3->setNum(input_count);
    ui->label_last_num_4->setNum(input_count/7);

    int num, num_count, input_count_sql = 0;
    int isNextRecord = 0;

    QString selectStr;
    if(ui->checkBox->isChecked())
        selectStr = QString("select * from lottery where RECORD_DATE >='%1' AND RECORD_DATE <='%2'").arg(startDate).arg(endDate);
    else
        selectStr = QString("select * from lottery where RECORD_DATE ='%1'").arg(startDate);

    QSqlQuery query(selectStr);

    //QSqlQuery query("select * from lottery");//查询表的内容
    //QSqlRecord record = query.record();

    //ID, NUM(1), NUM_COUNT, COLOR, INPUT_COUNT, RECORD_DATE(5)
    while (query.next()) {

        num = query.value(1).toInt();
        num_count = query.value(2).toInt();

        if(query.value(3).toString() == "red"){
            red_count[num] += num_count;
            QLabel_Red_list[num]->setNum(red_count[num]);

        } else {
            blue_count[num] += num_count;
            QLabel_Blue_list[num]->setNum(blue_count[num]);
        }

        if(isNextRecord == 0){
            input_count_sql = query.value(4).toInt();
            input_count += input_count_sql;
            ui->label_last_num_3->setNum(input_count);
            ui->label_last_num_4->setNum(input_count/7);
        }
        isNextRecord++;
        if(isNextRecord > 49)
        {
            isNextRecord = 0;

        }
        //qDebug() << column << num_count << color << date;

    }

    //qDebug() << "size:%d" << record.count();
}



void MainWindow::refresh()
{

    for(int i = 0; i < 33; i++){

        QString num = QString("%1").arg(red_count[i]);
        QLabel_Red_list[i]->setText(num);
    }

    for(int i = 0; i < 16; i++){
        QString num = QString("%1").arg(blue_count[i]);
        QLabel_Blue_list[i]->setText(num);
    }

    ui->label_last_num_3->setNum(input_count);
    ui->label_last_num_4->setNum(input_count/7);

}

//red  1  - 33
void MainWindow::on_lineEdit_returnPressed()
{

    if(ui->lineEdit->text().length() != 2){
        QMessageBox mesbox;
        mesbox.setText("长度必须为 2 ，请检查长度，如：02（正确），2（错误） !!!");
        mesbox.exec();
        return;
    }
    int linenum = ui->lineEdit->text().toInt();
    if(linenum > 33 || linenum <= 0)
        return;
    ui->lineEdit->clear();

    input_count += 1;
    if(ui->comboBox->currentIndex() == 0){
        red_count[linenum-1] += 1;

        last_num = linenum;
        last_isRed = 0;
        ui->label_last_num->setNum(last_num);
        QString s1 =QString::fromUtf8("（红球）");
        ui->label_last_num_2->setText(s1);

        // 输入源数据
        primal_red[primalRedCount] = linenum;
        primalRedCount++;

        if(primalRedCount + primalBlueCount == 35){
            //qDebug() << "primalRedCount + primalRedCount" << primalRedCount + primalBlueCount ;
            QDate date = ui->dateEdit->date();
            QString datestr = date.toString("yyyy-MM-dd");
            QSqlQuery query;
            int blue_tmp = 0;
            db.transaction();
            for(int i = 0; i < 30; ){

                query.prepare("INSERT INTO primal_data (RED_ONE, RED_TWO, RED_THREE, RED_FOUR, RED_FIVE, RED_SIX, BLUE, INPUT_COUNT, RECORD_DATE) "
                              "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
                query.addBindValue(primal_red[i++]);
                query.addBindValue(primal_red[i++]);
                query.addBindValue(primal_red[i++]);
                query.addBindValue(primal_red[i++]);
                query.addBindValue(primal_red[i++]);
                query.addBindValue(primal_red[i++]);
                query.addBindValue(primal_blue[blue_tmp++]);
                query.addBindValue(input_count);
                query.addBindValue(datestr);

                query.exec();
            }
            db.commit();
            memset(primal_red, 0, 128);
            memset(primal_blue, 0, 128);
            primalRedCount = 0;
            primalBlueCount = 0;
        }

    } else {
        //输入当期中奖号码
        QLabel_Red_list[linenum - 1]->setStyleSheet("color:red;");

        last_num = linenum;
        last_isRed = 0;
        ui->label_last_num->setNum(last_num);
        QString s1 =QString::fromUtf8("（红球）");
        ui->label_last_num_2->setText(s1);
    }
    refresh();


#if 0
    QMessageBox msgBox;
     msgBox.setText("The document has been modified.");
     msgBox.setInformativeText("Do you want to save your changes?");
     msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
     msgBox.setDefaultButton(QMessageBox::Save);
     int ret = msgBox.exec();
#endif

}

//blue  1 - 16
void MainWindow::on_lineEdit_2_returnPressed()
{
    if(ui->lineEdit_2->text().length() != 2){
        QMessageBox mesbox;
        mesbox.setText("长度必须为 2 ，请检查长度，如：02（正确），2（错误） !!!");
        mesbox.exec();
        return;
    }
    int linenum = ui->lineEdit_2->text().toInt();
    if(linenum > 16 || linenum <= 0)
        return;
    ui->lineEdit_2->clear();

    input_count += 1;

    if(ui->comboBox->currentIndex() == 0){

        blue_count[linenum-1] += 1;

        last_num = linenum;
        last_isRed = 1;
        ui->label_last_num->setNum(last_num);
        QString s1 =QString::fromUtf8("（蓝球）");
        ui->label_last_num_2->setText(s1);

        // 输入源数据
        primal_blue[primalBlueCount] = linenum;
        primalBlueCount++;

        if(primalRedCount + primalBlueCount == 35){
            //qDebug() << "primalRedCount + primalRedCount" << primalRedCount + primalBlueCount ;
            QDate date = ui->dateEdit->date();
            QString datestr = date.toString("yyyy-MM-dd");
            QSqlQuery query;
            int blue_tmp = 0;
            //QTime    tmpTime;
            //tmpTime.start();
            db.transaction();
            for(int i = 0; i < 30; ){

                query.prepare("INSERT INTO primal_data (RED_ONE, RED_TWO, RED_THREE, RED_FOUR, RED_FIVE, RED_SIX, BLUE, INPUT_COUNT, RECORD_DATE) "
                              "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
                query.addBindValue(primal_red[i++]);
                query.addBindValue(primal_red[i++]);
                query.addBindValue(primal_red[i++]);
                query.addBindValue(primal_red[i++]);
                query.addBindValue(primal_red[i++]);
                query.addBindValue(primal_red[i++]);
                query.addBindValue(primal_blue[blue_tmp++]);
                query.addBindValue(input_count);
                query.addBindValue(datestr);

                query.exec();
            }
            db.commit();
            //qDebug() <<"10000条数据耗时："<<tmpTime.elapsed()<<"ms"<<endl;
            memset(primal_red, 0, 128);
            memset(primal_blue, 0, 128);
            primalRedCount = 0;
            primalBlueCount = 0;
        }
    }
    else
    {
        //输入当期中奖号码
        QLabel_Blue_list[linenum - 1]->setStyleSheet("color:red;");

        last_num = linenum;
        last_isRed = 1;
        ui->label_last_num->setNum(last_num);
        QString s1 =QString::fromUtf8("（蓝球）");
        ui->label_last_num_2->setText(s1);
    }

    refresh();


}


void MainWindow::on_revocationButton_clicked()
{
    if(last_isRed == 2)
        return;
    if(last_isRed == 0){
        red_count[last_num-1] -= 1;
        primalRedCount -= 1;
    } else if (last_isRed == 1){
        blue_count[last_num-1] -= 1;
        primalBlueCount -= 1;
    }
    input_count -= 1;
    last_isRed = 2;


    refresh();

}

void MainWindow::on_reInitButton_clicked()
{
    initdata();
}

void MainWindow::on_checkMarkedButton_clicked()
{
    int redmixTip = ui->lineEdit_redTip->text().toInt();
    int redmaxTip = ui->lineEdit_redTip1->text().toInt();
    int bluemixTip = ui->lineEdit_blueTip->text().toInt();
    int bluemaxTip = ui->lineEdit_blueTip1->text().toInt();

    for(int i = 0;i < 33; i++){
        if(QLabel_Red_list[i]->text().toInt() >= redmixTip && QLabel_Red_list[i]->text().toInt() <= redmaxTip)
            if(redmixTip != 0 && redmaxTip != 0)
                QLabel_Red_list[i]->setStyleSheet("color:red;");
            else
                QLabel_Red_list[i]->setStyleSheet("color:black;");
        else
            QLabel_Red_list[i]->setStyleSheet("color:black;");
    }

    for(int i = 0;i < 16; i++){
        if(QLabel_Blue_list[i]->text().toInt() >= bluemixTip && QLabel_Blue_list[i]->text().toInt() <= bluemaxTip)
            if(bluemixTip != 0 && bluemaxTip != 0)
                QLabel_Blue_list[i]->setStyleSheet("color:red;");
            else
                QLabel_Blue_list[i]->setStyleSheet("color:black;");
        else
            QLabel_Blue_list[i]->setStyleSheet("color:black;");
    }

}

void MainWindow::on_deleteSqlButton_clicked()
{
    Dialog *dia = new Dialog(this);
    dia->exec();
}

void MainWindow::on_primalQueryButton_clicked()
{
#if 1

    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("primal_data");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    //ID, RED_ONE(1), RED_TWO, RED_THREE, RED_FOUR, RED_FIVE(5), RED_SIX, BLUE, INPUT_COUNT,RECORD_DATE(9)
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("RED_ONE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("RED_TWO"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("RED_THREE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("RED_FOUR"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("RED_FIVE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("RED_SIX"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("BLUE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("INPUT_COUNT"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("RECORD_DATE"));

    QTableView *view = new QTableView;
    view->setModel(model);
    view->hideColumn(0); // don't show the ID
    view->resize(1000, 500);
    view->setWindowTitle("Table View");

    view->show();
#endif

#if 1
    initdata();

    QDate date = ui->dateEdit->date();
    QString startDate = date.toString("yyyy-MM-dd");
    QDate date1 = ui->dateEdit_2->date();
    QString endDate = date1.toString("yyyy-MM-dd");

    QString selectStr;
    if(ui->checkBox->isChecked())
        selectStr = QString("select * from primal_data where RECORD_DATE >='%1' AND RECORD_DATE <='%2'").arg(startDate).arg(endDate);
    else
        selectStr = QString("select * from primal_data where RECORD_DATE ='%1'").arg(startDate);

    QSqlQuery query(selectStr);

    int row_count = 0;
    int red_one, red_two, red_three, red_four, red_five, red_six, blue = 0;

    //ID, RED_ONE(1), RED_TWO, RED_THREE, RED_FOUR, RED_FIVE, RED_SIX, BLUE(7), INPUT_COUNT, RECORD_DATE(9)
    while (query.next()) {

        red_one     = query.value(1).toInt();
        red_two     = query.value(2).toInt();
        red_three   = query.value(3).toInt();
        red_four    = query.value(4).toInt();
        red_five    = query.value(5).toInt();
        red_six     = query.value(6).toInt();
        blue        = query.value(7).toInt();

        if(red_one <= 0 || red_one > 33 || red_two <= 0 || red_two > 33 || red_three <= 0 || red_three > 33 \
                || red_four <= 0 || red_four > 33 || red_five <= 0 || red_five > 33 || red_six <= 0 || red_six > 33 \
                || blue <= 0 || blue > 16){

            QMessageBox mesbox;
            QString err = QString("数据有错误 !!! %1").arg(row_count);
            mesbox.setText(err);
            mesbox.exec();
            return;
        }


        red_count[red_one - 1] += 1;
        red_count[red_two - 1] += 1;
        red_count[red_three - 1] += 1;
        red_count[red_four - 1] += 1;
        red_count[red_five - 1] += 1;
        red_count[red_six - 1] += 1;
        blue_count[blue - 1] += 1;

        row_count += 1;
        //qDebug() << "row_count1222" ;
        //qDebug() << red_one << red_two << red_three << red_four << red_five << red_six << blue ;
        //qDebug() << row_count ;
        //qDebug() << red_six ;
    }
    //qDebug() << "row_count111" ;
    input_count = row_count * 7;

    refresh();




#endif


}
