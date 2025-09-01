#include <iostream>
#include <random>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;
//____________Player__________________
struct Player
{
    string name;
    char symbol;

    Player(int order, char s)
    {
        cout << "Welcome player " << order << endl;
        cout << "please enter your name : ";
        cin >> name;
        symbol = s;

    }
    void get_move(int& x, int& y)
    {
        cout << "Please enter your move x and y separated by spaces: ";
        cin >> x >> y;
        cout << endl;
    }
    char get_symbol()
    {
        return symbol;
    }
    string to_string()
    {
        return "player : " + name;
    }

};
//________________Board________________
struct Board
{
    int rows;
    int colm;
    char** grid;
    int moves;
    Board() {};
    Board(int n, int m)
    {
        rows = n;
        colm = m;
        moves = 0;
        grid = new char* [n];
        for (int i = 1;i <= n;i++)
        {
            grid[i] = new char[m];
            for (int j = 1;j <= m;j++)
            {
                grid[i][j] = 0;
            }
        }
    }
    bool isvalid(int i, int j)
    {
        return i > 0 && i <= rows && j > 0 && j <= colm;
    }
    bool isnear(int i, int j)
    {
        int x[] = { 1,1,0,-1,-1,-1,0,1 };
        int y[] = { 0,1,1,1,0,-1,-1,-1 };
        bool ok = false;
        for (int k = 0;k < 8;k++)
        {
            int a = i + x[k];
            int b = j + y[k];
            if (isvalid(a, b))
            {
                if (grid[a][b] == 'O' || grid[a][b] == 'X')
                {
                    ok = true;
                }
            }
        }
        return ok;
    }
    bool IsWinner()
    {
        for (int i = 1;i <= rows;i++)
        {
            for (int j = 1;j <= colm - 2;j++)
            {
                if (grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j] != 0)
                {
                    if (grid[i][j] != 0 && grid[i][j + 1] != 0 && grid[i][j + 2] != 0)
                        return true;
                }

            }
        }
        for (int i = 1;i <= rows - 2;i++)
        {
            for (int j = 1;j <= colm;j++)
            {
                if (grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j])
                {
                    if (grid[i][j] != 0 && grid[i + 1][j] != 0 && grid[i + 2][j] != 0)
                        return true;
                }
            }
        }
        for (int i = 1;i <= rows - 2;i++)
        {
            for (int j = 1;j <= colm;j++)
            {
                if (j <= colm / 2)
                {
                    if (grid[i][j] == grid[i + 1][j + 1] && grid[i + 1][j + 1] == grid[i + 2][j + 2])
                    {
                        if (grid[i][j] != 0 && grid[i + 1][j + 1] != 0 && grid[i + 2][j + 2] != 0)
                            return true;
                    }
                }
                if (colm % 2 != 0 && j == (colm / 2) + 1)
                {
                    if (grid[i][j] == grid[i + 1][j + 1] && grid[i + 1][j + 1] == grid[i + 2][j + 2])
                    {
                        if (grid[i][j] != 0 && grid[i + 1][j + 1] != 0 && grid[i + 2][j + 2] != 0)
                            return true;
                    }
                    if (grid[i][j] == grid[i + 1][j - 1] && grid[i + 1][j - 1] == grid[i + 2][j - 2])
                    {
                        if (grid[i][j] != 0 && grid[i + 1][j - 1] != 0 && grid[i + 2][j - 2] != 0)
                            return true;
                    }
                }

            }
        }
        for (int i = 1;i <= rows - 2;i++)
        {
            for (int j = colm / 2 + 1;j <= colm;j++)
            {
                if (grid[i][j] == grid[i + 1][j - 1] && grid[i + 1][j - 1] == grid[i + 2][j - 2])
                {
                    if (grid[i][j] != 0 && grid[i + 1][j - 1] != 0 && grid[i + 2][j - 2] != 0)
                        return true;
                }
            }
        }
        return false;
    }
    bool IsDraw()
    {
        return (moves == rows * colm && !IsWinner());
    }
    int CheckWinner()
    {
        for (int i = 1;i <= rows;i++)
        {
            for (int j = 1;j <= colm - 2;j++)
            {
                if (grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2])
                {
                    if (grid[i][j] != 0 && grid[i][j + 1] != 0 && grid[i][j + 2] != 0)
                    {
                        if (grid[i][j] == 'O')
                            return -2;
                        if (grid[i][j] == 'X')
                            return 2;
                    }
                }

            }
        }
        for (int i = 1;i <= rows - 2;i++)
        {
            for (int j = 1;j <= colm;j++)
            {
                if (grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j])
                {
                    if (grid[i][j] != 0 && grid[i + 1][j] != 0 && grid[i + 2][j] != 0)
                    {
                        if (grid[i][j] == 'O')
                            return -2;
                        if (grid[i][j] == 'X')
                            return 2;
                    }
                }
            }
        }
        for (int i = 1;i <= rows - 2;i++)
        {
            for (int j = 1;j <= colm;j++)
            {
                if (j <= colm / 2)
                {
                    if (grid[i][j] == grid[i + 1][j + 1] && grid[i + 1][j + 1] == grid[i + 2][j + 2])
                    {
                        if (grid[i][j] != 0 && grid[i + 1][j + 1] != 0 && grid[i + 2][j + 2] != 0)
                        {
                            if (grid[i][j] == 'O')
                                return -2;
                            if (grid[i][j] == 'X')
                                return 2;
                        }
                    }
                }
                if (colm % 2 != 0 && j == (colm / 2) + 1)
                {
                    if (grid[i][j] == grid[i + 1][j + 1] && grid[i + 1][j + 1] == grid[i + 2][j + 2])
                    {
                        if (grid[i][j] != 0 && grid[i + 1][j + 1] != 0 && grid[i + 2][j + 2] != 0)
                        {
                            if (grid[i][j] == 'O')
                                return -2;
                            if (grid[i][j] == 'X')
                                return 2;
                        }
                    }
                    if (grid[i][j] == grid[i + 1][j - 1] && grid[i + 1][j - 1] == grid[i + 2][j - 2])
                    {
                        if (grid[i][j] != 0 && grid[i + 1][j - 1] != 0 && grid[i + 2][j - 2] != 0)
                        {
                            if (grid[i][j] == 'O')
                                return -2;
                            if (grid[i][j] == 'X')
                                return 2;
                        }
                    }
                }
            }
        }
        for (int i = 1;i <= rows - 2;i++)
        {
            for (int j = colm / 2 + 1;j <= colm;j++)
            {
                if (grid[i][j] == grid[i + 1][j - 1] && grid[i + 1][j - 1] == grid[i + 2][j - 2])
                {
                    if (grid[i][j] != 0 && grid[i + 1][j - 1] != 0 && grid[i + 2][j - 2] != 0)
                    {
                        if (grid[i][j] == 'O')
                            return -2;
                        if (grid[i][j] == 'X')
                            return 2;
                    }
                }
            }
        }
        bool isdraw = true;
        for (int i = 1;i <= rows;i++)
        {
            for (int j = 1;j <= colm;j++)
            {
                if (grid[i][j] == 0)
                    isdraw = false;
            }
        }
        if (isdraw == true)
            return 0;
        return 1;

    }
    bool game_is_over()
    {
        return moves >= rows * colm;
    }
    bool UpdateBoard(int x, int y, char symbol)
    {
        if ((x > 0 || x <= rows || y > 0 || y <= colm) && grid[x][y] == 0)
        {
            grid[x][y] = toupper(symbol);
            moves++;
            return true;
        }
        else
        {
            cout << "The index you insert is not correct" << endl;
            return false;
        }
    }
    void Display()
    {
        cout << "  ";
        for (int i = 1;i <= colm;i++)
        {
            cout << i << "  ";
        }
        cout << endl;
        for (int i = 1;i <= rows;i++)
        {
            cout << i << " ";
            for (int j = 1;j <= colm;j++)
            {
                cout << grid[i][j] << "   ";
            }
            cout << endl;
            cout << endl;
        }
    }

};

