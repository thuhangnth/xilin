#include "display.h"
#include <math.h>

int initTFT()
{
	int Status;
	XTft_Config *TftConfigPtr;

	/*
	* Get address of the XTft_Config structure for the given device id.
	*/
	TftConfigPtr = XTft_LookupConfig(TFT_DEVICE_ID);
	if (TftConfigPtr == (XTft_Config *)NULL) 
	{
    return XST_FAILURE;
	}

	/*
	* Initialize all the TftInstance members and fills the screen with
	* default background color.
	*/
	Status = XTft_CfgInitialize(&TftInstance, TftConfigPtr,
      TftConfigPtr->BaseAddress);
	if (Status != XST_SUCCESS) 
	{
		return XST_FAILURE;
	}

	/*
	* Wait till Vsync(Video address latch) status bit is set before writing
	* the frame address into the Address Register. This ensures that the
	* current frame has been displayed and we can display a new frame of
	* data. Checking the Vsync state ensures that there is no data flicker
	* when displaying frames in real time though there is some delay due to
	* polling.
	*/
	while (XTft_GetVsyncStatus(&TftInstance) !=
      XTFT_IESR_VADDRLATCH_STATUS_MASK);

	/*
	* Change the Video Memory Base Address from default value to
	* a valid Memory Address and clear the screen.
	*/
	XTft_SetFrameBaseAddr(&TftInstance, TFT_FRAME_ADDR);
	XTft_ClearScreen(&TftInstance);

	XTft_SetPos(&TftInstance, 0,0);
	XTft_SetPosChar(&TftInstance, 0,0);

	XTft_SetColor(&TftInstance, 0x00000000, 0x00ffffff);

	XTft_FillScreen(&TftInstance, 0, 0,639,479,0x00ffffff); // white


  
	return XST_SUCCESS;
}

void drawCircle(int x0, int y0, int r)
{
	int x = r;
	int y =0;
	int re, yChange, xChange, dec;
	drawHorLine(&TftInstance, y0, x0-r, x0+r,0x000000ff);
	while (y<=x)
	{
		y++;
		re =  pow(x,2) + pow(y,2) - pow(r,2);
		yChange = 2*y+1;
		xChange = 1-2*x;
		dec = 2*(re+yChange)+xChange;
		if(dec>0)
		{
			x -= 1;
		}
		drawHorLine(&TftInstance, y0+y, x0-x, x0+x, 0x000000ff);
		drawHorLine(&TftInstance, y0-y, x0-x, x0+x, 0x000000ff);
		drawHorLine(&TftInstance, y0+x, x0-y, x0+y, 0x000000ff);
		drawHorLine(&TftInstance, y0-x, x0-y, x0+y, 0x000000ff);
	}
	xil_printf("5\r\n");
}

void drawHorLine(XTft *Tft, int y, int x1, int x2, int col)
{
	int i = 0;
	for (i=x1; i<= x2; i++)
	{
		XTft_SetPixel(Tft, i, y, col);
	}	
}

void printXY(char string[])
{
	int i = 0;
	clearScreen();
	XTft_SetPos(&TftInstance, 0,0);
	XTft_SetPosChar(&TftInstance, 0,0);
	//XTft_SetColor(&TftInstance, 0x000000, 0x00ffffff);

	for(i=0; i<strlen(string); i++)
	{
		if(i==3)
		{
			XTft_Write(&TftInstance,',');
		}
		XTft_Write(&TftInstance,string[i]);
	}
}

void clearScreen()
{
	XTft_ClearScreen(&TftInstance);
}

void fillScreen()
{
	xil_printf("1\r\n");
	XTft_SetPos(&TftInstance, 0,0);
	XTft_SetPosChar(&TftInstance, 0,0);
	xil_printf("2\r\n");
	XTft_SetColor(&TftInstance, 0x00000000, 0x00ffffff);
	xil_printf("3\r\n");
	XTft_FillScreen(&TftInstance, 0, 0,639,479,0x00ffffff); // white
	xil_printf("4\r\n");
}
