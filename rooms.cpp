#include"globals.h"
#include"creation.h"
void roomchg(short r){
	switch(r){
		case 0:{
		    bgrect('#',0,0,2,2);
		    doorset(0,5,9,1,5,0);
			//dialset(0,'&',8,8,"test\ntest2\ntest3");
			break;
		}case 1:{
			dialset(47,47,47,47,"You see some words on the ground!\n\nEven you don't know who wrote this,\nbut that one must be friendly.",47.0,true);//force=true, so the first five arguments are only placeholders
			dialset(0,'&',2,9,"What?\nNo, I don't know.\nMaybe you should get into the door.");
			bgrect('#',0,0,0,9);
			bgrect('#',9,0,9,9);
			bgchar(2,"Welcome!");
			bgchar(7,"Just go on");
		    doorset(0,8,9,2,8,0);
			break;
		}case 2:{
			dialset(0,'&',9,9,"Look them! They are moving!\nWould you want to take one?",2);
			for(int i=0;i<3;i++)creationset('a',2+i,3*i+2,"Baa...",47);//one call takes one slot, so no number is needed
			doorset(0,9,0,3,1,1);
		    break;
		}case 3:{
			bgchar(0,"Uniform");
			bgchar(1,"Movedelta");
			for(int i=0;i<3;i++)creationset('a',2+i,3*i+2,"Baa...");
			//for(int i=1;i<5;i++)crerase(i);
			creationset('a',4,4,"Don't run!",20,0,0,{1,0,-1,0},{0,1,0,-1},0,0);//the two tables are a square path, one pair per move
            creationset('a',5,5,"SO WHAT!",20,0,0,{-1,0,1,0},{0,-1,0,1},0,0);
            creationset('b',5,1,"You touched me!",50,0,0,vector<short>(),vector<short>(),0,1);//empty tables mean constant speed instead
			doorset(0,0,9,2,8,0);
			break;
		}
		default:{
			bgchar(0,"the room");
			bgchar(1,"does not");
			bgchar(2,"exist!");
			bgchar(7,"please");
			bgchar(8,"report");
			bgchar(9,"with this!");
		}
	}
}
