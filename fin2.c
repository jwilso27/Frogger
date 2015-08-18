//Sara Cunningham and Jenna Wilson Final Project: Frogger

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "gfx3.h"
#define PI 3.14

void background(int w, int h, int level); // function to print background
char blood(void); //game over function
char welcome(void); //welcome and directions
void draw_lives(int lives);
void drawfrog(int x,int y,int boardw,int boardh,char direction); //draws frog
void drawlog_small(int x, int y); //draws row of small logs
void drawlog_med(int x, int y); //draws row of med logs
void drawlog_large(int x, int y); //draws row of large logs
char win(void); //game won, play again or quit
char *num2str(int); //convert num to string
char hopper(int *frogx, int *frogy); //move froggy
int main()
{
  int i,ic,height=650, width=1200;
  int lives=5, level=1;
  int fgx=12, fgy=11, *frogx=&fgx, *frogy=&fgy;
  int row=13,col=25,board[row][col]; //dimensions
  char direction='R', play;
  int wnum=50, wseg=width/wnum, hnum=100, hseg=height/hnum, boardw=2*wseg, boardh=8*hseg;

  gfx_open(width,height,"Frogger"); //open graphics window

  play=welcome(); //begin game

  while(play!='q'){ //while user wants to play the game and not quit
    background(width,height,level); //eventaully this will be in draw function
    draw_lives(lives); //evnetually in draw function
    drawfrog(*frogx,*frogy,boardw,boardh,direction);//eventuall in draw function
    usleep(500000);
    if (gfx_event_waiting() == 1){ //if user tries to move frog
   	 direction = hopper(frogx,frogy); //move frog according to input if valid
    }
    /*switch(board[*frogx][*frogy]){
   	 case 0: //frog dies in this location
   		 lives=lives-1;
   		 if(lives==0){
   			 play=blood(); //game over, play again or end
   			 lives=5;
   		 }
   		 level=1;
   		 //reset everything here NEED TO DO
   		 break;    
   	 case 1: //frog can be in this location and game continues
   		 break;
   	 case 2: //frog made it to lilly pad
   		 level++;
   		 if (level>5){
   			 play=win();//you won!
   			 if (play != 'q'){
   				 level = 1;
   				 lives = 5;
   			 }
   		 }
   		 break;
    }*/
 }
}

