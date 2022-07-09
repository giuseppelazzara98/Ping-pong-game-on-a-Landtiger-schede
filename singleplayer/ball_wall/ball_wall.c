
/* Includes ------------------------------------------------------------------*/
#include "../GLCD/GLCD.h" 
#include "../GLCD/AsciiLib.h"
#include "../timer/timer.h"
#include "ball_wall.h"
#include "stdlib.h"
#include "stdio.h"
int x,y,xold,yold;
extern int left_point;
extern int right_point;
extern int center;
int res;
int constr;
int tempx,tempy;
const int freqs[8]={2120,1890,1684,1592,1417,1263,1125,1062};
int score=0;
int record_score=100;
char text[20];
char text2[20];
int xangle;
int yangle;

void Wall_Initialization(void){
	int i=0;
	for(i=0;i<5;i++){
		LCD_DrawLine(i,0,i,278,Red);//linea verticale sinistra spessa 5px
		LCD_DrawLine(236+i,0,236+i,278,Red);//linea verticale destra spessa 5px
		LCD_DrawLine(5,i,236,i,Red);//linea orizzontale superiore	
	}
		sprintf(text,"%d",score);
		GUI_Text(7,150,(uint8_t *)text,Yellow,Black);
		sprintf(text2,"%d",record_score);
		GUI_Text(200,8,(uint8_t *)text2,Blue2,Black);
}
void BallStart(){
	x=230;
	y=162;
	xold=227;
	yold=157;
	xangle=5;
	yangle=5;
	ball_creation(x,y,xold,yold);
	init_timer(1,0x98968);// la palla cambierà posizione ogni 25ms
	enable_timer(1);	
}
void ball_creation(int center_x,int center_y,int old_center_x,int old_center_y){
	int i=0;
	for(i=0;i<5;i++){
		LCD_DrawLine(center_x-2,center_y-2+i,center_x+2,center_y-2+i,Green);
		LCD_DrawLine(old_center_x-2,old_center_y-2+i,old_center_x+2,old_center_y-2+i,Black);
}
	//controllo ed eventualmente riscrivo i punteggi 
	if(x>=7 && x<=30 && y>=130 && y<=170){
		sprintf(text,"%d",score);
		GUI_Text(7,150,(uint8_t *)text,Yellow,Black);
	}
	if(x>=200 && x<=276 && y>=5 && y <=40)
		sprintf(text2,"%d",record_score);
		GUI_Text(200,8,(uint8_t *)text2,Blue2,Black);
	}
void moveBall(void){
		constr=0;
		tempx=x;
		tempy=y;
		res=directionControl();// controllo direzione palla
		
	if (x<=12 && y<=276){// se muro sinistro
		constr=1;
		ballSound(0);
		if (res==3){
			x=x+xangle;
			y=y+yangle;
		}
		else if(res==4){
			x=x+xangle;
			y=y-yangle;
		}
	}
	 else if(x>=226 && y<=276){//se muro destro
		constr=1;
		ballSound(0);
		if(res==2){
			x=x-xangle;
			y=y-yangle;
		}
		else if(res==1){
			x=x-xangle;
			y=y+yangle;
		}
	}
	 else if(x>=8 && y<=8 && x<=233){// se muro superiore
		constr=1;
		ballSound(0);
		if(res==2){
			x=x+xangle;
			y=y+yangle;
		}
		else if(res==4){
			x=x-xangle;
			y=y+yangle;
		}
	}
	else if( y>=272 ){ // soglia punteggio
		constr=1;
		if(x>=left_point && x<=right_point){
		//PUNTO
			ballSound(7);
			if(score <100)
			score=score+5;
			else score=score+10;
			if (score>=record_score){
				record_score=score;
				sprintf(text2,"%d",record_score);
				GUI_Text(200,8,(uint8_t *)text2,Blue2,Black);
			}
			sprintf(text,"%d",score);
			GUI_Text(7,150,(uint8_t *)text,Yellow,Black);
			//cambio angolo 
			if(x >= center - 10 && x <= center+10){
				//45 gradi
				xangle=5;
				yangle=5;
				init_timer(1,0x98968); //reimposto timer ogni 25 ms per la velocità 
			}
			else if( x < center - 15 || x > center + 15){
				//75 gradi
				xangle=8;
				yangle=2;
				init_timer(1,0x1E848);// reimposto timer ogni 5 ms aumento la velocità di default
			}
			else {
				//60 gradi
				xangle=6;
				yangle=3;				
				init_timer(1,0x3D090);// reimposto timer ogni 10 ms aumento la velocità di default
			}
			if(res==1){
				x=x+xangle;
				y=y-yangle;
			}
			else if(res==3){
				x=x-xangle;
				y=y-yangle;
			}
			
			}
			else{ //PERSO 
			GUI_Text(90,160,(uint8_t *)"YOU LOSE",White,Black);
			disable_timer(1);//disabilito movimento palla
			disable_timer(2);//disabilito pad
		}
			
	}
	
	if (constr==0){//entro qui se non ho colpito nessun muro o il pad
		switch(res){
			case 1:
				x=x+xangle;
				y=y+yangle;
				break;
			case 2:
				x=x+xangle;
				y=y-yangle;
				break;
			case 3:
				x=x-xangle;
				y=y+yangle;
				break;
			case 4:
				x=x-xangle;
				y=y-yangle;
				break;
		
		}
	}
	xold=tempx;
	yold=tempy;
	ball_creation(x,y,xold,yold);
}

int directionControl(void){
	int i, j;
	int res;
	i=x-xold;
	j=y-yold;
	if(i>0 && j>0){
		res=1;
	}
	if(i>0 && j<0){
		res=2;
	}
	if(i<0 && j>0){
		res=3;
	}
	if(i<0 && j<0){
		res=4;
	}
	return res;
	//1 da alto sinistra a basso destra
	//2 da basso sinistra a altro destra
	//3 da alto  destra a basso sinistra
	//4 da basso destra a alto sinistra
}

void ballSound(int pitch){
	disable_timer(0);
	reset_timer(0);
	init_timer(0,freqs[pitch]/8);
	enable_timer(0);
}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
