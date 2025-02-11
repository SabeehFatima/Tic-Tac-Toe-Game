#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

void gotoRowCol(int rpos, int cpos)
{
    int xpos = cpos, ypos = rpos;
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}

void print_board_screen(int Dim,char c)//This function will print the board on screen.
{
   for(int i=1;i<(Dim*6);i++)
    {
        for(int j=1;j<(Dim*12);j++)
        {
            if(i%6==0 || j%12==0)
            {
                gotoRowCol(i,j);
                cout<<c;
            }
        }
    }
}

void init_array(char A[], int Dim)//In the start,there is space at every index in array.
{
    for (int i = 0; i < Dim * Dim; i++)
    {
        A[i] = ' ';
    }
}

void print_array(char A[],int Dim)//This is used for the alignment of array on the board.
{
    int row=3,col=6,rep;
    rep=col;

    for(int i=0;i<Dim*Dim;i++)
    {
        gotoRowCol(row,col);
        cout<<A[i];

        if(i%Dim==(Dim-1))
        {
            row=row+6;
            col=rep;
        }
        else
        {
            col=col+12;
        }

    }
}
void Symbol_array(char Symbol[])//Symbols that will be used to represent the two players in our game.
{
       Symbol[0]='O';
       Symbol[1]='X';
}


void turn_change(bool &turn)//changing turn according to the players.
{
    if(turn==1)
    {
        turn=0;
    }
    else
    {
        turn=1;
    }
}
void Ask_for_move(int & ri,int & ci,int turn,int Dim)//user will tell at which place he/she wants to move in the game.
{
    gotoRowCol(Dim*3,Dim*15);
    if(turn==0)//if turn is zero,turn will be given to player 1(O).
    {
        cout<<" Turn of player 1(O) ";
        gotoRowCol(Dim*3+1,Dim*15);
        cout<<" Enter row :";
        cin>>ri;
        gotoRowCol(Dim*3+2,Dim*15);
        cout<<" Enter column:";
        cin>>ci;
    }
    else//If turn is other than zero,turn will be given to player 2(X).
    {
        cout<<" Turn of player 2(X) ";
        gotoRowCol(Dim*3+1,Dim*15);
        cout<<" Enter row :";
        cin>>ri;
        gotoRowCol(Dim*3+2,Dim*15);
        cout<<" Enter column:";
        cin>>ci;
    }
        gotoRowCol(Dim*3+1,Dim*15);
        cout<<"                    ";
        gotoRowCol(Dim*3+2,Dim*15);
        cout<<"                    ";
}

int TwoD_to_OneD(int ri,int ci,int Dim)//Converts value at specific row column to specific index in array.
{

    return (ri-1)*Dim+(ci-1);


}

void  Write_on_Board(char A[],int ri,int ci,int Dim,int turn,char Symbol[])//This will print our symbol at the board.
{
    int a=TwoD_to_OneD(ri,ci,Dim);
    A[a]=Symbol[turn];
}