void background(int w,int h,int level)
{  
	int wnum=50,wseg=w/wnum,hnum=100,hseg=h/hnum,i,ic; //define parameters
   
	gfx_clear_color(0,0,0);
	gfx_clear();
	gfx_color(255,255,255); //white
 	gfx_text(w/2, h-20, "Use arrow keys to navigate frog safely to a lilly pad. Do not get hit by a car or fall in the water.");
 	gfx_text(w/4,h-20,"LEVEL: ");
 	gfx_text(w/4+50,h-20,num2str(level));
 
	gfx_color(20,0,150); //blue color
	gfx_fill_rectangle(0,0,w,h/2); //draws water
    
	gfx_color(20,150,0); //green color
	gfx_fill_rectangle(0,0,w,hseg); //draws top green border
    
	for(i=0;i<6;i++) //draws lily pads
    	for(ic=1;ic<(3*hseg);ic++) //increment radius to fill circle
        	gfx_circle((i*8+5)*wseg,5*hseg,ic);
       	 
	for(i=0;i<wnum;i++){ //draws pad details
    	if((i+2)%4!=0)
        	gfx_fill_rectangle(wseg*i*2,hseg,2*wseg,hseg);
       	 
    	if((i+1)%8<4){
        	switch((i+2)%4){
            	case 1:
                	gfx_fill_rectangle(wseg*i,2*hseg,wseg,hseg);
                	gfx_fill_rectangle(wseg*i,4*hseg,wseg,2*hseg);
                	break;
            	case 2:
                	gfx_fill_rectangle(wseg*i,3*hseg,wseg,2*hseg);
                	gfx_fill_rectangle(wseg*i,6*hseg,wseg,1*hseg);
                	break;
            	case 3:
                	gfx_fill_rectangle(wseg*i,2*hseg,wseg,2*hseg);
                	gfx_fill_rectangle(wseg*i,5*hseg,wseg,2*hseg);
                	break;
            	case 0:
                	gfx_fill_rectangle(wseg*i,2*hseg,wseg,hseg);
                	gfx_fill_rectangle(wseg*i,4*hseg,wseg,2*hseg);
                	break;
        	} //end switch((i+2)%4)
    	} //end if((i+1)%8<4)
   	 
    	switch(i%8){ //draw middle grass
            	case 0:
            	case 1:
            	case 3:
            	case 6:
                	gfx_fill_rectangle(wseg*i,(h/2)-(4*hseg),wseg,5*hseg);
                	break;
            	case 2:
            	case 7:
                	gfx_fill_rectangle(wseg*i,(h/2)-(5*hseg),wseg,7*hseg);
                	break;
            	case 4:
                	gfx_fill_rectangle(wseg*i,(h/2)-(4*hseg),wseg,6*hseg);
                	break;
            	case 5:
                	gfx_fill_rectangle(wseg*i,(h/2)-(5*hseg),wseg,6*hseg);
                	break;
        	} //end switch((i+2)%4)
       	 
    	switch(i%8){ //draw bottom grass
        	case 0:
        	case 1:
        	case 3:
        	case 6:
            	gfx_fill_rectangle(wseg*i,h-(18*hseg),wseg,5*hseg);
            	break;
        	case 2:
        	case 7:
            	gfx_fill_rectangle(wseg*i,h-(19*hseg),wseg,7*hseg);
            	break;
        	case 4:
            	gfx_fill_rectangle(wseg*i,h-(18*hseg),wseg,6*hseg);
            	break;
        	case 5:
            	gfx_fill_rectangle(wseg*i,h-(19*hseg),wseg,6*hseg);
            	break;
    	} //end switch((i+2)%4)
   	 
	} //end for(i=0;i<wnum;i++)
    
	gfx_color(150,75,0); //brown color
	for(i=0;i<wnum;i++){ //draws grass details
    	switch(i%8){ //draw middle grass details
            	case 0:
            	case 1: break;
            	case 3:
            	case 6:
                	gfx_fill_rectangle(wseg*i,(h/2)-(2*hseg),wseg,hseg);
                	break;
            	case 2:
            	case 7:
                	gfx_fill_rectangle(wseg*i,(h/2)-(4*hseg),wseg,hseg);
                	break;
            	case 4:
                	gfx_fill_rectangle(wseg*i,(h/2)-(3*hseg),wseg,hseg);
                	break;
            	case 5:
                	gfx_fill_rectangle(wseg*i,(h/2)-hseg,wseg,hseg);
                	break;
        	} //end switch((i+2)%4)
       	 
        	switch(i%8){ //draw bottom grass details
            	case 0:
            	case 1: break;
            	case 3:
            	case 6:
                	gfx_fill_rectangle(wseg*i,h-(16*hseg),wseg,hseg);
                	break;
            	case 2:
            	case 7:
                	gfx_fill_rectangle(wseg*i,h-(18*hseg),wseg,hseg);
                	break;
            	case 4:
                	gfx_fill_rectangle(wseg*i,h-(17*hseg),wseg,hseg);
                	gfx_fill_rectangle(wseg*i,h-(14*hseg),wseg,hseg);
                	break;
            	case 5:
                	gfx_fill_rectangle(wseg*i,h-(15*hseg),wseg,hseg);
                	break;
        	} //end switch((i+2)%4)
       	 
	} //end for(i=0;i<wnum;i++)
    
} //end background


char blood(void)
{
	gfx_clear_color(255,0,0);
	gfx_clear();

	gfx_color(255,255,255);

	//Game over
	gfx_fill_rectangle(330,160,100,20);  
	gfx_fill_rectangle(310,180,40,20);
	gfx_fill_rectangle(290,200,40,60);
	gfx_fill_rectangle(310,260,40,20);
	gfx_fill_rectangle(330,280,100,20);
	gfx_fill_rectangle(390,260,40,20);
	gfx_fill_rectangle(370,240,60,20);

	//gAme over
	gfx_fill_rectangle(450,200,40,100);
	gfx_fill_rectangle(470,180,40,20);
	gfx_fill_rectangle(490,160,60,20);
	gfx_fill_rectangle(530,180,40,20);
	gfx_fill_rectangle(550,200,40,100);
	gfx_fill_rectangle(490,240,60,20);

	//gaMe over
	gfx_fill_rectangle(610,160,40,140);
	gfx_fill_rectangle(650,180,20,40);
	gfx_fill_rectangle(670,200,20,40);
	gfx_fill_rectangle(690,180,20,40);
	gfx_fill_rectangle(710,160,40,140);

	//gamE over
	gfx_fill_rectangle(770,160,40,140);
	gfx_fill_rectangle(810,160,100,20);
	gfx_fill_rectangle(810,220,80,20);
	gfx_fill_rectangle(810,280,100,20);

	//game Over
	gfx_fill_rectangle(290,370,40,100);
	gfx_fill_rectangle(390,370,40,100);
	gfx_fill_rectangle(310,350,100,20);
	gfx_fill_rectangle(310,470,100,20);

	//game oVer
	gfx_fill_rectangle(450,350,40,80);
	gfx_fill_rectangle(550,350,40,80);
	gfx_fill_rectangle(470,430,40,20);
	gfx_fill_rectangle(530,430,40,20);
	gfx_fill_rectangle(490,450,60,20);
	gfx_fill_rectangle(510,470,20,20);

	//game ovEr
	gfx_fill_rectangle(610,350,40,140);
	gfx_fill_rectangle(650,350,100,20);
	gfx_fill_rectangle(650,410,80,20);
	gfx_fill_rectangle(650,470,100,20);

	//game oveR
	gfx_fill_rectangle(770,350,40,140);
	gfx_fill_rectangle(810,350,80,20);
	gfx_fill_rectangle(870,370,40,60);
	gfx_fill_rectangle(850,410,20,20);
	gfx_fill_rectangle(810,430,60,20);
	gfx_fill_rectangle(830,450,60,20);
	gfx_fill_rectangle(860,470,60,20);

	//directions to continue
	gfx_text(450, 520, "Press any key to play Frogger again. Press \'q\' to quit.");

	return gfx_wait();
} //end blood

