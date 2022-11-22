#include<iostream>
#include<cmath>

using namespace std;

int index1;
char board[9] = { '*','*','*','*','*','*','*','*','*' }; // наше гральне поле, де * вказує на пусту клітинку



int isFull()    //  перевірка на те, чи існують пусті клітинки на полі
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i] != 'X')
        {
            if (board[i] != 'O')
            {
                return 0;
            }
        }
    }
    return 1;
}



int user_won()   // перевірка на те,що переміг саме гравець, а не комп'ютер
{
    for (int i = 0; i < 9; i += 3)
    {
        if ((board[i] == board[i + 1]) && (board[i + 1] == board[i + 2]) && (board[i] == 'O'))
            return 1;
    }
    for (int i = 0; i < 3; i++)
    {
        if ((board[i] == board[i + 3]) && (board[i + 3] == board[i + 6]) && (board[i] == 'O'))
            return 1;
    }
    if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == 'O'))
    {
        return 1;
    }
    if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] == 'O'))
    {
        return 1;
    }
    return 0;
}


int cpu_won()  // перевірка на те, що переміг комп'ютер
{
    for (int i = 0; i < 9; i += 3)
    {
        if ((board[i] == board[i + 1]) && (board[i + 1] == board[i + 2]) && (board[i] == 'X'))
            return 1;
    }
    for (int i = 0; i < 3; i++)
    {
        if ((board[i] == board[i + 3]) && (board[i + 3] == board[i + 6]) && (board[i] == 'X'))
            return 1;
    }
    if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == 'X'))
    {
        return 1;
    }
    if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] == 'X'))
    {
        return 1;
    }
    return 0;
}


void draw_board() // функція для відображення ігрового поля, де * - пуста клітинка, Х - хрестик, який ставить комп'ютер і О - нулик, який ставить гравець
{
    cout << endl;
    cout << board[0] << "|" << board[1] << "|" << board[2] << endl;
    cout << "-----" << endl;
    cout << board[3] << "|" << board[4] << "|" << board[5] << endl;
    cout << "-----" << endl;
    cout << board[6] << "|" << board[7] << "|" << board[8] << endl;
}


int minimax_alpha_beta(bool flag, int alpha, int beta)   // реалізація алгоритму мінімаксу з альфа-бета відсіканнями
{

    int max_val = -1000, min_val = 1000;
    int i, j, value = 1;
    if (cpu_won() == 1)
    {
        return 10;
    }
    else if (user_won() == 1)
    {
        return -10;
    }
    else if (isFull() == 1)
    {
        return 0;
    }
    int score[9] = { 1,1,1,1,1,1,1,1,1 };

    for (i = 0; i < 9; i++)
    {
        if (board[i] == '*')
        {
            if (min_val > max_val) 
            {
                if (flag == true)
                {
                    board[i] = 'X';
                    value = minimax_alpha_beta(false, alpha, beta);
                }
                else
                {
                    board[i] = 'O';
                    value = minimax_alpha_beta(true, alpha, beta);
                }
                board[i] = '*';
                score[i] = value;
            }
        }
    }

    if (flag == true)
    {
        max_val = -1000;
        for (j = 0; j < 9; j++)
        {
            if (score[j] > max_val && score[j] != 1)
            {
                max_val = score[j];
                index1 = j;
            }
            alpha = max(alpha, max_val);
            if (beta <= alpha)
                break;
        }
        return max_val;
    }
    if (flag == false)
    {
        min_val = 1000;
        for (j = 0; j < 9; j++)
        {
            if (score[j] < min_val && score[j] != 1)
            {
                min_val = score[j];
                index1 = j;
            }
            beta = min(beta, min_val);
            if (beta <= alpha)
                break;
        }
        return min_val;
    }
}



int main()
{
    // UI з ігровим меню та запуск гри
    int move, choice;
    cout << "-------------------------TIC TAC TOE-----------------------------------------------------";
    cout << endl << "USER--->(O)      CPU------>(X)";
    cout << endl << "SELECT : 1-> Player first 2-> CPU first:";
    cin >> choice;
    if (choice == 1)
    {
        draw_board();
    up:cout << endl << "Enter the move:";
        cin >> move;
        if (board[move - 1] == '*')
        {
            board[move - 1] = 'O';
            draw_board();
        }
        else
        {
            cout << endl << "Invalid Move......Try different move";
            goto up;
        }
    }

    while (true)
    {

        cout << endl << "CPU MOVE....";
        minimax_alpha_beta(true, -1000, 1000);
        board[index1] = 'X';
        draw_board();
        if (cpu_won() == 1)
        {
            cout << endl << "CPU WON.....";
            break;
        }
        if (isFull() == 1)
        {
            cout << endl << "Draw....";
            break;
        }
    again:  cout << endl << "Enter the move:";
        cin >> move;
        if (board[move - 1] == '*')
        {
            board[move - 1] = 'O';
            draw_board();
        }
        else
        {
            cout << endl << "Invalid Move......Try different move";
            goto again;
        }
        if (user_won() == 1)
        {
            cout << endl << "You Won......";
            break;
        }
        if (isFull() == 1)
        {
            cout << endl << "Draw....";
            break;
        }
    }

}