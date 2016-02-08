/*
 * thread.c
 *
 *  Created on: Feb 8, 2016
 *      Author: Mason
 */

#include "thread.h"


int main (void) {

  print("-- Entering main() --\r\n");
  //Initialize Xilkernel
  xilkernel_init();

  //Add main_prog as the static thread that will be invoked by Xilkernel
  xmk_add_static_thread(main_prog, 0);

  //Start Xilkernel
  xilkernel_start();

  //Control does not reach here
  return 0;
}

void* thread_func_1 () {
  while(1) {
    genXY();
    sleep(1);
  }
}


void* thread_func_2 () {
	initTFT();
	 XTft_SetPos(&TftInstance, 0,0);
	 XTft_SetPosChar(&TftInstance, 0,0);
	XTft_SetColor(&TftInstance, 0x00ffffff, 0x00ffffff);
	XTft_FillScreen(&TftInstance, 0, 0,640,480,0x00ffffff); // white
	while(1) {
    drawCircle(x,y,radius);
    sleep(1);
  }
}

void genXY()
{
	char *parse;
	x = rand() % 640;
	y = rand() % 480;
	parse = parseStr();
	printXY(parse);
}

char* parseStr()
{
	int temp;
	static char string[7];
	if (x<100) {
		if(x<10) {
			string[0] = '0';
			string[1] = '1';
			string[2] = (char) x;
		}
		else {
			string[0] = '0';
			string[1] = (char) x/10;
			string[2] = (char) x%10;
		}
	}
	else {
		string[0] = (char) x/100;
		temp = x%100;
		temp /= 10;
		string[1] = (char) temp;
		string[2] = (char) temp%10;
	}
	if (y<100) {
			if(y<10) {
				string[3] = '0';
				string[4] = '1';
				string[5] = (char) x;
			}
			else {
				string[3] = '0';
				string[4] = (char) x/10;
				string[5] = (char) x%10;
			}
		}
	else {
		string[3] = (char) y/100;
		temp = y%100;
		temp /= 10;
		string[4] = (char) temp;
		string[5] = (char) temp%10;
	}
	string[6] = '\0';
	return string;
}

void* main_prog(void *arg) {  // This thread is statically created and has priority 0 (This is the highest possible)

  int ret;

  print("-- Entering main_prog() --\r\n");

  //init semaphore
  ret = sem_init(&sem,0,1);
  if(ret != 0) {
	  xil_printf("ERROR (%d) initializing semaphore...\r\n", ret);
  }
  //start thread 1
  ret = pthread_create (&tid1, NULL, (void*)thread_func_1, NULL);
  if (ret != 0) {
    xil_printf ("-- ERROR (%d) launching thread_func_1...\r\n", ret);
  }
  else {
    xil_printf ("Thread 1 launched with ID %d \r\n",tid1);
  }

  //start thread 2
  ret = pthread_create (&tid2, NULL, (void*)thread_func_2, NULL);
  if (ret != 0) {
    xil_printf ("-- ERROR (%d) launching thread_func_2...\r\n", ret);
  }
  else {
    xil_printf ("Thread 2 launched with ID %d \r\n",tid2);
  }


  return 0;
}
