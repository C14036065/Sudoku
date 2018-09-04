#include "sudoku.h"
#include <QDebug>
using namespace std;

Sudoku::Sudoku()
{
    for (int i = 0; i < sudokuSize; ++i)
    {
        map[i] = 0;
    }
}

Sudoku::Sudoku(const int init_map[])
{
    for (int i = 0; i < sudokuSize; ++i)
    {
        map[i] = init_map[i];
    }
}

void Sudoku::setMap(const int set_map[])
{
    for (int i = 0; i < sudokuSize; ++i)
    {
        map[i] = set_map[i];
    }
}

int Sudoku::getElement(int index)
{
    return map[index];
}

void Sudoku::setElement(int index, int value)
{
    map[index] = value;
}

int Sudoku::getFirstZeroIndex()
{
    for (int i = 0; i < sudokuSize; ++i)
    {
        if (map[i] == 0)
        {
            return i;
        }
    }

    return -1;
}

bool Sudoku::checkUnity(int arr[])
{
    //counters
    int arr_unity[9];

    //initialize
    for (int i = 0; i < 9; ++i)
    {
        arr_unity[i] = 0;
    }

    //count
    for (int i = 0; i < 9; ++i)
    {
        ++arr_unity[arr[i] - 1];
    }

    //all element must be 1
    for (int i = 0; i < 9; ++i)
    {
        if (arr_unity[i] != 1)
        {
            return false;
        }

    }

    return true;
}

bool Sudoku::isCorrect()
{
    bool check_result;
    int check_arr[9];
    int location;

    for (int i = 0; i < 81; i += 9)
    {
        for (int j = 0; j < 9; ++j)
        {
            check_arr[j] = map[i+j];
        }

        check_result = checkUnity(check_arr);

        if (check_result == false)
        {
            return false;
        }
    }

    for (int i = 0; i < 9; ++i)
    {
         for (int j = 0; j < 9; ++j)
         {
             check_arr[j] = map[i+9*j];
         }

         check_result = checkUnity(check_arr);

         if (check_result == false)
         {
             return false;
         }

    }

    for (int i = 0; i < 9; ++i)
    {
         for (int j = 0; j < 9; ++j)
         {
             location = 27*(i/3) + 3*(i%3) + 9*(j/3) + (j%3);
             check_arr[j] = map[location];
         }

         check_result = checkUnity(check_arr);

         if (check_result == false)
         {
             return false;
         }

    }

    return true;

}

bool Sudoku::solve(Sudoku question, Sudoku & answer)
{

    int firstZero;
    firstZero = question.getFirstZeroIndex();
    qDebug() << "location:" << firstZero;

    if (firstZero == -1)
    {
        //end condition
        if (question.isCorrect())
        {
            answer = question;

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        //find possible number, just try them
        vector<int> v = find(question, firstZero);
        qDebug() << "rest:" << v;


        for (int num = 0; num < v.size(); ++num)
        {
            question.setElement(firstZero, v[num]);

            qDebug() << "input:" << v[num];
            if (solve(question, answer))
            {
                return true;
            }



        }

        return false;
    }

}

//create sudoku map
bool Sudoku::create(Sudoku & question, Sudoku & question_cansolve)
{
    //create a random array
    //wash card algorithm
    int poker[9] = {0};
    for (int i = 0; i < 9; i++)
    {
        poker[i] = i+1;
    }



    int temp = 0;
    for (int i = 0; i < 9; i++)
    {
        //srand(time(NULL));
        int ran = rand() % 9;
        temp = poker[i];
        poker[i] = poker[ran];
        poker[ran] = temp;
    }

    for (int i = 0; i < 9; i++)
    {
        qDebug() << poker[i];
    }



    /*line1 : original
      line2 : shift 3 of line1
      line3 : shift 3 of line2
      line4 : shift 1 of line3
      line5 : shift 3 of line4
      line6 : shift 3 of line5
      line7 : shift 1 of line6
      line8 : shift 3 of line7
      line9 : shift 3 of line8
    */
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            question.setElement(i*9 + j, poker[j]);
        }

        //shift 1
        if (i == 2 || i == 5)
        {
            int head = poker[0];
            for (int k = 0; k < 8; ++k)
            {
                poker[k] = poker[k+1];
            }
            poker[8] = head;

        }
        //shift 3
        else
        {
            int temp;
            for (int k = 0; k < 3; ++k)
            {
                temp = poker[k];
                poker[k] = poker[(k+3)%9];
                poker[(k+3)%9] = poker[(k+6)%9];
                poker[(k+6)%9] = temp;
            }

        }
    }

    //let map have 0 to play
    question_cansolve = question;
    srand(time(NULL));
    int r;

    for (int i = 0; i < 50; i++)
    {
        r = rand() % 81 + 1;
        question_cansolve.setElement(r, 0);
    }



    return true;
}

//find the number which is not used before
vector<int> Sudoku::find(Sudoku question, int index)
{   
    vector<int> v;
    int r, c, lr, lc;
    bool  num[10] = {0};
    r = index/9;
    c = index%9;

    //collect the number has shown
    //check row
    for (int i = 0; i < 9; ++i)
    {
        num[question.getElement(r*9+i)] = true;
    }

    //check column
    for (int i = 0; i < 9; ++i)
    {
        num[question.getElement(c+i*9)] = true;
    }

    //check cells
    lr = r - (r%3);
    lc = c - (c%3);

    for (int i = lr; i < lr+3; ++i)
    {
        for (int j = lc; j < lc+3; ++j)
        {
            num[question.getElement(9*i+j)] = true;
        }
    }

    //if never be used, then be the possible number
    for (int i = 1; i < 10; i++)
    {
        if (num[i] == false)
        {
            v.push_back(i);
        }
    }

    return v;
}

