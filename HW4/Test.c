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
	char            fname[SLEN];

	printf("Please input the file name to load for testing: ");
	scanf("%s", fname);

	AutoTest(fname);

	return 0;
}

/* EOF Test.c */
