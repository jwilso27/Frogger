//Sara Cunningham and Jenna Wilson Final Project: Frogger

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "gfx3.h"
#define PI 3.14
#define width 1200
#define height 650

void background(int level); // function to print background
char blood(void); //game over function
char welcome(void); //welcome and directions
void draw_lives(int lives); //draws circles representing lives
void drawfrog(int col,int row,char direction); //draws frog
int drawlog(int x, int row, int wseg, int hseg, int boardw, int boardh, int len, int col, int board[][col]); //draws num logs of length len
int drawturtle(int x, int row, int wseg, int hseg, int boardw, int boardh, int col, int board[][col]); //draws num turtles
int drawtruck(int x, int row, int wseg, int hseg, int boardw, int boardh, int num, int len, int col, int board[][col]); //draws trucks
int drawcar(int x, int row, int wseg, int hseg, int boardw, int boardh, int num, int len, int col, int board[][col]); //draws cars
void draw(int col, int board[][col], int dx, int x[19], int *frogx, int *frogy); //draws moving objects
char win(void); //game won, play again or quit
char *num2str(int); //convert num to string
char hopper(int *frogx, int *frogy, int row, int col); //move froggy

int main()
{
	int i,ic; //variables for incrementing in for loops
	int lives=5, level=1; //initialize lives and level
	int fgx=12, fgy=11, *frogx=&fgx, *frogy=&fgy; //initialize frog position
	int row=12,col=25,board[row][col]; //dimensions for board
	char play; //declare play character
	int x[19]={5-width/4,width+5,10-width/4,15-width/4,width+10,5-width/2,1.2*width,10-width/2,15-width/2,1.2*width,5-width,1.5*width,10-width,15-width,1.5*width,width+5,5-width,width+10,10-width/2}; //array of starting positions of moving objects

	//initialize board
	for(i=0;i<6;i++)
		for(ic=0;ic<col;ic++)
			board[i][ic]=0;
	for(i=6;i<row;i++)
		for(ic=0;ic<col;ic++)
			board[i][ic]=1;
	for(i=2;i<col;i+=4)
		board[0][i]=2;

	gfx_open(width,height,"Frogger"); //open graphics window

	play=welcome(); //begin game

  while(play!='q'){ //while user wants to play the game and not quit
    background(level);
    draw_lives(lives);
    draw(col,board,level,x,frogx,frogy);
    drawfrog(*frogx,*frogy,play);
    gfx_flush();
    usleep(100000);
/*
    for(i=0;i<row;i++){ //prints board in terminal
    	for(ic=0;ic<col;ic++)
    		printf("%d",board[i][ic]);
    	printf("\n");
    } //end for(i=0;i<row;i++)
    printf("\n");
*/    
    if (gfx_event_waiting()){ //if user tries to move frog
   		play = hopper(frogx,frogy,row,col); //move frog according to input if valid
    } //end if (gfx_event_waiting())
    
	switch(board[*frogy][*frogx]){
		case 0: //frog dies in this location
			lives--; //lose a life
			*frogx=12;
			*frogy=11;
			if(lives==0){
				play=blood(); //game over, play again or end
				lives=5;
				level=1;
			} //end if(lives==0)
			break;       
		 	
		case 1: //frog can be in this location and game continues
		 	break;
	 	
	 	case 2: //frog made it to lilly pad
			level++; //level up
			*frogx=12;
   			*frogy=11;
			if (level>5){
   				play=win();//you won!
				level = 1;
				lives = 5;
   			} //end if (level>5)
   		 	break;
		 	
		} //end switch(board[*frogx][*frogy])
		
	} //end while(play!='q')

} //end main

char *num2str(int n)
{
	static char a[4];
	sprintf(a,"%d",n);
	return (char *) a;
} //end num2str

