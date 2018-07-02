#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMinimumSize(650, 600);
    setMaximumSize(650, 600);

    //time
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showtime()));

    timesec = 0;
    timemin = 0;
    timehr = 0;
    QString s = " " + QString::number(timehr) + " : " + QString::number(timemin) + " : " + QString::number(timesec);
    ui->label_3->setText(s);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//put map on the board
void MainWindow::set(Sudoku su)
{
    for (int i = 0; i < 81; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(su.getElement(i)));
        string s = "";

        ui->tableWidget->setItem(i/9, i%9, item);

        //only zero can change, other can't change numbers
        if (su.getElement(i) != 0)
        {
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        else
        {
            ui->tableWidget->setItem(i/9, i%9, new QTableWidgetItem(QString::fromStdString(s)));
        }

        //map block style (middle & color)
        ui->tableWidget->item(i/9, i%9)->setTextAlignment(Qt::AlignHCenter |  Qt::AlignVCenter);

        if (i/9 < 3 || i/9 >= 6)
        {
            if (i%9 < 3 || i%9 >= 6)
            {
                ui->tableWidget->item(i/9, i%9)->setBackground(Qt::lightGray);
            }
            else
            {
                ui->tableWidget->item(i/9, i%9)->setBackground(Qt::white);
            }
        }
        else
        {
            if (i%9 >= 3 && i%9 < 6)
            {
                ui->tableWidget->item(i/9, i%9)->setBackground(Qt::lightGray);
            }
            else
            {
                ui->tableWidget->item(i/9, i%9)->setBackground(Qt::white);
            }
        }

    }
}

//get map on the board
void MainWindow::get(Sudoku & su)
{
    for (int i = 0; i < 81; ++i)
    {
        QString element = ui->tableWidget->item(i/9, i%9)->text();
        su.setElement(i, element.toInt());
    }
}

//check if the map can be solve i.e. check errors
bool MainWindow::check_error(Sudoku & su)
{
    get(su);

    for (int i = 0; i < 81; i++)
    {
        if (su.getElement(i) != 0)
        {
            if(su.getElement(i) != final_answer.getElement(i))
            {
                ui->tableWidget->item(i/9, i%9)->setBackground(Qt::red);

                return false;
            }
        }
    }

    return true;
}

//record time
void MainWindow::showtime()
{
    timesec++;
    if (timesec >= 60)
    {
        timemin++;
        timesec = 0;
    }

    if (timemin >= 60)
    {
        timehr++;
        timemin = 0;
    }

    QString s = " " + QString::number(timehr) + " : " + QString::number(timemin) + " : " + QString::number(timesec);
    ui->label_3->setText(s);
}

//start button
//create sudoku map that can be solved
void MainWindow::on_pushButton_clicked()
{
    Sudoku ques;
    Sudoku ques_cansolve;

    if (ques.create(ques, ques_cansolve))
    {
        final_answer = ques;
        first_question = ques_cansolve;

        for (int i = 0; i < 81; i++)
        {
            set(ques_cansolve);
        }
    }

    ui->label->setText(tr(""));

    //time start
    timesec = 0;
    timemin = 0;
    timehr = 0;
    QString s = " " + QString::number(timehr) + " : " + QString::number(timemin) + " : " + QString::number(timesec);
    ui->label_3->setText(s);
    timer->start(1000);

}

//game pause
//time pause, map store to temp, the block become black
void MainWindow::on_pushButton_2_clicked()
{   
    if (ui->pushButton_2->text() == "Pause")
    {
        ui->pushButton_2->setText(tr("Restart"));
        timer->stop();
        get(temp);


        for (int i = 0; i < 81; i++)
        {
            ui->tableWidget->item(i/9, i%9)->setText("");
            ui->tableWidget->item(i/9, i%9)->setTextAlignment(Qt::AlignHCenter |  Qt::AlignVCenter);
            ui->tableWidget->item(i/9, i%9)->setBackground(Qt::black);
        }
    }
    else
    {
        ui->pushButton_2->setText(tr("Pause"));
        timer->start(1000);
        set(temp);
    }

}

//solve map
void MainWindow::on_pushButton_3_clicked()
{
    Sudoku ques;
    Sudoku ans;

    get(ques);


    if (check_error(ques) && ques.solve(ques, ans))
    {
        set(ans);
        QMessageBox::about(this, "Finish", "Congradulation!\nYou solve the sudoku.");
    }
    else
    {
        QMessageBox::about(this, "Finish", "Wrong answer!");
        set(first_question);
    }


}

//click block, lighten the same numbers
//find possible chioces if tip is on
void MainWindow::on_tableWidget_itemPressed(QTableWidgetItem *item)
{
    Sudoku ques;
    QString number = item->text();

    for (int i = 0; i < 81; i++)
    {
        QString element = ui->tableWidget->item(i/9, i%9)->text();
        ques.setElement(i, element.toInt());

        //if numbers is equal to the item, then lighten them
        if (number == ui->tableWidget->item(i/9, i%9)->text() && number != "0" && number != "")
        {
            ui->tableWidget->item(i/9, i%9)->setBackground(Qt::green);
        }
        else
        {
            if (i/9 < 3 || i/9 >= 6)
            {
                if (i%9 < 3 || i%9 >= 6)
                {
                    ui->tableWidget->item(i/9, i%9)->setBackground(Qt::lightGray);
                }
                else
                {
                    ui->tableWidget->item(i/9, i%9)->setBackground(Qt::white);
                }
            }
            else
            {
                if (i%9 >= 3 && i%9 < 6)
                {
                    ui->tableWidget->item(i/9, i%9)->setBackground(Qt::lightGray);
                }
                else
                {
                    ui->tableWidget->item(i/9, i%9)->setBackground(Qt::white);
                }
            }
        }
    }

    //when tip is on, show possible numbers
    if (ui->pushButton_6->text() == "Tip On")
    {
        if (number == "")
        {
            //find available choices
            vector<int> avail = ques.find(ques,item->row()*9+item->column());
            QVector<int> q_avail = QVector<int>::fromStdVector(avail);
            QString s = "The possible numbers: ";

            for (int i = 0; i < q_avail.size(); i++)
            {
                s += QString::number(q_avail[i]) + " ";
            }
            ui->label->setText(s);

        }
        else
        {
            ui->label->setText("");
        }
    }
}

//start create custom map, clear board
void MainWindow::on_pushButton_4_clicked()
{
    ui->tableWidget->clear();
    ui->label->setText(tr("You can create your own sudoku map now."));

    timer->stop();
    timesec = 0;
    timemin = 0;
    timehr = 0;
    QString s = " " + QString::number(timehr) + " : " + QString::number(timemin) + " : " + QString::number(timesec);
    ui->label_3->setText(s);
}

//check every element, then mark the wrong ones
void MainWindow::on_pushButton_5_clicked()
{
    Sudoku ques;

    get(ques);

    for (int i = 0; i < 81; i++)
    {
        if (ques.getElement(i) != 0)
        {
            if(ques.getElement(i) != final_answer.getElement(i))
            {
                ui->tableWidget->item(i/9, i%9)->setBackground(Qt::red);
            }
        }
    }
}

//tip on or off show possible numbers when click on specific block
void MainWindow::on_pushButton_6_clicked()
{
    if (ui->pushButton_6->text() == "Tip Off")
    {
        ui->pushButton_6->setText(tr("Tip On"));
    }
    else
    {
        ui->pushButton_6->setText(tr("Tip Off"));
        ui->label->setText("");
    }
}


