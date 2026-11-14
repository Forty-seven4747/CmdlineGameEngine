#include"globals.h"
#include"creation.h"
int randomint(int min,int max){
	if(max==-47)return rand()%min;//-47 is the sign for a range starting at zero
	if(min>max)return rand()%(min-max)+max;
	return rand()%(max-min)+min;
}
void hidecursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}//not original
void showcursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}//not original
int getConsoleRows() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleScreenBufferInfo(h, &csbi)) return -1;
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}//not original
int getConsoleLength(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleScreenBufferInfo(h, &csbi)) return -1;
	return csbi.srWindow.Right-csbi.srWindow.Left+1;
}//initial not original
void gotoxy(int x, int y) {
    COORD coord; coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}//not original

bool sthhere(int x,int y){
	if(gra[x][y]!='#' and x>=0 and x<lim and y>=0 and y<lim)return 0;
	return 47;
}

void doorset(short ch,short x,short y,int gt,short tox,short toy){
	d[ch].x=x;
	d[ch].y=y;
	d[ch].gt=gt;//goto a room
	d[ch].tox=tox;//place player to x axis of that room
	d[ch].toy=toy;//place player to y axis of that room
}
int findfroom(int r=room){//r is not used, the search always uses the global room
	for(int i=0;i<froomax;i++)
	    if(forcedia[i].room==room)
	        return i;
	return -1;
}
void dialword(string word){//dialouge of a word
	gotoxy(0,lim+3);
	cout<<string(getConsoleLength()*10,' ');//wipe the line, ten times wider to be safe
	dialpool.resize(word.length());
	for(int i=0;i<word.length();i++){
		dialpool[i]=word[i];
	    gotoxy(0,lim+3);
	    cout<<dialpool;
		Sleep(47);
	}dialpool="";
	while(_kbhit())_getwch();//throw away keys pressed while reading
	gotoxy(0,0);
}
void dialogue(short ch=0){//dialouge of a creation
	if(ch>=dialmax or ch<0)return;
	gotoxy(0,lim+3);
	cout<<string(getConsoleLength()*10,' ');
	wordpool.resize(dial[ch].words.length());
	for(int i=0;i<dial[ch].words.length();i++){
		wordpool[i]=dial[ch].words[i];
		for(int j=1;j<=floor(200*dial[ch].speed);j++){//empty loop, a bigger speed holds a letter longer
			gotoxy(0,lim+3);
		    cout<<wordpool;
	    }
	}wordpool="";
	while(_kbhit())_getwch();
	if(findfroom()>=0)forcedia[findfroom()].trig=true;//a forced dialogue plays only once
	gotoxy(0,0);
}
void dialset(short ch,char pose,short x,short y,string words,double sp,bool force){//place a creation but just can dialogue
	if(force){//the last slot is kept for a dialogue that plays by itself
		dial[dialmax-1].pose='x';
		dial[dialmax-1].x=-2;
		dial[dialmax-1].y=-1;//off the map, so the player can never step on it
		dial[dialmax-1].words=words;
		dial[dialmax-1].speed=1.0;
		if(findfroom()<0){
			forcedia[fdcur].room=room;
			forcedia[fdcur].trig=0;
			fdcur++;
		}return;
	}if(ch>=dialmax or ch<0)return;
	dial[ch].pose=pose;//that decides what creation looks like
	dial[ch].x=x;
	dial[ch].y=y;
	dial[ch].words=words;
	dial[ch].speed=sp;//speed of speaking
}

