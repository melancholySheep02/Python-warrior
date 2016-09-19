//***************************header_files**************
#include"fstream.h"
#include"stdio.h"
#include"dos.h"
#include"bios.h"
#include"stdlib.h"
#include"conio"
#include"string.h"
//prototypes
void menu(int,int);
void start_game();
void load_game();
void options();
void esc();
void version();
void save();
void boundary();
void lo_wi(int );
void lhigh();
void shigh();
//***************************************************
struct node
{
int x,y,no;
node *pre;
node *nxt;
}*sav=NULL,*temp=NULL,*temp1=NULL;
//**************************variables******************
int *px=new int;//node variable
int *py=new int;//node variable
int *fx=new int;//food variable
int *fy=new int;//food variable
char pname[30];
//**********************global class*******************
class globe
{
node *p,*base;
int *score;
public:
       //**************score*****************
       void sc_mod()
       {
       *score+=5;
       }
       void sc_as(int x)
       {
       *score=x;
       }
       int sc_ret()
       {
       return(*score);
       }
       //node functions
       globe();
       void create_body();
       int ret_LL_x(int);
       int ret_LL_y(int);
       void LL_ass_x(int,int);
       void LL_ass_y(int,int);
       void LL_mod_x(int,int);
       void LL_mod_y(int,int);
       void swap();
       void output();
}GS;
//********************class functions****************
globe::globe()
       {
       *px=0,*py=0;
       node *ptr=new node;
       base=ptr,p=ptr; //default for one part
       base->nxt=NULL;
       base->pre=NULL;
       base->no=0;
       base->x=40,base->y=5;
       score=new int;
       *score=0;
       }
void globe::create_body()
       {
	 *px+=1;
	 *py+=1;
	 node *ptr=new node;
	 ptr->nxt=NULL;
	 ptr->no=*px;
	 p->nxt=ptr;
	 ptr->pre=p;
	 p=ptr;
       temp1=ptr->pre;
       while(temp1!=NULL)
	{
	ptr->x=temp1->x;
	ptr->y=temp1->y;
	ptr=temp1;
	temp1=temp1->pre;
	}
       }
int globe::ret_LL_x(int m)//m for which node
       {
	temp=base;
	while(temp->no<m)
	temp=temp->nxt;
	return(temp->x);
       }
int globe::ret_LL_y(int m)//m for which node
       {
       temp=base;
       while(temp->no<m)
       temp=temp->nxt;
       return(temp->y);
       }
void globe::LL_ass_x(int m,int val)
       {
       temp=base;
       while(temp->no<m)
       {temp=temp->nxt;}
       temp->x=val;
       }
void globe::LL_ass_y(int m,int val)
       {
       temp=base;
       while(temp->no<m)
       {temp=temp->nxt;}
       temp->y=val;
       }
void globe::LL_mod_x(int m,int factor)
       {
       temp=base;
       while(temp->no<m)
       {temp=temp->nxt;}
       temp->x=temp->x+factor;
       }
void globe::LL_mod_y(int m,int factor)
       {
       temp=base;
       while(temp->no<m)
       {temp=temp->nxt;}
       temp->y=temp->y+factor;
       }
void globe::swap()
       {
       temp=base;
       temp1=temp->nxt;
       if(*px!=0)
       while(temp1!=NULL)
	{
	 temp->x=temp1->x;
	 temp->y=temp1->y;
	 temp=temp->nxt;
	 temp1=temp->nxt;
	}
       }
void globe::output()
       {
	int a=*px,b=*py;
	sav=p;
	while(sav!=NULL)
	 {
	 gotoxy(*fx,*fy);cout<<"*";
	 gotoxy(ret_LL_x(a),ret_LL_y(b));
	 cout<<"*";
	 gotoxy(70,1);cout<<"score::"<<sc_ret();
	 sav=sav->pre;
	 a--,b--;
	 }
       }
