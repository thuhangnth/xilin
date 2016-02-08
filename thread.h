/*
 * thread
 *
 *  Created on: Feb 8, 2016
 *      Author: Mason
 */

#ifndef THREAD_
#define THREAD_
#include "xmk.h"
#include "sys/init.h"
#include <pthread.h>
#include <stdlib.h>
#include "display.h"

#define radius 7
volatile int x=0,y=0;
pthread_t tid1,tid2;
static sem_t sem;

void* main_prog(void *arg);
void genXY();
char* parseStr();



#endif /* THREAD_ */
