/*********************************************************************/
/* DIPs.c: homework assignment #3, for EECS 22,  Fall 2011       	 */
/*                                                                   */
/* History:                                                          */
/* 10/07/11 Weiwei Chen  updated for EECS22 assignment3 FAll2011     */
/* 						 initial version                			 */
/*********************************************************************/

#include <stdio.h>
#include <string.h>
#include "Constants.h"
#include "FileIO.h"
#include "DIPs.h"

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
	printf("10:  Decipher the watermark in the image\n");
	printf("11:  Blur an image \n");
	printf("12:  Detect the Edge \n");
    printf("13:  Test all functions\n");  
	printf("14:  Exit\n");
}

/* reverse image color */
void
BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int             x, y;

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			R[x][y] = G[x][y] = B[x][y]
				= (R[x][y] + G[x][y] + B[x][y]) / 3;
		}
}

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y;

    for( y=0; y<HEIGHT; y++ ){
        for( x=0; x<WIDTH; x++ )
          {
            R[x][y]=255-R[x][y];
            G[x][y]=255-G[x][y];
            B[x][y]=255-B[x][y];
          }
	}
}


/* flip image horizontally */
void
HFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int             x, y;
	unsigned char   r, g, b;

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH / 2; x++) {
			r = R[WIDTH - 1 - x][y];
			g = G[WIDTH - 1 - x][y];
			b = B[WIDTH - 1 - x][y];

			R[WIDTH - 1 - x][y] = R[x][y];
			G[WIDTH - 1 - x][y] = G[x][y];
			B[WIDTH - 1 - x][y] = B[x][y];

			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	}
}

/* mirror image horizontally */
void
HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int             x, y;

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH / 2; x++) {
			R[WIDTH - 1 - x][y] = R[x][y] ;
			G[WIDTH - 1 - x][y] = G[x][y] ;
			B[WIDTH - 1 - x][y] = B[x][y] ;
		}
	}
}

/* flip image vertically */
void
VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int             x, y;
	unsigned char   r, g, b;
    
	for (y = 0; y < HEIGHT/2; y++) {
		for (x = 0; x < WIDTH; x++) {
			r = R[x][HEIGHT - 1 - y];
			g = G[x][HEIGHT - 1 - y];
			b = B[x][HEIGHT - 1 - y];
            
			R[x][HEIGHT - 1 - y] = R[x][y];
			G[x][HEIGHT - 1 - y] = G[x][y];
			B[x][HEIGHT - 1 - y] = B[x][y];
            
			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	}
}

/* mirror image vertically */
void
VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int             x, y;
    
	for (y = 0; y < HEIGHT / 2; y++) {
		for (x = 0; x < WIDTH; x++) {
			R[x][HEIGHT - 1 - y] = R[x][y] ;
			G[x][HEIGHT - 1 - y] = G[x][y] ;
			B[x][HEIGHT - 1 - y] = B[x][y] ;
		}
	}
}

/* EOF DIPs.c */