void background(int level)
{  
	int wnum=50,wseg=width/wnum,hnum=100,hseg=height/hnum,i,ic; //define parameters
   
	gfx_clear_color(0,0,0);
	gfx_clear();
	gfx_color(255,255,255); //white
 	gfx_text(width/2, height-20, "Use arrow keys to navigate frog safely to a lilly pad. Do not get hit by a car or fall in the water.");
 	gfx_text(width/4,height-20,"LEVEL: ");
 	gfx_text(width/4+50,height-20,num2str(level));
 
	gfx_color(20,0,150); //blue color
	gfx_fill_rectangle(0,0,width,height/2); //draws water
    
	gfx_color(20,150,0); //green color
	gfx_fill_rectangle(0,0,width,hseg); //draws top green border
	
	for(i=0;i<6;i++) //draws lily pads
		for(ic=1;ic<(3*hseg);ic++) //increment radius to fill circle
			gfx_ellipse((i*8+5)*wseg,5*hseg,ic,ic);
			
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
				gfx_fill_rectangle(wseg*i,(height/2)-(3*hseg),wseg,5*hseg);
				break;
			case 2:
			case 7:
				gfx_fill_rectangle(wseg*i,(height/2)-(4*hseg),wseg,7*hseg);
				break;
			case 4:
				gfx_fill_rectangle(wseg*i,(height/2)-(3*hseg),wseg,6*hseg);
				break;
			case 5:
				gfx_fill_rectangle(wseg*i,(height/2)-(4*hseg),wseg,6*hseg);
				break;
        } //end switch((i+2)%4)
       	 
		switch(i%8){ //draw bottom grass
			case 0:
			case 1:
			case 3:
			case 6:
				gfx_fill_rectangle(wseg*i,height-(15*hseg),wseg,5*hseg);
				break;
			case 2:
			case 7:
				gfx_fill_rectangle(wseg*i,height-(16*hseg),wseg,7*hseg);
				break;
			case 4:
				gfx_fill_rectangle(wseg*i,height-(15*hseg),wseg,6*hseg);
				break;
			case 5:
				gfx_fill_rectangle(wseg*i,height-(16*hseg),wseg,6*hseg);
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
                	gfx_fill_rectangle(wseg*i,(height/2)-hseg,wseg,hseg);
                	break;
            	case 2:
            	case 7:
                	gfx_fill_rectangle(wseg*i,(height/2)-(3*hseg),wseg,hseg);
                	break;
            	case 4:
                	gfx_fill_rectangle(wseg*i,(height/2)-(2*hseg),wseg,hseg);
                	break;
            	case 5:
                	gfx_fill_rectangle(wseg*i,(height/2),wseg,hseg);
                	break;
        	} //end switch((i+2)%4)
       	 
        	switch(i%8){ //draw bottom grass details
            	case 0:
            	case 1: break;
            	case 3:
            	case 6:
                	gfx_fill_rectangle(wseg*i,height-(13*hseg),wseg,hseg);
                	break;
            	case 2:
            	case 7:
                	gfx_fill_rectangle(wseg*i,height-(15*hseg),wseg,hseg);
                	break;
            	case 4:
                	gfx_fill_rectangle(wseg*i,height-(14*hseg),wseg,hseg);
                	gfx_fill_rectangle(wseg*i,height-(11*hseg),wseg,hseg);
                	break;
            	case 5:
                	gfx_fill_rectangle(wseg*i,height-(12*hseg),wseg,hseg);
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
} //end win

void draw_lives(int lives)
{
	int l, i;
 
	gfx_color(255,255,0); //yellow

	for (l=0; l<lives; l++)
		for(i=0; i<10; i++)
			gfx_ellipse(20+l*30,630,i,i);
			
} //end draw_lives

void drawfrog(int col,int row,char direction)
{
	int boardw=width/25,boardh=height/13; //size of board spaces in pixels
	int xp=boardw*col+boardw/2,yp=boardh*row+boardh/2; //board to pixel conversion
	int i,inr=boardh/2-10,outr=boardh/2-5; //incrementing variable and radius definitions
	int eyer=5,xleye,yleye,xreye,yreye; //declare eye variables
	double theta=PI/4;
	
	gfx_color(255,255,0); //yellow
	for(i=1;i<inr;i++) 
		gfx_ellipse(xp,yp,i,i); //draws frog stomach
		
	gfx_color(150,255,50); //green
	for(i=inr;i<=outr;i++)
		gfx_ellipse(xp,yp,i,i); //draws frog
		
	gfx_color(255,0,255); //magenta
	switch(direction){ //draws frog eyes in direction of movement
		case 'Q': //left
			xleye=xp-outr*cos(theta); //x center of left eye
			yleye=yp+outr*sin(theta); //y center of left eye
			xreye=xp-outr*cos(theta); //x center of right eye
			yreye=yp-outr*sin(theta); //y center of right eye
			
			for(i=1;i<eyer;i++){
				gfx_ellipse(xleye,yleye,i,i);
				gfx_ellipse(xreye,yreye,i,i);
			} //end for(i=1;i<eyer;i++)
			break;
		
		default: //any other case
		case 'R': //up
			xleye=xp-outr*cos(theta); //x center of left eye
			yleye=yp-outr*sin(theta); //y center of left eye
			xreye=xp+outr*cos(theta); //x center of right eye
			yreye=yp-outr*sin(theta); //y center of right eye
			
			for(i=1;i<eyer;i++){
				gfx_ellipse(xleye,yleye,i,i);
				gfx_ellipse(xreye,yreye,i,i);
			} //end for(i=1;i<eyer;i++)
			break;
			
		case 'S': //right
			xleye=xp+outr*cos(theta); //x center of left eye
			yleye=yp-outr*sin(theta); //y center of left eye
			xreye=xp+outr*cos(theta); //x center of right eye
			yreye=yp+outr*sin(theta); //y center of right eye
			
			for(i=1;i<eyer;i++){
				gfx_ellipse(xleye,yleye,i,i);
				gfx_ellipse(xreye,yreye,i,i);
			} //end for(i=1;i<eyer;i++)
			break;
		
		case 'T': //down
			xleye=xp+outr*cos(theta); //x center of left eye
			yleye=yp+outr*sin(theta); //y center of left eye
			xreye=xp-outr*cos(theta); //x center of right eye
			yreye=yp+outr*sin(theta); //y center of right eye
			
			for(i=1;i<eyer;i++){
				gfx_ellipse(xleye,yleye,i,i);
				gfx_ellipse(xreye,yreye,i,i);
			} //end for(i=1;i<eyer;i++)
		
			break;
	} //end switch(direction)
} //end drawfrog

