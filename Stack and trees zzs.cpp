#include <iostream>
#include <vector>
#include <stack>
 
 
using namespace std;
 //1zad obqsnena v tetradka po sdp (moi si neshta pishe v neq)+list v 1vata tetradka po sdp
int H(int n, int x)
{
    if (n == 0)
    {
        return 1;
    }
    else if (n == 1)
    {
        return 2 * x;
    }
    else
    {
        return 2 * x*H(n - 1, x) + 2 * (n - 1) * H(n - 2, x);
    }
}
 

int Hstack2(int n, int x)
{
 
    if (n == 0)
    {
        return 1;
    }
    else if (n == 1)
    {
        return 2 * x;
    }
    stack<int> s;
    s.push(1);
    s.push(2 * x);
    int temp = 2;
    while (temp<=n)
    {
        int t = s.top();
        s.pop();
        int y = s.top();
        s.pop();
        s.push(t);
        s.push((2 * x)*t + 2 * (temp - 1)*y);
        temp++;
    }
    return s.top();
}
 int factorial(int n)
{
    stack<int> s;
    s.push(1);
    while (n > 1)
    {
        s.push(n);
        n--;
    }
    int mult = s.top();
    s.pop();
    while (!s.empty())
    {
        mult *= s.top();
        s.pop();
    }
    return mult;
}
 
int main()
{
    cout << H(3, 1) << endl;
    cout << Hstack2(3, 1);
    return 0;
}




//2ra zad HORSES
//obqsnena vuv 2rata tetradka po sdp(moi si neshta)
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <string.h>
#include <string>
#include <assert.h>
 
using namespace std;
#define MAX_SIZE 8
 
bool board[MAX_SIZE][MAX_SIZE] = { false };//zashto v takiv skobi
 
void printBoard(int size)
{
    cout << "+++++++++++++++++++\n";
    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            if (board[r][c])
                cout << "H ";
            else
                cout << "_ ";
 
        }
        cout << endl;
    }
    cout << "+++++++++++++++++++\n";
}
 
bool hasHorse(int r, int c, int size)
{
    return r >= 0 &&
        c >= 0 &&
        r < size &&
        c < size &&
        board[r][c];//da ni e true t.e da ima neshto na board-a
 
}
       
bool canPlaceHorse(int r, int c, int size)
{
    return !hasHorse(r - 2, c - 1, size) &&
        !hasHorse(r - 2, c + 1, size) &&
        !hasHorse(r - 1, c - 2, size) &&
        !hasHorse(r - 1, c + 2, size) &&
        !hasHorse(r + 1, c - 2, size) &&
        !hasHorse(r + 1, c + 2, size) &&
        !hasHorse(r + 2, c - 1, size) &&
        !hasHorse(r + 2, c + 1, size) &&
        !hasHorse(r, c, size);
}
 
 #define OPER_PLACE_HORSE 0
#define OPER_REMOVE_HORSE 1
#define OPER_FIND_SOLUTION 2
struct Operation {
    int operType;
    int k;
    int size;
    int r;
    int c;
    Operation(int _t,int _k,int _s):operType(_t),k(_k),size(_s){}//k is the number of horses
    Operation(int _t, int _k, int _s, int _r, int _c)
    :operType(_t), k(_k), size(_s), r(_r), c(_c){}
};
void configStack(int k, int size)
{
    stack<Operation> operations;
    operations.push(Operation(OPER_FIND_SOLUTION, k, size));
    while (!operations.empty())
    {
        Operation topOperation = operations.top();
        int k = topOperation.k;//tezi k i size koito sme podali
        int size = topOperation.size;
        operations.pop();
 
        if (k == 0)//if there aren't any horses
        {
            printBoard(size);
        }
        else if (topOperation.operType == OPER_PLACE_HORSE)
        {
            board[topOperation.r][topOperation.c] = true;
        }
        else if (topOperation.operType == OPER_REMOVE_HORSE)
        {
            board[topOperation.r][topOperation.c] = false;
        }
        else//if it is find solution
        {
            for (size_t r = 0; r < size; r++)
            {
                for (size_t c = 0; c < size; c++)
                {
                    if (canPlaceHorse(r, c, size))
                    {
                        operations.push(Operation(OPER_REMOVE_HORSE, 1, size,r,c));
                        operations.push(Operation(OPER_FIND_SOLUTION, k - 1, size));
                        operations.push(Operation(OPER_PLACE_HORSE, 1, size, r, c));
                    }
                }
            }
        }
    }
}
void config(int k, int size)
{
    if (k == 0)
    {
        printBoard(size);
        return;
    }
 
    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            if (canPlaceHorse(r, c, size))
            {
                    board[r][c] = true;
                    config(k - 1, size);
                    board[r][c] = false;
            }
        }
    }
 
}
int main()
{
    //config(2, 4);
    configStack(2, 3);
    return 0;
   
}
 
