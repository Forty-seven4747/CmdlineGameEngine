#ifndef GLOBALS_H
#define GLOBALS_H
#include<iostream>
#include<conio.h>
#include<cstring>
#include<windows.h>
#include<cstdlib>
#include<cmath>
#include<ctime>
using namespace std;
const short msize=64;
const short froomax=256;
const short dialmax=160;
const short doormax=100;
const short cremax=500;
extern unsigned long long tick;
extern short lim;
extern char gra[msize][msize];
extern char prech;
extern char bgch;
extern short key,room;
extern short x,y;
extern short prex,prey;
extern int hp;
extern string wordpool;
extern string dialpool;
struct Fdialogue{
	int room;
	bool trig;
};
extern Fdialogue forcedia[froomax];
extern short fdcur;
struct dials{
	char pose;
	short x;
	short y;
	string words;
	double speed;
};
extern dials dial[dialmax];
struct doors{
	short x;
	short y;
	int gt;
	short tox;
	short toy;
};
extern doors d[doormax];
int randomint(int min,int max=-47);
void doorset(short add,short x,short y,int gt,short tox,short toy);
void bgchar(short col,string a);
void bgrect(char f,short xs,short ys,short xe,short ye);
void dialset(short ch,char pose,short x,short y,string words,double sp=1.0,bool force=false);
void roomchg(short r);
void creationset(short ch,char pose,short initx,short inity,string words,int freq=50,short nextx=0,short nexty=0);
void creationupdate();
#endif
