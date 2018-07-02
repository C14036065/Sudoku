#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include "sudoku.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_tableWidget_itemPressed(QTableWidgetItem *item);

    void set(Sudoku su);

    void get(Sudoku & su);

    bool check_error(Sudoku & su);

    void showtime();





private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int timesec;
    int timemin;
    int timehr;
    bool check_start;
    Sudoku first_question;
    Sudoku final_answer;
    Sudoku temp;
};

#endif // MAINWINDOW_H
