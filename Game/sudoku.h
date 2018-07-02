#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Sudoku {
public:
    Sudoku();
    Sudoku(const int init_map[]);
    void setMap(const int set_map[]);
    int getElement(int index);
    void setElement(int index, int value);
    int getFirstZeroIndex();
    bool isCorrect();
    bool solve(Sudoku question, Sudoku & answer);
    bool create(Sudoku & question, Sudoku & question_cansolve);
    vector<int> find(Sudoku question, int index);
    static const int sudokuSize = 81;

private:
    bool checkUnity(int arr[]);
    int map[sudokuSize];
};


#endif // SUDOKU_H
