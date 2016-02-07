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

/**************************** Type Definitions ******************************/

/************************** Function Prototypes *****************************/

int initTFT();
void drawCircle(int x0, int y0, int r);
void drawHorLine(XTft *Tft, int y, int x1, int x2, int col);


/************************** Variable Definitions ****************************/

static XTft TftInstance;

int initTFT()
{
	int Status;
  XTft_Config *TftConfigPtr;
  unsigned int *col;

  unsigned char c;

  /*
   * Get address of the XTft_Config structure for the given device id.
   */
  TftConfigPtr = XTft_LookupConfig(TFT_DEVICE_ID);
  if (TftConfigPtr == (XTft_Config *)NULL) {
    return XST_FAILURE;
  }

  /*
   * Initialize all the TftInstance members and fills the screen with
   * default background color.
   */
  Status = XTft_CfgInitialize(&TftInstance, TftConfigPtr,
      TftConfigPtr->BaseAddress);
  if (Status != XST_SUCCESS) {
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
  
  return XST_SUCCESS
}

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