//***********************Ist_global_structure************
struct Save
{
int Sx[70],Sy[70];
int X,Y;
int Sfx,Sfy;
int Sscore;
char Spname[30];
};
//***********************IInd_global_structure***********
struct hs
{
char hname[30];
int hscore;
};
//***************************start_game*******************************
void start_game()
{
textbackground(RED);
textcolor(YELLOW);
int *key=new int;
int *save_x=new int;
int *save_y=new int;//temp variables
int *n=new int;
clrscr();
while(_bios_keybrd(_KEYBRD_READY) == 0)
{
clrscr();
gotoxy(30,10);
delay(50);
cout<<"press any key to start";
delay(100);
}
while(*n!=-1)
  {
   *key=getch();
   if(*key==72||*key==119)
    {
     *save_x=GS.ret_LL_x(0),*save_y=GS.ret_LL_y(0);
     GS.swap();
     GS.LL_mod_y(*py,-1);
    }
   if(*key==80||*key==115)
    {
     *save_x=GS.ret_LL_x(0),*save_y=GS.ret_LL_y(0);
     GS.swap();
     GS.LL_mod_y(*py,1);
    }
   if(*key==75||*key==97)
    {
     *save_x=GS.ret_LL_x(0),*save_y=GS.ret_LL_y(0);
     GS.swap();
     GS.LL_mod_x(*px,-1);
    }
   if(*key==77||*key==100)
    {
     *save_x=GS.ret_LL_x(0),*save_y=GS.ret_LL_y(0);
     GS.swap();
     GS.LL_mod_x(*px,1);
    }
    p:
    if(GS.ret_LL_x(*px)>80)
    {
    GS.LL_ass_x(*px,1);
    goto p;
    }
    if(GS.ret_LL_x(*px)<1)
    {
    GS.LL_ass_x(*px,80);
    goto p;
    }
    if(GS.ret_LL_y(*py)<1)
    {
    GS.LL_ass_y(*py,24);
    goto p;
    }
    if(GS.ret_LL_y(*py)>24)
    {
    GS.LL_ass_y(*py,1);
    goto p;
    }
    vik:
   if(GS.ret_LL_x(*px)==*fx&&GS.ret_LL_y(*py)==*fy)//food eating check
    {
    GS.sc_mod();
    *fx=random(77)+2;
    *fy=random(21)+2;
    GS.create_body();
    GS.LL_ass_x(0,*save_x),GS.LL_ass_y(0,*save_y);
    clrscr();
    GS.output();
    }//end of if
    else
    {
     clrscr();
     GS.output();
    }//end of else

  if(*key==27)
  {
  esc();
  goto vik;
  }
  if(*px==70)
  {
  *n=-1;
  shigh();
  lo_wi(0);
  }
  }//end of while
}//end of function

//******************************main*********************
void main()
{
clrscr();
version();
randomize();
*fx=random(random(70))+5,*fy=random(random(13))+10;
int *key=new int;
int *p=new int[2];
p[0]=35,p[1]=10;
textbackground(BLUE);
clrscr();
*key=10;
textcolor(YELLOW);
menu(p[0],p[1]);
menu(p[0],p[1]);
while(*key!=13)
  {
   *key=getch();
   if(*key==80)
    {
     if(p[1]==14)
      {
       clrscr();
       p[1]=10;
       menu(p[0],p[1]);
      }
     else
      {
       clrscr();
       p[1]++;
       menu(p[0],p[1]);
      }
    }
   if(*key==72)
    {
     if(p[1]==10)
      {
       clrscr();
       p[1]=14;
       menu(p[0],p[1]);
      }
     else
      {
       clrscr();
       p[1]--;
       menu(p[0],p[1]);
      }
    }
  }//while loop
if(p[1]==10)
  {
   clrscr();
   gotoxy(35,10);
   cout<<"PLAYER'S NAME::\n";
   gotoxy(35,11);
   gets(pname);
   start_game();
   exit(0);
  }
else
if(p[1]==11)
  load_game();
else
if(p[1]==12)
  options();
else
if(p[1]==13)
lhigh();
else
if(p[1]==14)
exit(0);
}//main
//****************************menu*****************************
void menu(int p,int q)
{
gotoxy(p-1,q);cout<<"->";
gotoxy(p+1,10);cout<<"START GAME";
gotoxy(p+1,11);cout<<"LOAD GAME";
gotoxy(p+1,12);cout<<"HELP";
gotoxy(p+1,13);cout<<"HIGHSCORES";
gotoxy(p+1,14);cout<<"EXIT";
}