int drawlog(int x, int row, int wseg, int hseg, int boardw, int boardh, int len, int col, int board[][col])
{
	int yp=boardh*row+hseg,xb,i,i2; //define parameters
	
		xb=x/boardw;
		for(i=xb;i<=xb+len;i++)
			if(i>=0 && i<col)
				board[row][i]=1; //update board with position of log
		if(xb>0 && xb<=col)
			board[row][xb-1]=0; //update board by resetting previous position of log
		
		for(i=len-1;i>=0;i--){
			gfx_color(150,75,0); //light brown color
			gfx_fill_rectangle(x+wseg/2+i*boardw,yp,2*wseg,hseg);
			gfx_fill_rectangle(x+i*boardw,yp+hseg,2*wseg,hseg);
			gfx_fill_rectangle(x+2.5*wseg+i*boardw,yp+hseg,wseg/2,hseg);
			gfx_fill_rectangle(x+i*boardw,yp+2*hseg,1*wseg,hseg);
			gfx_fill_rectangle(x+1.5*wseg+i*boardw,yp+2*hseg,1.5*wseg,hseg);
	
			gfx_color(100,50,0); //medium brown color
			gfx_fill_rectangle(x+i*boardw,yp+3*hseg,1.5*wseg,hseg);
			gfx_fill_rectangle(x+2*wseg+i*boardw,yp+3*hseg,wseg,hseg);
			gfx_fill_rectangle(x+i*boardw,yp+4*hseg,wseg/2,hseg);
			gfx_fill_rectangle(x+1.5*wseg+i*boardw,yp+4*hseg,wseg,hseg);
			gfx_fill_rectangle(x+2.5*wseg+i*boardw,yp+4*hseg,wseg/2,hseg);
	
			gfx_color(50,25,0); //dark brown color
			gfx_fill_rectangle(x+wseg/2+i*boardw,yp+5*hseg,2*wseg,hseg);
		} //end for(i=0;i<length;i++)
	
	if(x>width) //when log passes width
		x=10-width/2; //reset position
	else
		x++; //increment position to move right
	
	return x; //return new position
	
} //end drawlog

int drawturtle(int x, int row, int wseg, int hseg, int boardw, int boardh, int col, int board[][col])
{
	int xb,yc=boardh*row+4*hseg,hr=10,tr=5,i,it; //define parameters

		xb=x/boardw;
		if(xb<col && xb>=0)
			board[row][xb]=1; //update position of turtle on board
		if(xb+1<col && xb+1>=0)
			board[row][xb+1]=0; //reset previous position of turtle on board
		
		gfx_color(50,25,0); //dark brown color
		for(i=0;i<wseg;i++) //draws shell
			gfx_ellipse(x,yc,i,i);
			
		gfx_color(20,150,0); //green color
		for(i=0;i<hr;i++) //draws head
			gfx_ellipse(x-wseg,yc,i,i);
		
		for(i=tr;i>0;i--) //draws tail
			gfx_triangle(x+wseg,yc+i,x+wseg,yc-i,x+wseg+i,yc);
	
	if(x<0) //if turtle goes off board
		x=width; //reset position of turtle
	else
		x--; //decrement x to move left
		
	return x; //return new position of turtle
	
} //end drawturtle

