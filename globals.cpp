#include"globals.h"
unsigned long long tick;
short lim=10;//map size
char gra[msize][msize];
char bgch='.';//what background looks like
char prech=bgch;
short key,room=0;
short x=5,y=5;
short prex=-1,prey=-1;//-1 means there is no last place yet
int hp;
string wordpool;
string dialpool;
Fdialogue forcedia[froomax];//one entry per room with a forced dialogue
short fdcur;//next free slot of forcedia
dials dial[dialmax];
doors d[doormax];
