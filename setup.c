/*
 *
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "callbacks.h"

PSP_MODULE_INFO("PSPGL Setup", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf pspDebugScreenPrintf

int main(int argc, char* argv[]) {

	pspDebugScreenInit();

//	setupCallbacks();

	printf("debug: START\n");

//	while (running()) {
//		printf("gloob> Hello world!\n");
//	}

	printf("debug: STOP\n");

	sceKernelDelayThread(5000*1000);
	sceKernelExitGame();

	return 0;
}
