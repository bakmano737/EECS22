/*********************************************************************/ 
/* Advanced.h: header file for advanced DIP operations	             */ 
/*                                                                   */
/* 10/07/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment3 FAll2011             */
/*********************************************************************/

#include <stdio.h>
#include <string.h>
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"

void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int i, j;
	for(i = 0; i < WIDTH; i++){
		for(j = 0; j < HEIGHT; j++){
			B[i][j] = (R[i][j] + G[i][j] + B[i][j]) / 5;
			R[i][j] = B[i][j] * 1.6;
			G[i][j] = B[i][j] * 1.6;
		}
	}
}

/* blur the image */
void
Blur(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int             x, y, m, n, a, b;
	int             tmpR = 0;
	int             tmpG = 0;
	int             tmpB = 0;
	
    unsigned char   R_tmp[WIDTH][HEIGHT];
	unsigned char   G_tmp[WIDTH][HEIGHT];
	unsigned char   B_tmp[WIDTH][HEIGHT];

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			R_tmp[x][y] = R[x][y];
			G_tmp[x][y] = G[x][y];
			B_tmp[x][y] = B[x][y];
		}

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			for (n = -2; n <= 2; n++)
				for (m = -2; m <= 2; m++) {
					a = x + m;
					b = y + n;
					if (a > WIDTH - 1)
						a = WIDTH - 1;
					if (a < 0)
						a = 0;
					if (b > HEIGHT - 1)
						b = HEIGHT - 1;
					if (b < 0)
						b = 0;

					tmpR += R_tmp[a][b];
					tmpG += G_tmp[a][b];
					tmpB += B_tmp[a][b];
				}

			R[x][y] = tmpR / 25;
			G[x][y] = tmpG / 25;
			B[x][y] = tmpB / 25;
			tmpR = tmpG = tmpB = 0;	/* for next loop */
		}

}

void WaterMarkDecipher(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int i = 0;
    unsigned char ch = 0, chtmp;
    unsigned char Message[MLEN];
 
    while(i < WIDTH / 4){
        chtmp = R[i][0] & 0x1;
		
        ch |=  (chtmp << (i % 8));
		i ++;
        if(i % 8 == 0){
            Message[i / 8 - 1] = ch;
			ch = 0;
        }
	}
    printf("The watermark message is \"%s\"\n", Message);
}

void EdgeDetection(double K, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int i, j;
	unsigned int d0, d1;
	unsigned char rt[WIDTH][HEIGHT], bt[WIDTH][HEIGHT], gt[WIDTH][HEIGHT];

	for(i = 0; i < WIDTH - 1; i++){
		for(j = 0; j < HEIGHT - 1; j++){
			d0 = (R[i][j] - R[i + 1][j]) * (R[i][j] - R[i + 1][j])
				+(G[i][j] - G[i + 1][j]) * (G[i][j] - G[i + 1][j])
				+(B[i][j] - B[i + 1][j]) * (B[i][j] - B[i + 1][j]);

			d1 = (R[i][j] - R[i][j + 1]) * (R[i][j] - R[i][j + 1])
				+(G[i][j] - G[i][j + 1]) * (G[i][j] - G[i][j + 1])
				+(B[i][j] - B[i][j + 1]) * (B[i][j] - B[i][j + 1]);

			if(d0 > K * K || d1 > K * K)
			{
				rt[i][j] = 255;
				gt[i][j] = 255;
				bt[i][j] = 255;
			}
			else
			{
				rt[i][j] = 0;
				gt[i][j] = 0;
				bt[i][j] = 0;
			}
		}
	}

	for(i = 0; i < WIDTH - 1; i++){
		for(j = 0; j < HEIGHT - 1; j++){
			R[i][j] = rt[i][j];
			G[i][j] = gt[i][j];
			B[i][j] = bt[i][j];
		}
	}
}


/* auto test*/
void
AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	char            fname[SLEN] = "sailing";

	ReadImage(fname, R, G, B);
	BlackNWhite(R, G, B);
	SaveImage("bw", R, G, B);
#ifdef DEBUG 
	printf("Black & White tested!\n\n");
#endif

	ReadImage(fname, R, G, B);
	Negative(R, G, B);
	SaveImage("negative", R, G, B);
#ifdef DEBUG
	printf("Negative tested!\n\n");
#endif

	ReadImage(fname, R, G, B);
	HFlip(R, G, B);
	SaveImage("hflip", R, G, B);
#ifdef DEBUG
	printf("HFlip tested!\n\n");
#endif

	ReadImage(fname, R, G, B);
	HMirror(R, G, B);
	SaveImage("hmirror", R, G, B);
#ifdef DEBUG
	printf("HMirror tested!\n\n");
#endif
    
    ReadImage(fname, R, G, B);
	VFlip(R, G, B);
	SaveImage("vflip", R, G, B);
#ifdef DEBUG
	printf("VFlip tested!\n\n");
#endif
    
	ReadImage(fname, R, G, B);
	VMirror(R, G, B);
	SaveImage("vmirror", R, G, B);
#ifdef DEBUG
	printf("VMirror tested!\n\n");
#endif

	ReadImage(fname, R, G, B);
	Aging(R, G, B);
	SaveImage("aging", R, G, B);
#ifdef DEBUG
	printf("Aging tested!\n\n");
#endif

	ReadImage(fname, R, G, B);
    WaterMarkDecipher(R, G, B);
#ifdef DEBUG
	printf("Watermark Deciphering tested!\n\n");
#endif

	ReadImage(fname, R, G, B);
	Blur(R, G, B);
	SaveImage("blur", R, G, B);
#ifdef DEBUG
	printf("Blur tested!\n\n");
#endif

	ReadImage(fname, R, G, B);
	EdgeDetection(60, R, G, B);
	SaveImage("edge", R, G, B);
#ifdef DEBUG
	printf("EdgeDetection tested!\n\n");
#endif

}

/* EOF Advanced.c */