char welcome(void)
{
	gfx_clear_color(0,255,0); //green
	gfx_clear();

	gfx_color(255,255,255);

	//Frogger
	gfx_fill_rectangle(50,160,40,140);
	gfx_fill_rectangle(90,160,100,20);
	gfx_fill_rectangle(90,220,80,20);

	//fRogger
	gfx_fill_rectangle(210,160,40,140);
	gfx_fill_rectangle(250,160,80,20);
	gfx_fill_rectangle(310,180,40,60);
	gfx_fill_rectangle(290,220,20,20);
	gfx_fill_rectangle(250,240,60,20);
	gfx_fill_rectangle(270,260,60,20);
	gfx_fill_rectangle(300,280,60,20);

	//frOgger
	gfx_fill_rectangle(370,180,40,100);
	gfx_fill_rectangle(470,180,40,100);
	gfx_fill_rectangle(390,160,100,20);
	gfx_fill_rectangle(390,280,100,20);

	//froGger
	gfx_fill_rectangle(570,160,100,20);  
	gfx_fill_rectangle(550,180,40,20);
	gfx_fill_rectangle(530,200,40,60);
	gfx_fill_rectangle(550,260,40,20);
	gfx_fill_rectangle(570,280,100,20);
	gfx_fill_rectangle(630,260,40,20);
	gfx_fill_rectangle(610,240,60,20);

	//frogGer
	gfx_fill_rectangle(730,160,100,20);  
	gfx_fill_rectangle(710,180,40,20);
	gfx_fill_rectangle(690,200,40,60);
	gfx_fill_rectangle(710,260,40,20);
	gfx_fill_rectangle(730,280,100,20);
	gfx_fill_rectangle(790,260,40,20);
	gfx_fill_rectangle(770,240,60,20);

	//froggEr
	gfx_fill_rectangle(850,160,40,140);
	gfx_fill_rectangle(890,160,100,20);
	gfx_fill_rectangle(890,220,80,20);
	gfx_fill_rectangle(890,280,100,20);

	//froggeR
	gfx_fill_rectangle(1010,160,40,140);
	gfx_fill_rectangle(1050,160,80,20);
	gfx_fill_rectangle(1110,180,40,60);
	gfx_fill_rectangle(1090,220,20,20);
	gfx_fill_rectangle(1050,240,60,20);
	gfx_fill_rectangle(1070,260,60,20);
	gfx_fill_rectangle(1100,280,60,20);

	gfx_text(530,325, "CSE20211: Final Project");
	gfx_text(510,345, "Sara Cunningham and Jenna Wilson");
	gfx_text(470,365, "Press any key to play Frogger. Press \'q\' to quit");

	return gfx_wait();
} //end welcome

void draw_lives(int lives)
{
	int l, i;
 
	gfx_color(255,255,0); //yellow

	for (l=0; l<lives; l++)
    	for(i=0; i<10; i++)
        	gfx_circle(20+l*30,630,i);
       	 
} //end draw_lives

