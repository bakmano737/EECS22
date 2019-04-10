/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2011       */
/*                                                                   */
/* History:                                                          */
/* 10/07/11 Weiwei Chen  updated for EECS22 assignment3 FAll2011     */
/* 09/27/11 Weiwei Chen  updated for EECS22 assignment2 Fall2011     */
/* 11/11/04 Rainer Doemer:   update for EECS 10 formatting style     */
/* 11/10/04 Rustam Sengupta: initial template version                */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Constants.h"
#include "FileIO.h"
#include "Advanced.h"
#include "DIPs.h"


int             main()
{
	/*
	 * Two dimensional arrays to hold the current image data. One array
	 * for each color component
	 */
	unsigned char   R[WIDTH][HEIGHT];
	unsigned char   G[WIDTH][HEIGHT];
	unsigned char   B[WIDTH][HEIGHT];

	char            fname[SLEN];
	int             choice;       
	double          K;


	PrintMenu();
	printf("please make your choice: ");
	scanf("%d", &choice);

	while (choice != 14) {
		switch (choice) {
		case 1:
			printf("Please input the file name to load: ");
			scanf("%s", fname);
			ReadImage(fname, R, G, B);
			break;
		case 2:
			printf("Please input the file name to save: ");
			scanf("%s", fname);
			SaveImage(fname, R, G, B);
			break;
		case 3:
			BlackNWhite(R, G, B);
	        printf("\"Black & White\" operation is done!\n");
			break;
		case 4:
            Negative(R,G,B);
			printf( "\"Negative\" operation is done!\n" );
			break;
		case 5:
			HFlip(R, G, B);
			printf("\"HFlip\" operation is done!\n");
			break;
		case 6:
			HMirror(R, G, B);
			printf("\"HMirror\" operation is done!\n");
			break;
        case 7:
            VFlip(R, G, B);
            printf("\"VFlip\" operation is done!\n");
            break;
        case 8:
            VMirror(R, G, B);
            printf("\"VMirror\" operation is done!\n");
            break;
		case 9:
			Aging(R, G, B);
			printf("\"Aging\" operation is done!\n");
			break;
		case 10:
			WaterMarkDecipher(R, G, B);
			printf("\"Decipher the Watermark Message\" operation is done!\n");
			break;
			
		case 11:
			Blur(R, G, B);
			printf("\"Blur\" operation is done!\n");
			break;
		case 12:
			printf("Please give the threshold value: ");
			scanf("%lf", &K);
			EdgeDetection(K, R, G, B);
			printf("\"EdgeDetection\" operation is done!\n");
			break;
        case 13:
            AutoTest(R, G, B);
			break;
		case 14:
			break;
		default:
			printf("Invalid selection!\n");
			break;
		}

		PrintMenu();
		printf("please make your choice: ");
		scanf("%d", &choice);
	}

	return 0;
}


