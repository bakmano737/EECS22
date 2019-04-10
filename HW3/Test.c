/*********************************************************************/
/* test.c: homework assignment #3, for EECS 22,  Fall 2011           */
/*                                                                   */
/* History:                                                          */
/* 10/07/11 Weiwei Chen  updated for EECS22 assignment3 FAll2011     */
/* 						 initial version                    		 */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constants.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"


int             main()
{
	/*
	 * Two dimensional arrays to hold the current image data. One array
	 * for each color component
	 */
	unsigned char   R[WIDTH][HEIGHT];
	unsigned char   G[WIDTH][HEIGHT];
	unsigned char   B[WIDTH][HEIGHT];

	AutoTest(R, G, B);
	return 0;
}

