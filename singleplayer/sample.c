/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "adc/adc.h"
#include "button/button.h"
#include "ball_wall/ball_wall.h"
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{
	
   SystemInit();	/* System Initialization (i.e., PLL)  */
	BUTTON_init();
	LCD_Initialization();
	LCD_Clear(Black);
	Wall_Initialization(); 
	ADC_init();
	init_timer(2,0x180858);//63ms ->63*10^-3*25*10^6 per la gestione del pad
	enable_timer(2);//movimento pad	
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec      */ 
	//init_RIT (0x989680);//100ms							/* RIT Initialization 100 msec      */ 
	
	//SETTAGGIO PIN SPEAKER
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
  //power-down mode
	LPC_SC->PCON |= 0x1;						
	LPC_SC->PCON &= ~(0x2);						
	

  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
