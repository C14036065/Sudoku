#ifndef BOARD_H
#define BOARD_H

#include "sudoku.h"
#include <QWidget>
#include <QPushButton>

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = 0);

Q_SIGNALS:
    //bool solve(Sudoku question, Sudoku & answer);

private slots:
    void setup();
    void start();
    void



private:
    QPushButton *reset;

};





#endif // BOARD_H
