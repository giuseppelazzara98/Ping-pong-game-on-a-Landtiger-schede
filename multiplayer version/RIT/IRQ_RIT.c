/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h"
#include "../ball_wall/ball_wall.h"
#include "../timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

int pause=0;
extern int score1;
extern int score2;
extern int button_num;
void RIT_IRQHandler (void){
	static int down=0;	
	down++;
	if((LPC_GPIO2->FIOPIN & (1<<10)||LPC_GPIO2->FIOPIN & (1<<11)||LPC_GPIO2->FIOPIN & (1<<12)) == 0){//controllo decimo, 11esimo o 12esimo  pin della porta 2: se è 0 vuol dire che il relativo pulsante è premuto
		reset_RIT();
		if(down==1){
			switch (button_num){
				case 0:
					score1=0;
					score2=0;
					LCD_Clear(Black);
					Wall_Initialization();
					enable_timer(2);
					break;
				case 1:
					BallStart();
					break;
				case 2:
					pause++;
					if(pause == 1){
						disable_timer(1);//disattivo movimento palla
						disable_timer(2);//disattivo pad
						GUI_Text(100,160,(uint8_t *)"PAUSE",White,Black);
					}
					else {
						pause=0;
						GUI_Text(100,160,(uint8_t *)"PAUSE",Black,Black);
						enable_timer(2);//riattivo pad
						enable_timer(1);//riattivo movimento palla
					}
					break;
				default: 
					break;
			}
	}
	}
	else {	/* button released */
		down=0;			
		disable_RIT();
		reset_RIT();
				switch (button_num){
					case 0:
						NVIC_EnableIRQ(EINT0_IRQn);	
						LPC_PINCON->PINSEL4    |= (1 << 20);
						break;
					case 1:
						NVIC_EnableIRQ(EINT1_IRQn);	
						LPC_PINCON->PINSEL4    |= (1 << 22);
						break;
					case 2:
						NVIC_EnableIRQ(EINT2_IRQn);
						LPC_PINCON->PINSEL4    |= (1 << 24);
						break;
				}
		    /* External interrupt 0 pin selection */
	}
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */	
  return;
}
				


/******************************************************************************
**                            End Of File
******************************************************************************/
