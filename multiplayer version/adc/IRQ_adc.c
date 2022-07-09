/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../GLCD/GLCD.h"
#include "stdlib.h"
/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current=0x7FF;   
unsigned short AD_last = 0x7FF;     /* Last converted value               */
int left_point;
int right_point;
int last_right;
int last_left;
int f;
int center;
void ADC_IRQHandler(void) {
  	
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
  if( (AD_current >= AD_last+270 || AD_current<=AD_last-270) && ((abs((int)AD_current-(int)AD_last))<1500) ){
			
			center=AD_current*190/0xFFF;//200
			center=center+25;//20
			right_point=center+20;
			left_point=right_point-40;
		for(f=0;f<10;f++){
		LCD_DrawLine(last_left,278+f,last_right,278+f,Black);
		LCD_DrawLine(left_point,278+f,right_point,278+f,Green);
		}
		last_right=right_point;
		last_left=left_point;
		AD_last = AD_current;	
  }	
}
