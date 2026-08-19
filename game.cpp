#include"globals.h"
void doorset(short add,short x,short y,int gt,short tox,short toy){
	d[add].x=x;
	d[add].y=y;
	d[add].gt=gt;
	d[add].tox=tox;
	d[add].toy=toy;
}
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

int findfroom(int r=room){
	for(int i=0;i<256;i++)
	    if(forcedia[i].room==room)
	        return i;
}
void dialogue(short ch=0){
	if(ch>15 or ch<0)return;
	gotoxy(0,lim+3);
	wordpool.resize(dial[ch].words.length());
	for(int i=0;i<dial[ch].words.length();i++){
		wordpool[i]=dial[ch].words[i];
		for(int j=1;j<=floor(250/dial[ch].speed);j++){
			gotoxy(0,lim+3);
		    cout<<wordpool;
	    }
	}for(int i=1;i<=7;i++)cout<<string(getConsoleLength(),' ')<<endl;
	wordpool="";
	forcedia[findfroom()].trig=true;
	gotoxy(0,0);
}
void dialset(short ch,char pose,short x,short y,string words,double sp,bool force){
	if(force){
		dial[15].pose='x';
		dial[15].x=-2;
		dial[15].y=-1;
		dial[15].words=words;
		dial[15].speed=1.0;
		forcedia[fdcur].room=room;
		forcedia[fdcur].trig=0;
		fdcur++;
		return;
	}if(ch>16 or ch<0)return;
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
	if(gra[x][y]=='#')
	    {x=prex;y=prey;}
	for(int i=0;i<10;i++)
	    if(d[i].x==x and d[i].y==y){
	    	memset(gra,'.',sizeof(gra));
	    	room=d[i].gt;
	    	roomchg(room);
	    	x=d[i].tox;
	    	y=d[i].toy;
	    	memset(d,-1,sizeof(d));
	    	prex=prey=-1;
	    	break;
		}
	for(int i=0;i<16;i++)
	    if(dial[i].x==x and dial[i].y==y){
	    	x=prex;y=prey;
	    	dialogue(i);
	    	gotoxy(0,0);
		}
	if(x<0)x=0;
	if(x>lim-1)x=lim-1;
	if(y<0)y=0;
	if(y>lim-1)y=lim-1;
	prech=gra[prex][prey];
	gra[x][y]='@';
	if((prex!=x or prey!=y)and prex!=-1 and prex!=-1)
	   gra[prex][prey]=prech;
}

void graph(short r=room){
	gotoxy(0,0);
	memset(d,-1,sizeof(d));
	memset(gra,'.',sizeof(gra));
	for(int i=0;i<16;i++){
        dial[i].pose=dial[i].x=dial[i].y=0;
        dial[i].words.clear();
        dial[i].speed=1.0;
    }
	roomchg(r);
	for(int i=0;d[i].x!=-1;i++)gra[d[i].x][d[i].y]='O';
	for(int i=0;dial[i].words!="";i++)gra[dial[i].x][dial[i].y]=dial[i].pose;
	updMChara();
	for(int i=0;i<lim;i++){
	    for(int j=0;j<lim;j++)
	        cout<<gra[i][j]<<' ';
	    cout<<endl;
	}if(!forcedia[findfroom()].trig)dialogue(15);
	for(int i=1;i<=getConsoleRows()-lim-10;i++)cout<<endl;
}
int main(){
	updMChara();
	graph();
	while(true){
		key=_getwch();
		if(key==0x1b)break;
		if(key==0xe0){
			key=_getwch();
			prex=x;prey=y;
			if(key==0x48)x--;
			if(key==0x50)x++;
			if(key==0x4b)y--;
			if(key==0x4d)y++;
	   }graph();
	}system("cls");
	cout<<"bye!"<<endl<<endl<<endl;
}
