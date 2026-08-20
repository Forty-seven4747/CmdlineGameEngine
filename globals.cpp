#include"globals.h"
unsigned long long tick;
short lim=10;
char gra[msize][msize];
char bgch='.';
char prech='.';
short key,room=0;
short x=5,y=5;
short prex=-1,prey=-1;
int hp;
string wordpool;
string dialpool;
Fdialogue forcedia[froomax];
short fdcur;
dials dial[dialmax];
doors d[doormax];
