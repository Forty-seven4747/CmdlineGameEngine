#include"globals.h"
#include"creation.h"
creation cre[cremax];
short creacur;
void creationset(short ch,char pose,short initx,short inity,string words,int freq,short nextx,short nexty){
	if(cre[ch].trig)return;
	cre[ch].tick=tick;
	cre[ch].trig=47;
	cre[ch].pose=pose;
	cre[ch].x=initx;
	cre[ch].y=inity;
	cre[ch].words=words;
	cre[ch].freq=freq;
	cre[ch].nex=nextx;
	cre[ch].ney=nexty;
}
void creationupdate(){
	for(int i=0;cre[i].pose!='\0';i++){
		if(tick-cre[i].tick<cre[i].freq)continue;
		for(int att=0;att<8;att++){
			int direct=randomint(0,500);
			short precx=cre[i].x,precy=cre[i].y;
			if(direct<125)precx--;
			else if(direct<250)precx++;
			else if(direct<375)precy--;
			else precy++;
			if(precx<0 or precx>=lim or precy<0 or precy>=lim)continue;
			if(gra[precx][precy]=='#')continue;
			bool hit=false;
			for(int j=0;cre[j].pose!='\0';j++)
				if(j!=i and cre[j].x==precx and cre[j].y==precy){hit=true;break;}
			if(hit)continue;
			if(precx==x and precy==y)continue;
			cre[i].x=precx;
			cre[i].y=precy;
			break;
		}cre[i].tick=tick;
	}
}