//3 ZAD
#include <iostream>
#include<iomanip>
 
#include <stack>
using namespace std;
#define maxsize 8
 
bool labirint[maxsize][maxsize] = { false };
 
void displayLabirint(int size)
{
    for (int r = 0; r<size; r++)
    {
        for (int c = 0; c<size; c++)
            cout << setw(4) << labirint[r][c];
 
        cout << endl;
    }
 
 
}
bool possibleMovement(int x, int y,int size)
{
    return (0 <= x) &&
        (0 <= y) &&
        (x <size) &&
        (y <=size) &&
        (!labirint[x][y]);
 
 
}
 
bool downstairs(int sx, int sy, int tx, int ty,int size)
 
{
    if (sx == tx&&sy == ty)
    {
        return true;
    }
 
    if (possibleMovement(sx, (sy + 1), size) && possibleMovement(sx + 1, sy, size))
        return downstairs(sx + 1, sy, tx, ty, size) || downstairs(sx, sy + 1, tx, ty, size);
    if (possibleMovement(sx, sy + 1, size))
        return downstairs(sx, sy + 1, tx, ty, size);
    if (possibleMovement(sx + 1, sy, size))
        return downstairs(sx + 1, sy, tx, ty, size);
    else
        return false;
 
 
 
}
 
 
struct Operation
{
 
    int r;
    int c;
 
    Operation(int _r, int _c)
        : r(_r), c(_c) {}
    //Operation (){}
};
 
bool downstairsStack(int xs, int ys, int xt, int yt,int size)
 
{
    stack<Operation> s;
    s.push(Operation(xs, ys));
   
    while (!s.empty())
 
    {
        Operation top = s.top();
        int xs = top.r;
        int ys = top.c;
        s.pop();
 
        if (xs== xt&&ys == yt)//ili ako ne pishem che xs=top.r tuk shte e (top.r==xs&&top.c==yt)
            return true;
 
        else if (possibleMovement(xs+ 1, top.c, size) && possibleMovement(top.r, ys + 1, size))
        {
            s.push(Operation((xs + 1), ys));
            s.push(Operation(xs, ys + 1));
        }
 
        else if (possibleMovement(xs + 1, ys, size))
            s.push(Operation((xs + 1), ys));
 
 
        else if (possibleMovement(xs, ys + 1, size))
            s.push(Operation(xs, ys + 1));
    }
    if (s.empty())
        return false;
}
 
//ako pisha int xs=top.r
/*bool downstairsStack(int xs,int ys,int xt,int yt)
 
{
    stack<Operation> s;
    s.push(Operation(   xs,ys));
 
    while(!s .empty())
 
    {
        Operation top=s.top();
        s.pop();
 
        if(top.r==xt&&top.c==yt)
            return 1;
 
        else if (possibleMovement(top.r+1,top.c)&&possibleMovement(top.r,top.c+1))
        {
            s.push(Operation((top.r+1),top.c));
            s.push(Operation( top.r ,top.c+1));
        }
 
           else if (possibleMovement(top.r+1,top.c) )
               s.push(Operation((top.r+1),top.c));
 
 
          else if ( possibleMovement(top.r,top.c+1))
                    s.push(Operation( top.r ,top.c+1));
    }
    if(s.empty())
        return false;
 
 
 
}*/
 
int main()
{
    displayLabirint(4);
    cout << downstairs(2, 0, 3, 3,4) << endl;
    cout << downstairs(1, 3, 0, 0,4) << endl;
    cout << downstairsStack(2, 0, 3, 3,4) << endl;
    cout << downstairsStack(1, 3, 0, 0, 4) << endl;
    return 0;
}
 
 