void bgchar(short col,string a){//replace the background by a line of characters
	if(a.length()>lim)return;
	for(short i=0;a[i]!='\0';i++)
	    gra[col][i]=a[i];
}
void bgrect(char f,short xs,short ys,short xe,short ye){//replace the background by rectangle made of a character
	if(xs<0 or ys<0 or xe<0 or ye<0)return;//s=start, e=end
	if(xs>lim or ys>lim or xe>lim or ye>lim)return;
	for(short i=xs;i<=xe;i++)
	    for(short j=ys;j<=ye;j++)
	        gra[i][j]=f;
}
bool checkDoor(){//room changed, so graph has to lay it again
	for(int i=0;i<doormax;i++)
		if(d[i].x>=0 and d[i].x==x and d[i].y==y){//x=-1 means an empty door slot
			room=d[i].gt;
			x=d[i].tox;y=d[i].toy;
			prex=x;prey=y;
			return 47;
		}
	return 0;
}
void gracre(){//graph creations
	for(int i=0;i<doormax and d[i].x!=-1;i++)
		if(d[i].x>=0 and d[i].x<lim and d[i].y>=0 and d[i].y<lim)gra[d[i].x][d[i].y]='O';
	for(int i=0;i<dialmax and dial[i].words!="";i++)
		if(dial[i].x>=0 and dial[i].x<lim and dial[i].y>=0 and dial[i].y<lim)gra[dial[i].x][dial[i].y]=dial[i].pose;
	for(int i=0;i<cremax and cre[i].pose!='\0';i++)
		if(cre[i].x>=0 and cre[i].x<lim and cre[i].y>=0 and cre[i].y<lim)gra[cre[i].x][cre[i].y]=cre[i].pose;
}
void updMChara(){
	if(x<0)x=0;//clamp before touching gra, the arrow keys can go outside
	if(x>lim-1)x=lim-1;
	if(y<0)y=0;
	if(y>lim-1)y=lim-1;
	if(prex<0 or prey<0){prex=x;prey=y;}
	if(gra[x][y]=='#'){x=prex;y=prey;}
	for(int i=0;i<dialmax and dial[i].words!="";i++)
	    if(dial[i].x==x and dial[i].y==y){
	    	x=prex;y=prey;
	    	dialogue(i);
	    	gotoxy(0,0);
		}
	for(int i=0;i<cremax;i++)
		if(cre[i].pose!='\0' and cre[i].x==x and cre[i].y==y){
			if(!sthhere(prex,prey)){x=prex;y=prey;}
			else if(sthhere(x-1,y))x--;
			else if(sthhere(x+1,y))x++;
			else if(sthhere(x,y-1))y--;
			else if(sthhere(x,y+1))y++;
			dialword(cre[i].words);
		}
	if(x<0)x=0;
	if(x>lim-1)x=lim-1;
	if(y<0)y=0;
	if(y>lim-1)y=lim-1;
	if(prex>=0 and prey>=0 and prex<lim and prey<lim)prech=gra[prex][prey];
	else prech=bgch;
	gra[x][y]='@';
	if((prex!=x or prey!=y)and prex>=0 and prey>=0 and prex<lim and prey<lim)
	   gra[prex][prey]=prech;
}

void graph(){
	gotoxy(0,0);
	for(int pass=0;pass<2;pass++){//a door can change the room, then everything is laid again
		memset(d,-1,sizeof(d));
		memset(gra,bgch,sizeof(gra));
		for(int i=0;i<dialmax;i++){
	        dial[i].pose=dial[i].x=dial[i].y=-1;
	        dial[i].words.clear();
	        dial[i].speed=1.0;
	    }
		roomchg(room);
		if(checkDoor())continue;
		break;
	}
	creationupdate();
	gracre();
	updMChara();
	for(int i=0;i<lim;i++){
	    for(int j=0;j<lim;j++)
	        cout<<gra[i][j]<<' ';
	    cout<<endl;
	}if(findfroom()>=0 and !forcedia[findfroom()].trig)dialogue(dialmax-1);//the forced dialogue waits in the last slot
}
int main(){
	hidecursor();
	srand(time(0));
	updMChara();
	graph();
	while(true){
		if(_kbhit()){
			key=_getwch();
			if(key==0x1b)break;//esc quits
			if(key==0xe0){//0xe0 starts an arrow key, 0x48/50/4b/4d are up/down/left/right
				key=_getwch();
				prex=x;prey=y;
				if(key==0x48)x--;
				if(key==0x50)x++;
				if(key==0x4b)y--;
				if(key==0x4d)y++;
		   }
	    }else;
	    graph();
	    tick++;
	}system("cls");
	cout<<"bye!"<<endl<<endl<<endl;
}