bool check_legality(char A[],int ri,int ci,int Dim,int turn,char Symbol[])//It checks whether the row column entered by user can be assessed or not.
{

    if(ri<=Dim && ci<=Dim && A[(ri-1)*Dim+(ci-1)]==' ')
    {
        A[(ri-1)*Dim+(ci-1)]=Symbol[turn];
        return true;
    }
    else
    {
        gotoRowCol(Dim*3+6,Dim*12+24);
        cout<<"This place is out of reach.Find another";
        return false;

    }
}
bool horizontal_win(char A[],int Dim,char Symbol[],bool turn)//If same characters are found in horizontal pattern.
{
     int count=0;
    for(int i=0;i<=Dim*Dim;i++)
    {
       if(A[i]==Symbol[turn])//checks every box in a horizontal line
       {
           count++;
       }
       if(count<Dim && i%Dim==(Dim-1))//ending at the last box of row.
       {
              count=0;
       }
    }
    if(count<Dim)
    {
        return 0;
    }
    else
    {
        return 1;
    }


}
bool vertical_win(char A[],int Dim,char Symbol[],bool turn)//If same characters are found in vertical pattern.
{
     int count=0;
    for(int i=0;i<=Dim;i++)
    {
        for(int j=0;j<=Dim;j++)
    {
       if(A[(i-1)*Dim+(j-1)]==Symbol[turn])//checks every box in a vertical line
       {
           count++;
       }
    }
      if(count<Dim)
        {
        count=0;
        }
     else
        {
        return 1;
        }
    }
    if(count<Dim)
    {
        return 0;
    }


}
bool diagonal_win(char A[],int Dim,char Symbol[],bool turn)
{
    int p=1,q=1,count=0;

    while(p<=Dim && q<=Dim)//Checking the main diagonal
    {

         if(A[(p-1)*Dim+(q-1)]==Symbol[turn])
       {
           count++;
       }
       p++;
       q--;
    }
  if(count<Dim)//Reseting the count and checking in the other diagonal
    {
        count=0,p=1,q=Dim;
        while(p<=Dim && q>=1)
        {
            if(A[(p-1)*Dim+(q-1)]==Symbol[turn])
            {
                count++;
            }
            p++;
            q--;
        }

     if(count<Dim)//if count less than dimension means no diagonal win
        {
            return 0;
        }
        else//Diagonal win in second diagonal
        {
            return 1;
        }
    }
  else//Diagonal win in main diagonal.
    {
        return 1;

    }
}
bool is_win(char A[],int Dim,char Symbol[],bool turn)//All the wins will be checked if any was done,it will be showed here.
{
    int win=horizontal_win(A,Dim,Symbol,turn)+ vertical_win( A,Dim,Symbol,turn)+ diagonal_win(A,Dim,Symbol,turn);
    return win;
}
bool is_draw(char A[],int Dim)//If all the places are filled but no one won.
{
  int count=0;
  for(int i=0;i<Dim*Dim;i++)
  {
      if(A[i]!=' ')
      {
          count++;
      }
     if(count<Dim*Dim)
     {
         return 0;
     }
     else
     {
         return 1;
     }


  }
}
void results(int win,int draw,bool turn)//For displaying the end results.
{
    if(win>0)
    {
        system("CLS");
        if(turn==0)
        {
             gotoRowCol(20,100);
             cout<<"Crown goes to player 1"<<endl;
        }
        else
        {
            gotoRowCol(20,100);
             cout<<"Crown goes to player 2"<<endl;
        }


    }
    else
    {
         system("CLS");
         gotoRowCol(20,100);
        cout<<"BAD LUCK."<<endl;
         gotoRowCol(21,100);
         cout<<"The match is draw"<<endl;

    }

}

int main()
{
    int Dim,win,draw;
    gotoRowCol(30,100);
    cout<<"Tic_Tac_Toe Game"<<endl;
    gotoRowCol(32,100);
    cout<<"PLAY"<<endl;
    gotoRowCol(34,100);
    cout << "Enter the dimension:";
    cin >> Dim;
    system("CLS");
    bool turn=1;
    char a;
    int ri,ci;
    char Symbol[2];
    char A[Dim * Dim];
    print_board_screen(Dim,219);
    init_array(A, Dim);
    Symbol_array(Symbol);
    do
    {
      turn_change(turn);
      do
      {

        Ask_for_move(ri,ci,turn,Dim);
        a=check_legality(A,ri,ci,Dim,turn,Symbol);


      }
      while(a==false);
      Write_on_Board( A,ri,ci, Dim, turn,Symbol);
      print_array(A,Dim);
      win=is_win(A,Dim,Symbol,turn);
      draw=is_draw(A,Dim);



    }
    while(win==0 && draw==0);
    getch();
    results(win,draw,turn);
    getch();


  return 0;
}









