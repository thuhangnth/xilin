/***************************** Include Files ********************************/

#include "xtft.h"
#include "xparameters.h"

/************************** Constant Definitions ****************************/
/**
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define TFT_DEVICE_ID    XPAR_TFT_0_DEVICE_ID
#define DDR_HIGH_ADDR    XPAR_PS7_DDR_0_S_AXI_HIGHADDR 

#ifndef DDR_HIGH_ADDR
#warning "CHECK FOR THE VALID DDR ADDRESS IN XPARAMETERS.H"
#endif

#define DISPLAY_COLUMNS  640
#define DISPLAY_ROWS     480


/**
 * User has to specify a 2MB memory space for filling the frame data.
 * This constant has to be updated based on the memory map of the
 * system.
 */
#define TFT_FRAME_ADDR        0x10000000

void drawCircle(int x0, int y0, int r)
{
	int x = r;
	int y =0;
	int re, yChange, xChange, dec;
	drawHorLine(&TftInstance, y0, x0-r, x0+r)
	while (0<=x)
	{
		y++;
		re =  x^2 + y^2 - r^2;
		yChange = 2*y+1;
		xChange = 1-2*x;
		dec = 2*(re+yChange)+xChange;
		if(dec>0)
		{
			x--;	
		{
		drawHorLine(&TftInstance, y0+y, x0-x, x0+x, 0x000000ff)
		drawHorLine(&TftInstance, y0-y, x0-x, x0+x, 0x000000ff)
	}
	
}

void drawHorLine(XTft *Tft, int y, int x1, int x2, int col)
{
	int i = 0;
	for (i=x1, i<= x2, i++)
	{
		XTft_SetPixel(Tft, i, y, colour)
	}	
}