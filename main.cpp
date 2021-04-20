#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;
enum eDir {STOP=0,LEFT=1,UPLEFT=2,DOWNLEFT=3,RIGHT=4,UPRIGHT=5,DOWNRIGHT=6};
class cBall
{
private:
    int x;
    int y;
    eDir dir=STOP;
public :
    cBall(int posX,int posY)
    {
        x=posX;
        y=posY;
    }
    inline int getBallX(){return x;}
    inline int getBallY(){ return y;}
    inline int getDir(){ return dir;}
    inline void randDir(){dir=(eDir)(rand() % 6 + 1);}
    inline void newDir(eDir direction){dir=direction;}
    void MoveB()
    {
        switch(dir)
        {
        case STOP:
            break;
        case LEFT:
            y--;
            break;
        case UPLEFT:
            y--;
            x--;
            break;
        case DOWNLEFT:
            y--;
            x++;
            break;
        case RIGHT:
            y++;
            break;
        case UPRIGHT:
            y++;
            x--;
            break;
        case DOWNRIGHT:
            y++;
            x++;
            break;
        }
    }
    void setB(int a,int b)
    {
        x=a/2;;
        y=b/2;
        dir=STOP;
    }

};
class cPaddle
{
private :
    int x;
    int y;

public :
    cPaddle(int psX,int psY)
    {
        x=psX;
        y=psY;
    }
    inline int getPaX(){return x;}
    inline int getPaY(){return y;}
    void setP(int a,int b)
    {
        x=a;
        y=b;
    }
    inline void MoveUp(){x--;}
    inline void MoveDown(){x++;}

};
class cGame
{
    private:
        cBall *m;
        cPaddle *p1;
        cPaddle *p2;
        int score1,score2;
        char up1,up2,down1,down2;
        int w,h;
    public:
        cGame(int a,int b)
        {
            w=a;h=b;
            m=new cBall(h/2,w/2);
            p1=new cPaddle(h/2-2,1);
            p2=new cPaddle(h/2-2,w-2);
            up1='w';up2='i';
            down1='s';down2='k';
            score1=score2=0;
        }
        ~cGame()
    {
        delete m;
        delete p1;
        delete p2;
    }
    void ScoreUp(cPaddle * player)
    {
        if (player == p1)
            score1++;
        else if (player == p2)
            score2++;

        m->setB(h/2,w/2);
        p1->setP(h/2-2,1);
        p2->setP(h/2-2,w-2);
    }
void Draw()
    {
        system("cls");
        for (int i = 0; i < w ; i++)
            cout << "\xB2";
        cout << endl;

        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w+2; j++)
            {
                int bx = m->getBallX();
                int by = m->getBallY();
                int p1x = p1->getPaX();
                int p2x = p2->getPaX();
                int p1y = p1->getPaY();
                int p2y = p2->getPaY();
                if(j==0 or j==w-1)
                    cout << "\xB2";
                else if(bx==i and by==j)
                    cout << "O";
                else if(p1x==i and p1y==j)
                    cout << "\xDB";
                else if(p1x+1==i and p1y==j)
                    cout << "\xDB";
                else if(p1x+2==i and p1y==j)
                    cout << "\xDB";
                else if(p1x+3==i and p1y==j)
                    cout << "\xDB";
                else if(p2x==i and p2y==j)
                    cout << "\xDB";
                else if(p2x+1==i and p2y==j)
                    cout << "\xDB";
                else if(p2x+2==i and p2y==j)
                    cout << "\xDB";
                else if(p2x+3==i and p2y==j)
                    cout << "\xDB";
                else
                    cout << " ";
            }
            cout << endl;
        }
        for (int i = 0; i < w ; i++)
            cout << "\xB2";
        cout << endl;
        cout << "Scor 1: " << score1 << endl << "Scor 2: " << score2 << endl;
    }
    void Input()
    {
        m->MoveB();
        char current;
        int p1x = p1->getPaX();
        int p2x = p2->getPaX();
        if(_kbhit())
            current=_getch();
        if(current==up1)
        {
            if(p1x>0)
                p1->MoveUp();
        }
        if(current==up2)
        {
            if(p2x>0)
                p2->MoveUp();
        }
        if(current ==down1)
        {
            if(p1x+4<h)
                p1->MoveDown();
        }
        if(current==down2)
        {
            if(p2x+4<h)
                p2->MoveDown();
        }
        if(m->getDir()==STOP)
            m->randDir();
    }
    void Logic()
    {
        int bx = m->getBallX();
        int by = m->getBallY();
        int p1x = p1->getPaX();
        int p2x = p2->getPaX();
        int p1y = p1->getPaY();
        int p2y = p2->getPaY();

        for(int i=0;i<4;i++)
        {
            if(by==p1y+1 and bx==p1x+i)
                m->newDir(eDir(rand()%3+4));
        }
        for(int i=0;i<4;i++)
        {
            if(by==p2y-1 and bx==p2x+i)
                m->newDir(eDir(rand()%3+1));
        }
        if(bx==0)
            m->newDir(m->getDir() == UPLEFT ? DOWNLEFT : DOWNRIGHT);
        if(bx==h-1)
            m->newDir(m->getDir()==DOWNRIGHT ? UPRIGHT : UPLEFT);
        if(by==-1)
                ScoreUp(p2);
        if(by==w)
                ScoreUp(p1);
        }
   };
int main()
{
    srand(time(NULL));
   cGame c(32,16);
while(true)
{
    Sleep(100);
    c.Draw();
    c.Input();
    c.Logic();
}
}
