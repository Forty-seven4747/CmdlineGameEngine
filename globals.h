#ifndef GLOBALS_H
#define GLOBALS_H
#include<iostream>
#include<conio.h>
#include<cstring>
#include<windows.h>
#include<cstdlib>
#include<cmath>
using namespace std;
const short msize=64;
extern short lim;
extern char gra[msize][msize];
extern char prech;
extern short key,room;
extern short x,y;
extern short prex,prey;
extern int hp;
extern string wordpool;
struct Fdialogue{
	int room;
	bool trig;
};
extern Fdialogue forcedia[256];
extern short fdcur;
struct dials{
	char pose;
	short x;
	short y;
	string words;
	double speed;
};
extern dials dial[16];
struct doors{
	short x;
	short y;
	int gt;
	short tox;
	short toy;
};
extern doors d[10];
void doorset(short add,short x,short y,int gt,short tox,short toy);
void bgchar(short col,string a);
void bgrect(char f,short xs,short ys,short xe,short ye);
void dialset(short ch,char pose,short x,short y,string words,double sp=1.0,bool force=false);
void roomchg(short r);
#endif
