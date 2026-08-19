#include"globals.h"
void roomchg(short r){
	switch(r){
		case 0:{
		    bgrect('#',0,0,2,2);
		    doorset(0,5,9,1,5,0);
			//dialset(0,'&',8,8,"test\ntest2\ntest3");
			break;
		}case 1:{
			dialset(47,47,47,47,"You see some words on the ground!\n\nEven you don't know who wrote this,\nbut that one must be friendly.",47.0,true);
			dialset(0,'&',2,9,"What?\nNo, I don't know.\nMaybe you should get into the door.");
			bgrect('#',0,0,0,9);
			bgrect('#',9,0,9,9);
			bgchar(2,"Welcome!");
			bgchar(7,"Just go on");
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