//____________________Game_Manager_________________

struct GameManager
{
    Board* brd;
    Player* players[2];
    GameManager(Board* b, Player* pls[2])
    {
        brd = b;
        players[0] = pls[0];
        players[1] = pls[1];
    }
    void run()
    {
        int x, y;
        brd->Display();
        while (!brd->game_is_over())
        {
            for (int i : {0, 1})
            {
                players[i]->get_move(x, y);
                while (!brd->UpdateBoard(x, y, players[i]->get_symbol()))
                {
                    players[i]->get_move(x, y);
                }
                brd->Display();
                if (brd->IsWinner())
                {
                    cout << players[i]->to_string() << "Win" << endl;
                    return;
                }
                if (brd->IsDraw())
                {
                    cout << "Draw" << endl;
                    return;
                }
            }
        }
    }
};

//________________Ai_Player____________
struct AiPlayer
{
    string name;
    char symbol;
    int dimension;
    Board* brd;
    int numsteps;
    AiPlayer(int d, char s, Board* b)
    {
        name = "Computer Player";
        cout << "My name is : " << name << endl;
        dimension = d;
        symbol = s;
        brd = b;
        numsteps = 0;
    }
    int CheckWinner()
    {
        for (int i = 1;i <= brd->rows;i++)
        {
            for (int j = 1;j <= brd->colm - 2;j++)
            {
                if (brd->grid[i][j] == brd->grid[i][j + 1] && brd->grid[i][j + 1] == brd->grid[i][j + 2])
                {
                    if (brd->grid[i][j] != 0 && brd->grid[i][j + 1] != 0 && brd->grid[i][j + 2] != 0)
                    {
                        if (brd->grid[i][j] == 'O')
                            return -2;
                        if (brd->grid[i][j] == 'X')
                            return 2;
                    }
                }

            }
        }
        for (int i = 1;i <= brd->rows - 2;i++)
        {
            for (int j = 1;j <= brd->colm;j++)
            {
                if (brd->grid[i][j] == brd->grid[i + 1][j] && brd->grid[i + 1][j] == brd->grid[i + 2][j])
                {
                    if (brd->grid[i][j] != 0 && brd->grid[i + 1][j] != 0 && brd->grid[i + 2][j] != 0)
                    {
                        if (brd->grid[i][j] == 'O')
                            return -2;
                        if (brd->grid[i][j] == 'X')
                            return 2;
                    }
                }
            }
        }
        for (int i = 1;i <= brd->rows - 2;i++)
        {
            for (int j = 1;j <= brd->colm;j++)
            {
                if (j <= brd->colm / 2)
                {
                    if (brd->grid[i][j] == brd->grid[i + 1][j + 1] && brd->grid[i + 1][j + 1] == brd->grid[i + 2][j + 2])
                    {
                        if (brd->grid[i][j] != 0 && brd->grid[i + 1][j + 1] != 0 && brd->grid[i + 2][j + 2] != 0)
                        {
                            if (brd->grid[i][j] == 'O')
                                return -2;
                            if (brd->grid[i][j] == 'X')
                                return 2;
                        }
                    }
                }
                if (brd->colm % 2 != 0 && j == (brd->colm / 2) + 1)
                {
                    if (brd->grid[i][j] == brd->grid[i + 1][j + 1] && brd->grid[i + 1][j + 1] == brd->grid[i + 2][j + 2])
                    {
                        if (brd->grid[i][j] != 0 && brd->grid[i + 1][j + 1] != 0 && brd->grid[i + 2][j + 2] != 0)
                        {
                            if (brd->grid[i][j] == 'O')
                                return -2;
                            if (brd->grid[i][j] == 'X')
                                return 2;
                        }
                    }
                    if (brd->grid[i][j] == brd->grid[i + 1][j - 1] && brd->grid[i + 1][j - 1] == brd->grid[i + 2][j - 2])
                    {
                        if (brd->grid[i][j] != 0 && brd->grid[i + 1][j - 1] != 0 && brd->grid[i + 2][j - 2] != 0)
                        {
                            if (brd->grid[i][j] == 'O')
                                return -2;
                            if (brd->grid[i][j] == 'X')
                                return 2;
                        }
                    }
                }
            }
        }
        for (int i = 1;i <= brd->rows - 2;i++)
        {
            for (int j = brd->colm / 2 + 1;j <= brd->colm;j++)
            {
                if (brd->grid[i][j] == brd->grid[i + 1][j - 1] && brd->grid[i + 1][j - 1] == brd->grid[i + 2][j - 2])
                {
                    if (brd->grid[i][j] != 0 && brd->grid[i + 1][j - 1] != 0 && brd->grid[i + 2][j - 2] != 0)
                    {
                        if (brd->grid[i][j] == 'O')
                            return -2;
                        if (brd->grid[i][j] == 'X')
                            return 2;
                    }
                }
            }
        }
        bool isdraw = true;
        for (int i = 1;i <= brd->rows;i++)
        {
            for (int j = 1;j <= brd->colm;j++)
            {
                if (brd->grid[i][j] == 0)
                    isdraw = false;
            }
        }
        if (isdraw == true)
            return 0;
        return 1;

    }
    int z = 0;
    int mini_max(int& x, int& y, int depth, bool IsMaximizing, bool IsFirst, int alpha, int beta)
    {

        int res = CheckWinner();
        //cout<<res<<endl;
        if (depth == 0 || res != 1)
            return res;
        if (IsMaximizing)
        {
            int finalscore = -10;
            int finali, finalj;
            for (int i = 1;i <= brd->rows;i++)
            {
                for (int j = 1;j <= brd->colm;j++)
                {
                    if (brd->grid[i][j] == 0 && brd->isnear(i, j))
                    {
                        brd->grid[i][j] = 'X';
                        int score = mini_max(x, y, depth - 1, false, false, alpha, beta);
                        brd->grid[i][j] = 0;
                        if (score > finalscore)
                        {
                            //cout<<score<<endl;
                            finalscore = score;
                            finali = i;
                            finalj = j;
                        }
                        alpha = max(alpha, finalscore);
                        if (alpha >= beta)
                        {
                            break;
                        }
                        //if(IsFirst)
                            //cout<<i<<','<<j<<"score : "<<score<<endl;
                    }
                }
            }
            if (IsFirst)
            {
                x = finali;
                y = finalj;
                cout<<"computer played in indexes "<<x<<" and "<<y<<"."<<endl;
                cout<<endl;
            }
            return finalscore;

        }
        else
        {
            int finalscore = 10;
            int finali, finalj;
            for (int i = 1;i <= brd->rows;i++)
            {
                for (int j = 1;j <= brd->colm;j++)
                {
                    if (brd->grid[i][j] == 0 && brd->isnear(i, j))
                    {
                        brd->grid[i][j] = 'O';
                        int score = mini_max(x, y, depth - 1, true, false, alpha, beta);
                        brd->grid[i][j] = 0;
                        if (score < finalscore)
                        {
                            //cout<<score<<endl;
                            finalscore = score;
                            finali = i;
                            finalj = j;
                        }
                        beta = min(beta, finalscore);
                        if (beta <= alpha)
                        {
                            break;
                        }
                        //if(IsFirst)
                            //cout<<i<<','<<j<<"score : "<<score<<endl;
                    }
                }
            }
            if (IsFirst)
            {
                x = finali;
                y = finalj;
                cout<<"computer played in indexes "<<x<<" and "<<y<<"."<<endl;
                cout<<endl;
            }
            return finalscore;
        }
    }
    void get_move(int& x, int& y)
    {
        if (numsteps < 1)
        {
            get_rand_move(x, y);
            numsteps++;
        }
        else
        {
            mini_max(x, y, 6, false, true, INT_MIN, INT_MAX);
        }
    }
    char get_symbol()
    {
        return symbol;
    }
    string to_string()
    {
        return "Player : " + name;
    }
    void get_rand_move(int& x, int& y)
    {
        srand(time(0));
        x = (int)(rand() % (dimension)) + 1;
        y = (int)(rand() % (dimension)) + 1;
        cout<<"computer played in indexes "<<x<<" and "<<y<<"."<<endl;
        cout<<endl;
    }

};

