#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QLabel"
#include <QVector>
#include <QtSql>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void init();
    void initdata();
    void refresh();
private slots:

    void on_lineEdit_2_returnPressed();

    void on_revocationButton_clicked();

    void on_reInitButton_clicked();

    void on_saveDataButton_clicked();

    void on_queryDataButton_clicked();


    void on_checkMarkedButton_clicked();

    void on_deleteSqlButton_clicked();

    void on_primalQueryButton_clicked();

    void on_lineEditRed1_returnPressed();

    void on_lineEditRed2_returnPressed();

    void on_lineEditRed3_returnPressed();

    void on_lineEditRed4_returnPressed();

    void on_lineEditRed5_returnPressed();

    void on_lineEditRed6_returnPressed();

    void on_primalImportButton_clicked();

    void on_lineEditRed1_textEdited(const QString &arg1);

    void on_lineEditRed2_textEdited(const QString &arg1);

    void on_lineEditRed3_textEdited(const QString &arg1);

    void on_lineEditRed4_textEdited(const QString &arg1);

    void on_lineEditRed5_textEdited(const QString &arg1);

    void on_lineEditRed6_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QList<QLabel *> QLabel_Red_list;
    QList<QLabel *> QLabel_Blue_list;
    int red_count[33];
    int blue_count[16];

    int input_count;
    QSqlDatabase db;
    QDate curDate;
    int primal_red[7];
    int primal_blue;
    int primalRedCount;//红球输入数
    int primalBlueCount;//蓝球输入数

};

#endif // MAINWINDOW_H
