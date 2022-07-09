/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			GLCD.h
** Descriptions:		Has been tested SSD1289、ILI9320、R61505U、SSD1298、ST7781、SPFD5408B、ILI9325、ILI9328、
**						HX8346A、HX8347A
**------------------------------------------------------------------------------------------------------
** Created by:			AVRman
** Created date:		2012-3-10
** Version:				1.3
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:		
********************************************************************************************************/

#ifndef __ballwall_H 
#define __ballwall_H

void Wall_Initialization(void);
void BallStart(void);
void ball_creation(int center_x,int center_y,int old_center_x,int old_center_y);
void moveBall(void);
int directionControl(void);
void paddle2(void);
void win_function(void);
#endif 

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