struct GameManagerWithComputer
{
    Board* brd;
    Player* human;
    AiPlayer* computer;
    GameManagerWithComputer(Board* b, Player* h, AiPlayer* c)
    {
        brd = b;
        human = h;
        computer = c;
    }
    void run()
    {
        int x, y;
        brd->Display();
        while (!brd->game_is_over())
        {
            for (int i : {1, 0})
            {
                if (i == 0)
                {
                    human->get_move(x, y);
                    while (!brd->UpdateBoard(x, y, human->get_symbol()))
                    {
                        human->get_move(x, y);
                    }
                    brd->Display();
                    if (brd->IsWinner())
                    {
                        cout << human->to_string() << " Win" << endl;
                        return;
                    }
                    if (brd->IsDraw())
                    {
                        cout << "Draw" << endl;
                        return;
                    }
                }
                if (i == 1)
                {
                    computer->get_move(x, y);
                    while (!brd->UpdateBoard(x, y, computer->get_symbol()))
                    {
                        computer->get_move(x, y);
                    }
                    brd->Display();
                    if (brd->IsWinner())
                    {
                        cout << computer->to_string() << " Win" << endl;
                        return;
                    }
                    if (brd->IsDraw())
                    {
                        cout << "Draw" << endl;
                        return;
                    }
                }

            }
        }
    }
};

