
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
int score1=0;
int score2=0;
char text[20];
char text2[20];
int xangle;
int yangle;
int left_point2;
int right_point2;
int last_left2;
int last_right2;
int center2=120;
int pright=1;

void Wall_Initialization(void){
	int i=0;
	for(i=0;i<5;i++){
		LCD_DrawLine(i,0,i,320,Red);//linea verticale sinistra spessa 5px
		LCD_DrawLine(236+i,0,236+i,320,Red);//linea verticale destra spessa 5px
	}
		sprintf(text,"%d",score1);
		GUI_Text(7,150,(uint8_t *)text,Yellow,Black);
		sprintf(text2,"%d",score2);
		GUI_Text(222,150,(uint8_t *)text2,Yellow,Black);
}
void BallStart(){
	x=224;
	y=162;
	xold=227;
	yold=157;
	xangle=5;
	yangle=5;
	ball_creation(x,y,xold,yold);
	init_timer(1,0x1C9C38);// la palla cambierà posizione ogni 75ms
	enable_timer(1);	
}
void ball_creation(int center_x,int center_y,int old_center_x,int old_center_y){
	int i=0;
	for(i=0;i<5;i++){
		LCD_DrawLine(center_x-2,center_y-2+i,center_x+2,center_y-2+i,Green);
		LCD_DrawLine(old_center_x-2,old_center_y-2+i,old_center_x+2,old_center_y-2+i,Black);
}
	//controllo ed eventualmente riscrivo i punteggi se la palla passa sopra
	if(x>=7 && x<=30 && y>=130 && y<=170){
		sprintf(text,"%d",score1);
		GUI_Text(7,150,(uint8_t *)text,Yellow,Black);
	}
	if(x>=212  && x<=235 && y>=130 && y<=170){
		sprintf(text2,"%d",score2);
		GUI_Text(222,150,(uint8_t *)text2,Yellow,Black);
	}

	}
void moveBall(void){
		constr=0;
		tempx=x;
		tempy=y;
		res=directionControl();// controllo direzione palla
		
	if (x<=15 && y<=276 && y>=48){// se muro sinistro
		constr=1;
		if (res==3){
			x=x+xangle;
			y=y+yangle;
		}
		else if(res==4){
			x=x+xangle;
			y=y-yangle;
		}
	}
	 else if(x>=225 && y<=276 && y>=48){//se muro destro
		constr=1;
		
		if(res==2){
			x=x-xangle;
			y=y-yangle;
		}
		else if(res==1){
			x=x-xangle;
			y=y+yangle;
		}
	}
	 else if(x>=15 && y<=47 && x<=233){// se paddle player 2
		constr=1;
		 if(x>=left_point2 && x<=right_point2){
			 			if(x >= center2 - 10 && x <= center2+10){
				//45 gradi
				xangle=5;
				yangle=5;
				init_timer(1,0x1C9C38); //reimposto timer ogni 75 ms per la velocità 
			}
			else if( x < center2 - 15 || x > center2 + 15){
				//75 gradi
				xangle=8;
				yangle=2;
				init_timer(1,0x98968);// reimposto timer ogni 25 ms aumento la velocità di default
			}
			else {
				//60 gradi
				xangle=6;
				yangle=3;				
				init_timer(1,0x1312D0);// reimposto timer ogni 50 ms aumento la velocità di default
			}

		 }
		 else{
		 score1=score1+1;
		sprintf(text,"%d",score1);
		GUI_Text(7,150,(uint8_t *)text,Yellow,Black);
			 if (score1==5) win_function();
		 }
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
			//cambio angolo 
			if(x >= center - 10 && x <= center+10){
				//45 gradi
				xangle=5;
				yangle=5;
				init_timer(1,0x1C9C38); //reimposto timer ogni 75 ms per la velocità 
			}
			//timer per 50ms -> 50*10^-3*25*10^6 = 0x1312D0
			//timer per 75 ms ->75*10^-3*25*10^6 = 0x1C9C38
			else if( x < center - 15 || x > center + 15){
				//75 gradi
				xangle=8;
				yangle=2;
				init_timer(1,0x98968);// reimposto timer ogni 25 ms aumento la velocità di default
			}
			else {
				//60 gradi
				xangle=6;
				yangle=3;				
				init_timer(1,0x1312D0);// reimposto timer ogni 50 ms aumento la velocità di default
			}

			
			}
		else{
		score2=score2+1;
		sprintf(text2,"%d",score2);
		GUI_Text(222,150,(uint8_t *)text2,Yellow,Black);
		if(score2==5) win_function();
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

void paddle2(void){	
	static int a=0;
		if (center2==215)
			pright=0;
		else if(center2==25)
			pright=1;
		right_point2=center2+20;
		left_point2=right_point2-40;
		for(a=0;a<10;a++){
		LCD_DrawLine(last_left2,32+a,last_right2,32+a,Black);
		LCD_DrawLine(left_point2,32+a,right_point2,32+a,Green);
		}
		switch(pright){
			case 1:
				center2=center2+19;
				break;
			case 0:
				center2=center2-19;
				break;
			default: 
				break;
		
		}
		last_right2=right_point2;
		last_left2=left_point2;
		
}
void win_function(void){
	if (score2==5){			
				GUI_Text2(100,90,(uint8_t *)"NIW UOY",White,Black);
				GUI_Text(90,230,(uint8_t *)"YOU LOSE",White,Black);
				disable_timer(1);//disabilito movimento palla
				disable_timer(2);}//disabilito pad
		else if (score1==5){		 
			GUI_Text(90,230,(uint8_t *)"YOU WIN",White,Black);
			GUI_Text2(88,90,(uint8_t *)"ESOL UOY",White,Black);
			disable_timer(1);//disabilito movimento palla
			disable_timer(2);//disabilito pad	
		}
}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
