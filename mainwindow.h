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
    void on_lineEdit_returnPressed();

    void on_lineEdit_2_returnPressed();

    void on_revocationButton_clicked();

    void on_reInitButton_clicked();

    void on_saveDataButton_clicked();

    void on_queryDataButton_clicked();


    void on_checkMarkedButton_clicked();

    void on_deleteSqlButton_clicked();

    void on_primalQueryButton_clicked();

private:
    Ui::MainWindow *ui;
    QList<QLabel *> QLabel_Red_list;
    QList<QLabel *> QLabel_Blue_list;
    int red_count[33];
    int blue_count[16];
    int last_num;
    int last_isRed;
    int input_count;
    QSqlDatabase db;
    QDate curDate;
    int primal_red[128];
    int primal_blue[128];
    int primalRedCount;
    int primalBlueCount;

};

#endif // MAINWINDOW_H
