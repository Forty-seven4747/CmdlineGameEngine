#include"globals.h"
#include"creation.h"
creation cre[cremax];//all creations
short creacur;
void crerase(int n){//clear a creation slot
	cre[n].tick=0;
	cre[n].trig=0;
	cre[n].pose='\0';
	cre[n].x=-1;//off the map, so nothing can touch it
	cre[n].y=-1;
	cre[n].words="";
	cre[n].freq=0;
	cre[n].nex=0;
	cre[n].ney=0;
	cre[n].deltax.clear();
	cre[n].deltay.clear();
	cre[n].mdpoint=0;
	cre[n].dx=0;
	cre[n].dy=0;
	cre[n].roomat=0;
}
void creationset(char pose,short initx,short inity,string words,int freq,short nextx,short nexty,const vector<short>& movedeltax,const vector<short>& movedeltay,short xdelta,short ydelta){//place a creation and set its data
	int ch=creacur++;//take the next free slot
	if(ch>=cremax)return;//no slot left
	if(cre[ch].roomat!=room)crerase(ch);//reset it when the room changes
	if(cre[ch].trig)return;//only set once in the same room
	cre[ch].tick=tick;
	cre[ch].trig=47;
	cre[ch].pose=pose;
	cre[ch].x=initx;
	cre[ch].y=inity;
	cre[ch].words=words;
	cre[ch].freq=freq;//ticks between two moves
	cre[ch].nex=nextx;
	cre[ch].ney=nexty;
	int n=(int)(movedeltax.size()<movedeltay.size()?movedeltax.size():movedeltay.size());//the two tables are used in pairs, so take the shorter one
	cre[ch].deltax.assign(movedeltax.begin(),movedeltax.begin()+n);//the step table on x
	cre[ch].deltay.assign(movedeltay.begin(),movedeltay.begin()+n);//the step table on y
	cre[ch].mdpoint=0;
	cre[ch].dx=xdelta;//constant speed on x axis
	cre[ch].dy=ydelta;//constant speed on y axis
	cre[ch].roomat=room;//which room it belongs to
}
void creationupdate(){//move all creations every frame
	for(int i=0;cre[i].pose!='\0';i++){//stop at the first empty slot
	    if(cre[i].dx!=0 or cre[i].dy!=0){//move at a constant speed
	    	if(tick-cre[i].tick<cre[i].freq)continue;//wait until enough ticks
	    	short nx=cre[i].x+cre[i].dx;
	    	short ny=cre[i].y+cre[i].dy;
	    	if(nx<0 or nx>=lim){cre[i].dx=-cre[i].dx;nx=cre[i].x+cre[i].dx;}//turn around at the edge
	    	if(ny<0 or ny>=lim){cre[i].dy=-cre[i].dy;ny=cre[i].y+cre[i].dy;}
	    	if(nx<0 or nx>=lim)nx=cre[i].x;
	    	if(ny<0 or ny>=lim)ny=cre[i].y;
	    	cre[i].x=nx;
	    	cre[i].y=ny;
	    	cre[i].tick=tick;
			continue;
		}
		int dlen=(int)cre[i].deltax.size();
		if(dlen>0){//follow the delta path
			if(tick-cre[i].tick<cre[i].freq)continue;//wait until enough ticks
			if(cre[i].mdpoint<0 or cre[i].mdpoint>=dlen)cre[i].mdpoint=0;
			short nx=cre[i].x+cre[i].deltax[cre[i].mdpoint];
			short ny=cre[i].y+cre[i].deltay[cre[i].mdpoint];//one step from the table
			bool blocked=false;
			if(nx<0 or nx>=lim or ny<0 or ny>=lim)blocked=47;
			else if(gra[nx][ny]=='#')blocked=47;//do not walk into a wall
			else if(nx==x and ny==y)blocked=47;//do not stand on the player
			else for(int j=0;cre[j].pose!='\0';j++)
				if(j!=i and cre[j].x==nx and cre[j].y==ny){blocked=true;break;}
			if(blocked){nx=cre[i].x;ny=cre[i].y;}//stay when blocked
			cre[i].x=nx;
			cre[i].y=ny;
			(cre[i].mdpoint+1>dlen-1)?cre[i].mdpoint=0:cre[i].mdpoint+=1;//next step in the table
			cre[i].tick=tick;
			continue;
	    }
		if(tick-cre[i].tick<cre[i].freq)continue;
		for(int att=0;att<8;att++){//try another direction when blocked
			int direct=randomint(0,500);//four quarters pick up, down, left, right
			short precx=cre[i].x,precy=cre[i].y;
			if(direct<125)precx--;
			else if(direct<250)precx++;
			else if(direct<375)precy--;
			else precy++;
			if(precx<0 or precx>=lim or precy<0 or precy>=lim)continue;
			if(gra[precx][precy]=='#')continue;//do not walk into a wall
			bool hit=false;
			for(int j=0;cre[j].pose!='\0';j++)
				if(j!=i and cre[j].x==precx and cre[j].y==precy){hit=47;break;}
			if(hit)continue;//do not stand on another creation
			if(precx==x and precy==y)continue;//do not stand on the player
			cre[i].x=precx;
			cre[i].y=precy;
			break;
		}cre[i].tick=tick;
	}
}
