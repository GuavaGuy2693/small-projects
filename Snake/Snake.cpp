#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;
bool gameOver;
const int WIDTH = 20;
const int HEIGHT = 20;
int x,y,fx,fy,score;
enum direction {STOP=0,LEFT,RIGHT,UP,DOWN};
direction dir;
int tx[100], ty[100], tn;
void Setup(){
  gameOver=false;
  dir=STOP;
  x=WIDTH/2;
  y=HEIGHT/2;
  fx=1+rand()%WIDTH-2;
  fy=1+rand()%HEIGHT-2;
}
void Draw(){
  system("cls");
  for(int i=0;i<WIDTH+1;i++)
    cout<<"#";
  cout<<endl;
  for(int i=0;i<HEIGHT;i++){
    for(int j=0;j<WIDTH;j++){
      if(j==0||j==WIDTH-1)
        cout<<"#";
      if(i==y&&j==x)
        cout<<"0";
      else if(i==fy&&j==fx)
        cout<<"F";
      else{
        bool print=false;
        for(int k=0;k<tn;k++){
          if(tx[k]==j&&ty[k]==i){
            print=true;
            cout<<"o";
          }
        }
        if (!print)
          cout<<" ";
      } 
    }
    cout<<endl;
  }
  for(int i=0;i<WIDTH+1;i++)
    cout<<"#";
  cout<<endl<<"Score: "<<score<<endl;
}
void Input(){
  if(_kbhit()){
    switch(_getch()){
      case 'w':
        if(dir!=DOWN)
          dir=UP;
        break;
      case 'a':
        if(dir!=RIGHT)
          dir=LEFT;
        break;
      case 'd':
        if(dir!=LEFT)
          dir=RIGHT;
        break;
      case 's':
        if(dir!=UP)
          dir=DOWN;
        break;
      case 'q':
        gameOver=true;
        break;
    }
  }
}
void Logic(){
  int px=tx[0],py=ty[0],p2x,p2y;
  tx[0]=x,ty[0]=y;
  for(int i=1;i<tn;i++){
    p2x=tx[i];
    p2y=ty[i];
    tx[i]=px;
    ty[i]=py;
    px=p2x;
    py=p2y;
  }
  switch(dir){
  case UP:
    y--;
    break;
  case DOWN:
    y++;
    break;
  case LEFT:
    x--;
    break;
  case RIGHT:
    x++;
    break;
  default:
    break;
  }
  // walled
  if(x<0||x>=WIDTH-1||y<0||y>=HEIGHT-1){
    gameOver=true;
  }
  // not walled
  // if(x>=WIDTH)x=0;else if(x<0)x=WIDTH-1;
  // if(y>=HEIGHT)y=0;else if(y<0)y=HEIGHT-1;
  for(int i=0;i<tn;i++){
    if(tx[i]==x&&ty[i]==y)
      gameOver=true;
  }
  if(x==fx&&y==fy){
    score+=10;
    fx=1+rand()%(WIDTH-3);
    fy=1+rand()%(HEIGHT-3);
    tn++;
  }
}
int main(){
  Setup();
  while(!gameOver){
    Draw();
    Input();
    Logic();
    Sleep(4);
  }
}