void drawfrog(int col,int row,int boardw,int boardh,char direction)
{
	int xp=boardw*col+boardw/2,yp=boardh*row+boardh/2,i,inr=boardh/2-10,outr=boardh/2-5,eyer=5,xleye,yleye,xreye,yreye;
	double theta=PI/4;
    
	gfx_color(255,255,0); //yellow
	for(i=1;i<inr;i++)
    	gfx_circle(xp,yp,i); //draws frog stomach
   	 
	gfx_color(150,255,50); //green
	for(i=inr;i<=outr;i++)
    	gfx_circle(xp,yp,i); //draws frog
   	 
	gfx_color(255,0,255); //magenta
	switch(direction){ //draws frog eyes in direction of movement
    	case 'Q': //left
        	xleye=xp-outr*cos(theta); //x center of left eye
        	yleye=yp+outr*sin(theta); //y center of left eye
        	xreye=xp-outr*cos(theta); //x center of right eye
        	yreye=yp-outr*sin(theta); //y center of right eye
       	 
        	for(i=1;i<eyer;i++){
            	gfx_circle(xleye,yleye,i);
            	gfx_circle(xreye,yreye,i);
        	} //end for(i=1;i<eyer;i++)
        	break;
   	 
    	case 'R': //up
        	xleye=xp-outr*cos(theta); //x center of left eye
        	yleye=yp-outr*sin(theta); //y center of left eye
        	xreye=xp+outr*cos(theta); //x center of right eye
        	yreye=yp-outr*sin(theta); //y center of right eye
       	 
        	for(i=1;i<eyer;i++){
            	gfx_circle(xleye,yleye,i);
            	gfx_circle(xreye,yreye,i);
        	} //end for(i=1;i<eyer;i++)
        	break;
       	 
    	case 'S': //right
        	xleye=xp+outr*cos(theta); //x center of left eye
        	yleye=yp-outr*sin(theta); //y center of left eye
        	xreye=xp+outr*cos(theta); //x center of right eye
        	yreye=yp+outr*sin(theta); //y center of right eye
       	 
        	for(i=1;i<eyer;i++){
            	gfx_circle(xleye,yleye,i);
            	gfx_circle(xreye,yreye,i);
        	} //end for(i=1;i<eyer;i++)
        	break;
   	 
    	case 'T': //down
        	xleye=xp+outr*cos(theta); //x center of left eye
        	yleye=yp+outr*sin(theta); //y center of left eye
        	xreye=xp-outr*cos(theta); //x center of right eye
        	yreye=yp+outr*sin(theta); //y center of right eye
       	 
        	for(i=1;i<eyer;i++){
            	gfx_circle(xleye,yleye,i);
            	gfx_circle(xreye,yreye,i);
        	} //end for(i=1;i<eyer;i++)
   	 
        	break;
	} //end switch(direction)
} //end drawfrog

void drawlog_small(int x, int y)
{
	gfx_color(150,75,0); //brown color
    
} //end drawlog_small

void drawlog_med(int x, int y)
{

} //end drawlog_med

void drawlog_large(int x, int y)
{

} //end drawlog_large

char win(void)
{
  gfx_clear_color(0,0,255); //blue background
  gfx_clear();
  gfx_color(255,255,255); //white letters

  //You
  gfx_fill_rectangle(370,160,40,60);
  gfx_fill_rectangle(470,160,40,60);
  gfx_fill_rectangle(390,220,100,20);
  gfx_fill_rectangle(410,240,60,60);
 
  //yOu
  gfx_fill_rectangle(530,180,40,100);
  gfx_fill_rectangle(630,180,40,100);
  gfx_fill_rectangle(550,160,100,20);
  gfx_fill_rectangle(550,280,100,20);

  //yoU
  gfx_fill_rectangle(690,160,40,120);
  gfx_fill_rectangle(790,160,40,120);
  gfx_fill_rectangle(710,280,100,20);

  //Won
  gfx_fill_rectangle(370,350,40,140);
  gfx_fill_rectangle(470,350,40,140);
  gfx_fill_rectangle(410,430,20,40);
  gfx_fill_rectangle(430,410,20,40);
  gfx_fill_rectangle(450,430,20,40);

  //wOn
  gfx_fill_rectangle(530,370,40,100);
  gfx_fill_rectangle(630,370,40,100);
  gfx_fill_rectangle(550,350,100,20);
  gfx_fill_rectangle(550,470,100,20);

  //woN
  gfx_fill_rectangle(690,350,40,140);
  gfx_fill_rectangle(790,350,40,140);
  gfx_fill_rectangle(730,370,20,40);
  gfx_fill_rectangle(750,390,20,40);
  gfx_fill_rectangle(770,410,20,40);

  gfx_text(450,520,"Press any key to play Frogger. Press \'q\' to quit.");

  return gfx_wait();
}

char *num2str(int n)
{
  static char a[4];
  sprintf(a, "%d", n);
  return (char *) a;
}

char hopper(int *frogx, int *frogy)
{
  char direction;

  direction = gfx_wait();

  if (direction == 'Q'){
    (*frogx)--;
    if (*frogx<0)
   	 (*frogx)++;
  }else if (direction == 'R'){
    (*frogy)--;
    if (*frogy<0)
   	 (*frogy)++;
  }else if (direction = 'S'){
    (*frogx)++;
    if (*frogx>=25)
   	 (*frogx)--;
  }else if (direction = 'T'){
    (*frogy)++;
    if (*frogy>=13)
   	 (*frogy)--;
  }
  printf("%c", direction);
  return direction;

}