void display()
{
    cout << "-----------------Welcome to Tic Tac Toe Game--------------------" << endl;
    cout << endl;
    cout << "1. 3x3 Board game" << endl;
    cout << "2. 4x4 Board game" << endl;
    cout << "3. 5x5 Board game" << endl;
    cout << endl;
}
int main()
{
    display();
    int choose;
    int dim;
    cout << "Enter you choose : ";
    cin >> choose;
    Board* b;
    if (choose == 1)
    {
        b = new Board(3, 3);
        dim = 3;
    }
    else if (choose == 2)
    {
        b = new Board(4, 4);
        dim = 4;
    }
    else if (choose == 3)
    {
        b = new Board(5, 5);
        dim = 5;
    }
    else
    {
        cout << "your choose is not correct" << endl;
    }
    int choosePlayer;
    cout << "if you want to play with computer choose 1 " << endl;
    cout << "if you want to play with your friend choose 2 : ";
    cin >> choosePlayer;
    if (choosePlayer == 1)
    {
        Player* hum = new Player(1, 'X');
        AiPlayer* com = new AiPlayer(dim, 'O', b);
        GameManagerWithComputer* game = new GameManagerWithComputer(b, hum, com);
        game->run();
    }
    if (choosePlayer == 2)
    {
        Player* plays[2];
        plays[0] = new Player(1, 'X');
        plays[1] = new Player(2, 'O');
        GameManager* game = new GameManager(b, plays);
        game->run();
    }
    return 0;
}
