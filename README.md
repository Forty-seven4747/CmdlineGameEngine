# Commmand-line Game Engine

Files:
- `game.cpp`         the main of game. 
- `globals.cpp`      stores *declared* variables.
- `globals.h`
- `roomchg.cpp`      your game map starts there.

Functions:
- getConsoleRows()
- getConsoleLength()
- gotoxy(int x, int y)
- dialogue(short ch=0)
- dialset(short ch,char pose,short x,short y,string words,double sp,bool force)
- bgchar(short col,string a)
- bgrect(char f,short xs,short ys,short xe,short ye)


Use these functions at `roomchg.cpp`