//*******************************esc******************************
void esc()
{
textbackground(GREEN);
clrscr();
gotoxy(26,12);
cout<<"do you want to save the game...?\n";
gotoxy(26,13);
cout<<"if yes press Y otherwise N\n";
char a;
a=getch();
if(a=='y'||a=='Y')
  {
   save();
  }
else
{
clrscr();
cout<<"THANKS FOR PLAYING\n";
delay(1000);
exit(0);
}
}//end of function
//******************************save*******************************
void save()
{
ofstream ofile(pname,ios::out|ios::binary);
Save s1;
for(s1.X=0;s1.X<=*px;s1.X++)
  {
  s1.Sx[s1.X]=GS.ret_LL_x(s1.X);
  s1.Sy[s1.X]=GS.ret_LL_y(s1.X);
  }
s1.Y=*py;
s1.X--;
s1.Sfx=*fx;
s1.Sfy=*fy;
strcpy(s1.Spname,pname);
s1.Sscore=GS.sc_ret();
ofile.write((char*)&s1,sizeof(s1));
ofile.close();
clrscr();
cout<<"game saved......\n";
delay(1000);
exit(0);
}//end of function
//*****************************load********************************
void load_game()
{
textbackground(GREEN);
textcolor(YELLOW);
Save load;
clrscr();
gotoxy(35,10);
cout<<"PLAYER'S NAME::\n";
gotoxy(35,11);
gets(pname);
ifstream ifile(pname,ios::in|ios::binary);
if(!ifile)
{
clrscr();
textcolor(RED);
cout<<"Game is not found on this account\n";
getch();
main();
}
else
{
ifile.seekg(0);
ifile.read((char*)&load,sizeof(Save));
for(int xl=0;xl<=load.X;xl++)
  {
   if(xl==0)
   {
   GS.LL_ass_x(xl,load.Sx[xl]);
   GS.LL_ass_y(xl,load.Sy[xl]);
   }
   else
   {
   GS.LL_ass_x(xl,load.Sx[xl]);
   GS.LL_ass_y(xl,load.Sy[xl]);
   GS.create_body();
   }
  }
xl--;
*px=xl,*py=xl;
*fx=load.Sfx,*fy=load.Sfy;
strcpy(pname,load.Spname);
GS.sc_as(load.Sscore);
ifile.close();
start_game();
}
}//end of function
//************************options********************
void options()
{
textcolor(YELLOW);
clrscr();
char t='p';
ifstream ifile("help.pw",ios::in|ios::binary);
gotoxy(35,1);
while(ifile)
{
ifile.get(t);
cout<<t;
delay(100);
}
ifile.close();
getch();
main();
}
//*********************version*********************
void version()
{
textbackground(GREEN);
textcolor(YELLOW);
clrscr();
gotoxy(24,10);
char q;
ifstream ifile("start.pw",ios::in|ios::binary);
while(q!='\n')
{
delay(100);
ifile.get(q);
textcolor(GREEN);
cout<<q;
}
gotoxy(50,24);
q='a';
ifile.seekg(1,ios::cur);
while(q!='\n')
{
ifile.get(q);
textcolor(YELLOW);
delay(100);
cout<<q;
}
getch();
 while(_bios_keybrd(_KEYBRD_READY) == 0)
 {
 textbackground(RED);
 clrscr();
 delay(50);
 gotoxy(33,12);
 cout<<"PRESS ENTER";
 delay(100);
 }
 getch();
}///end of function
//********************win_lose***************************
void lo_wi(int Q)
{
clrscr();
if(Q==0)
 {
 gotoxy(35,10);
 cout<<pname<<" is a winner\n";
 getch();
 }
else
{
gotoxy(35,10);
cout<<pname<<" is a loser\n";
}
}//end of function
//********************highscore******************************
void lhigh()
{
textcolor(GREEN);
textbackground(RED);
clrscr();
gotoxy(35,1);
cout<<"HIGHSCORE......";
hs lh;
int z=1,v=7;
ifstream ifile("hs.pw",ios::in|ios::binary);
while(z<=5)
 {
 gotoxy(35,v);
 ifile.read((char*)&lh,sizeof(lh));
 cout<<z<<".";
 cout<<lh.hname;
 cout<<"::"<<lh.hscore<<endl;;
 z++;
 v++;
 }
ifile.close();
getch();
main();
}
void shigh()
{
hs sh;
fstream iofile("hs.pw",ios::in|ios::ate|ios::binary);
iofile.seekg(0);
while(iofile)
  {
  iofile.read((char*)&sh,sizeof(sh));
  if((GS.sc_ret()>sh.hscore)||(GS.sc_ret()==sh.hscore))//if score is greater or equal
    {
    iofile.seekg(-1*sizeof(sh),ios::cur);
    strcpy(sh.hname,pname);
    sh.hscore=GS.sc_ret();
    iofile.write((char*)&sh,sizeof(sh));
    ofstream hofile("ram.pw",ios::out|ios::binary);
    int j=0;
    iofile.seekg(0);
    while(j<5)
      {
      iofile.read((char*)&sh,sizeof(sh));
      hofile.write((char*)&sh,sizeof(sh));
      j++;
      }
    hofile.close();
    goto viK;
    }
  }
viK:
remove("hs.pw");
rename("ram.pw","hs.pw");
iofile.close();
}
