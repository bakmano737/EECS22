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
#include "Image.h"
#include "FileIO.h"
#include "Advanced.h"
#include "DIPs.h"

/* print a menu */
void            PrintMenu();

int             main()
{
	/*
	 * Two dimensional arrays to hold the current image data. One array
	 * for each color component
	 */

	char            fname[SLEN];
	int             choice;       
	double          K;
	unsigned int	xo, yo, W, H;
	unsigned int 	percentage;

	IMAGE *image	= NULL;
	PrintMenu();
	printf("please make your choice: ");
	scanf("%d", &choice);

	while (choice != 16) {
		switch (choice) {
		case 1:
			printf("Please input the file name to load: ");
			if(image){
				DeleteImage(image);
			}
			scanf("%s", fname);
			GetImageSize(fname, &W, &H);
			image = CreateImage(W, H);
			ReadImage(fname, image);
			break;
		case 2:
			printf("Please input the file name to save: ");
			scanf("%s", fname);
			SaveImage(fname, image);
			break;
		case 3:
			BlackNWhite(image);
	        printf("\"Black & White\" operation is done!\n");
			break;
		case 4:
            Negative(image);
			printf( "\"Negative\" operation is done!\n" );
			break;
		case 5:
			HFlip(image);
			printf("\"HFlip\" operation is done!\n");
			break;
		case 6:
			HMirror(image);
			printf("\"HMirror\" operation is done!\n");
			break;
        case 7:
            VFlip(image);
            printf("\"VFlip\" operation is done!\n");
            break;
        case 8:
            VMirror(image);
            printf("\"VMirror\" operation is done!\n");
            break;
		case 9:
			Aging(image);
			printf("\"Aging\" operation is done!\n");
			break;
		/*case 10:
			WaterMarkDecipher(W, H, R, G, B);
			printf("\"Decipher the Watermark Message\" operation is done!\n");
			break;*/
		case 10:
			Blur(image);
			printf("\"Blur\" operation is done!\n");
			break;
		case 11:
			printf("Please give the threshold value: ");
			scanf("%lf", &K);
			EdgeDetection(K, image);
			printf("\"EdgeDetection\" operation is done!\n");
			break;
		case 12:
			image = Rotate(image);
			printf("\"Rotate 90 degree clockwise\" operation is done!\n");
			break;
		case 13:
			printf("Please input the resizing percentage (integer between 1~500): ");
			scanf("%d", &percentage);
			image = Resize(percentage, image);
			printf("\"Resizing the image\" operation is done!\n");
			break;
		case 14:
			printf("Please input the file name for the second image: ");
			scanf("%s", fname);
			printf("Please input x coordinate of the overlay image: ");
			scanf("%d", &xo);
			printf("Please input y coordinate of the overlay image: ");
			scanf("%d", &yo);
			Overlay(fname, image, xo, yo);
			printf("\"Image Overlay\" operation is done!\n");
			break;
        case 15:
            AutoTest("sailing");
			break;
		case 16:
			break;
		default:
			printf("Invalid selection!\n");
			break;
		}

		PrintMenu();
		printf("Please make your choice: ");
		scanf("%d", &choice);
	}

	if(image){
		DeleteImage(image);
		image = NULL;
	}
	return 0;
}

/* print a menu */
void
PrintMenu()
{
	printf("\n--------------------------------\n");
	printf(" 1:  Load a PPM image\n");
	printf(" 2:  Save an image in PPM and JPEG format\n");
	printf(" 3:  Change a color image to black and white\n");
	printf(" 4:  Make a negative of an image\n");
	printf(" 5:  Flip an image horizontally\n");
	printf(" 6:  Mirror an image horizontally\n");
    printf(" 7:  Flip an image vertically \n");
	printf(" 8:  Mirror an image vertically \n");
	printf(" 9:  Age the image \n");
/*	printf("10:  Decipher the watermark in the image\n");*/
	printf("10:  Blur an image \n");
	printf("11:  Detect edges \n");
	printf("12:  Rotate 90 degrees clockwise \n");
	printf("13:  Resize the image \n");
	printf("14:  Overlay an image \n");
    printf("15:  Test all functions\n");  
	printf("16:  Exit\n");
}

/* EOF PhotoLab.c */