int drawtruck(int x, int row, int wseg, int hseg, int boardw, int boardh, int num, int len, int col, int board[][col])
{
	int xb,xp=x,yp=boardh*row+hseg,h=5*hseg,w=len*boardw,i,ib;
	
	for(i=0;i<num;i++){
		xb=xp/boardw;
		for(ib=xb;ib<col;ib++){ //update board
			if(ib<=xb+len && ib>=0)
				board[row][ib]=0;
			else if(board[row][ib]==0)
				board[row][ib]=1;
		} //end for(ib=xb;ib<col;ib++)
		
		gfx_color(120,120,120); //gray color
		gfx_fill_rectangle(xp,yp+hseg,w,h);
		
		gfx_color(255,255,0); //yellow color
		gfx_fill_rectangle(xp+wseg/2,yp,wseg/2,hseg);
		gfx_fill_rectangle(xp+wseg/2,yp+h+hseg,wseg/2,hseg);
		gfx_fill_rectangle(xp+w-wseg,yp,wseg/2,hseg);
		gfx_fill_rectangle(xp+w-wseg,yp+h+hseg,wseg/2,hseg);
		
		xp+=2*w;
	} //end for(i=0;i<num;i++)
	
	if(x+num*2*w<0) //if truck goes off board
		x=width; //reset position of truck
	else 
		x--; //decrement position to move left
		
	return x; //return new position
	
} //end drawtruck

int drawcar(int x, int row, int wseg, int hseg, int boardw, int boardh, int num, int len, int col, int board[][col])
{
	int xb,yp=boardh*row+hseg,h=5*hseg,w=len*boardw,i,ib; //define parameters
	
	x+=4*w*num;
	
	for(i=0;i<num;i++){
		xb=x/boardw;
		for(ib=xb+len;ib>=0;ib--){ //update board
			if(ib>=xb && ib<col)
				board[row][ib]=0;
			else if(board[row][ib]==0)
				board[row][ib]=1;
		} //end for(ib=xb+len;ib>=0;i--)
		
		gfx_color(255,0,255); //magenta color
		gfx_fill_rectangle(x,yp+hseg,w,h);
		
		gfx_color(255,255,0); //yellow color
		gfx_fill_rectangle(x+wseg/2,yp,wseg/2,hseg);
		gfx_fill_rectangle(x+wseg/2,yp+h+hseg,wseg/2,hseg);
		gfx_fill_rectangle(x+w-wseg,yp,wseg/2,hseg);
		gfx_fill_rectangle(x+w-wseg,yp+h+hseg,wseg/2,hseg);
		
		x-=4*w;
	} //end for(i=0;i<num;i++)
	
	if(x>width) //if car goes off board
		x=10-width; //reset position
	else
		x++; //increment position to move right
		
	return x; //return new position
	
} //end drawcar

void draw(int col, int board[][col], int level, int x[19], int *frogx, int *frogy)
{
	int wnum=50, wseg=width/wnum, hnum=100, hseg=height/hnum, boardw=width/25, boardh=height/13, temp; //graphics parameters
	int dx=3*level,i;

    for(i=0;i<3;i++){ //draw multiple logs and turtles in the same rows
    	x[0+i*5]=drawlog(x[0+i*5]+=(dx+4),1,wseg,hseg,boardw,boardh,2,col,board); //moves right	
    	x[1+i*5]=drawturtle(x[1+i*5]-=(dx+3),2,wseg,hseg,boardw,boardh,col,board); //moves left
    	x[2+i*5]=drawlog(x[2+i*5]+=(dx+2),3,wseg,hseg,boardw,boardh,4,col,board); //moves right
    	x[3+i*5]=drawlog(x[3+i*5]+=(dx+1),4,wseg,hseg,boardw,boardh,3,col,board); //moves right
    	x[4+i*5]=drawturtle(x[4+i*5]-=(dx),5,wseg,hseg,boardw,boardh,col,board); //moves left
    } //end for(i=0;i<3;i++)
    
    if(*frogy<6 && *frogy>0) //if frog on a moving item
    	for(i=0;i<3;i++) //go through items on the row
    		if(abs(*frogx-x[(*frogy+5*i)-1]/boardw)<=1) //find which item in the row the frog is on
    			*frogx=x[(*frogy+5*i)-1]/boardw; //move the frog with the drifting item

    x[15]=drawtruck(x[15]-=(dx+4),7,wseg,hseg,boardw,boardh,2,4,col,board); //moves left
    x[16]=drawcar(x[16]+=(dx+2),8,wseg,hseg,boardw,boardh,3,2,col,board); //moves right
    x[17]=drawtruck(x[17]-=(dx+3),9,wseg,hseg,boardw,boardh,3,3,col,board); //moves left
    x[18]=drawcar(x[18]+=(dx+5),10,wseg,hseg,boardw,boardh,4,1,col,board); //moves right

} //end draw

char hopper(int *frogx, int *frogy, int row, int col)
{
	char direction;

	direction = gfx_wait();

	if (direction == 'Q'){ //move frog left
		if (*frogx>0)
			(*frogx)--;
	}else if (direction == 'R'){ //move frog up
		if (*frogy>0)
			(*frogy)--;
	}else if (direction == 'S'){ //move frog right
		if (*frogx<col-1)
			(*frogx)++;
	}else if (direction == 'T'){ //move frog down
		if (*frogy<row)
			(*frogy)++;
	} //end if...else if
	
	return direction;

} //end hopper