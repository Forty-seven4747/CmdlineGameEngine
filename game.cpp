#include"globals.h"
#include"creation.h"
int randomint(int min,int max){
	if(max==-47)return rand()%min;
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
}//initation not original
void gotoxy(int x, int y) {
    COORD coord; coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}//not original

void doorset(short ch,short x,short y,int gt,short tox,short toy){
	d[ch].x=x;
	d[ch].y=y;
	d[ch].gt=gt;
	d[ch].tox=tox;
	d[ch].toy=toy;
}
int findfroom(int r=room){
	for(int i=0;i<froomax;i++)
	    if(forcedia[i].room==room)
	        return i;
	return -1;
}
void dialword(string word){
	gotoxy(0,lim+3);
	cout<<string(getConsoleLength()*10,' ');
	dialpool.resize(word.length());
	for(int i=0;i<word.length();i++){
		dialpool[i]=word[i];
	    gotoxy(0,lim+3);
	    cout<<dialpool;
		Sleep(47);
	}dialpool="";
	gotoxy(0,0);
}
void dialogue(short ch=0){
	if(ch>dialmax or ch<0)return;
	gotoxy(0,lim+3);
	cout<<string(getConsoleLength()*10,' ');
	wordpool.resize(dial[ch].words.length());
	for(int i=0;i<dial[ch].words.length();i++){
		wordpool[i]=dial[ch].words[i];
		for(int j=1;j<=floor(200*dial[ch].speed);j++){
			gotoxy(0,lim+3);
		    cout<<wordpool;
	    }
	}wordpool="";
	if(findfroom()>=0)forcedia[findfroom()].trig=true;
	gotoxy(0,0);
}
void dialset(short ch,char pose,short x,short y,string words,double sp,bool force){
	if(force){
		dial[dialmax-1].pose='x';
		dial[dialmax-1].x=-2;
		dial[dialmax-1].y=-1;
		dial[dialmax-1].words=words;
		dial[dialmax-1].speed=1.0;
		if(findfroom()<0){
			forcedia[fdcur].room=room;
			forcedia[fdcur].trig=0;
			fdcur++;
		}return;
	}if(ch>dialmax or ch<0)return;
	dial[ch].pose=pose;
	dial[ch].x=x;
	dial[ch].y=y;
	dial[ch].words=words;
	dial[ch].speed=sp;
}

void bgchar(short col,string a){
	if(a.length()>lim)return;
	for(short i=0;a[i]!='\0';i++)
	    gra[col][i]=a[i];
}
void bgrect(char f,short xs,short ys,short xe,short ye){
	if(xs<0 or ys<0 or xe<0 or ye<0)return;
	if(xs>lim or ys>lim or xe>lim or ye>lim)return;
	for(short i=xs;i<=xe;i++)
	    for(short j=ys;j<=ye;j++)
	        gra[i][j]=f;
}
void updMChara(){
	if(gra[x][y]=='#'){x=prex;y=prey;}
	for(int i=0;i<doormax;i++)
		if(d[i].x==x and d[i].y==y){
			short tox=d[i].tox,toy=d[i].toy;
			memset(gra,bgch,sizeof(gra));
			room=d[i].gt;
			roomchg(room);
			x=tox;
			y=toy;
			memset(d,-1,sizeof(d));
			prex=prey=-1;
			break;
		}
	for(int i=0;i<dialmax;i++)
	    if(dial[i].x==x and dial[i].y==y){
	    	x=prex;y=prey;
	    	dialogue(i);
	    	gotoxy(0,0);
		}
	for(int i=0;i<cremax;i++)
		if(cre[i].x==x and cre[i].y==y){
			x=prex;y=prey;
			dialword(cre[i].words);
		}
	if(x<0)x=0;
	if(x>lim-1)x=lim-1;
	if(y<0)y=0;
	if(y>lim-1)y=lim-1;
	prech=gra[prex][prey];
	gra[x][y]='@';
	if((prex!=x or prey!=y)and prex!=-1 and prey!=-1)
	   gra[prex][prey]=prech;
}

void graph(short r=room){
	gotoxy(0,0);
	memset(d,-1,sizeof(d));
	memset(gra,bgch,sizeof(gra));
	for(int i=0;i<dialmax;i++){
        dial[i].pose=dial[i].x=dial[i].y=0;
        dial[i].words.clear();
        dial[i].speed=1.0;
    }
	roomchg(r);
	for(int i=0;d[i].x!=-1;i++)gra[d[i].x][d[i].y]='O';
	for(int i=0;dial[i].words!="";i++)gra[dial[i].x][dial[i].y]=dial[i].pose;
	for(int i=0;cre[i].pose!='\0';i++)gra[cre[i].x][cre[i].y]=cre[i].pose;
	creationupdate();
	updMChara();
	for(int i=0;i<lim;i++){
	    for(int j=0;j<lim;j++)
	        cout<<gra[i][j]<<' ';
	    cout<<endl;
	}if(findfroom()>=0 and !forcedia[findfroom()].trig)dialogue(dialmax-1);
}
int main(){
	hidecursor();
	srand(time(0));
	updMChara();
	graph();
	while(true){
		if(_kbhit()){
			key=_getwch();
			if(key==0x1b)break;
			if(key==0xe0){
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
