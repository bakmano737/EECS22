/*********************************************************************/ 
/* Advanced.h: header file for advanced DIP operations	             */ 
/*                                                                   */
/* 10/19/11 Weiwei Chen: Add Overlay, Rotate, Resize				 */
/*						 for EECS22 assignment4 Fall2011			 */
/* 10/07/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment3 Fall2011             */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"

void Aging(IMAGE *image)
{
	int x, y;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	unsigned int tmp;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	for(x = 0; x < WIDTH; x++){
		for(y = 0; y < HEIGHT; y++){
			tmp = (GetRPixel(image, x, y) + GetBPixel(image, x, y) + GetGPixel(image, x, y)) / 5;
			SetBPixel(image, x, y, tmp);
			SetRPixel(image, x, y, GetBPixel(image, x, y) * 1.6);
			SetGPixel(image, x, y, GetBPixel(image, x, y) * 1.6);
		}
	}
}

/* blur the image */
void
Blur(IMAGE *image)
{
	int             x, y, m, n, a, b;
	int             tmpR = 0;
	int             tmpG = 0;
	int             tmpB = 0;
	unsigned int WIDTH;
	unsigned int HEIGHT;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	IMAGE *image_tmp = CreateImage(WIDTH, HEIGHT);

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			SetRPixel(image_tmp, x, y, GetRPixel(image, x, y));
			SetGPixel(image_tmp, x, y, GetGPixel(image, x, y));
			SetBPixel(image_tmp, x, y, GetBPixel(image, x, y));
		}

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			for (n = -1; n <= 1; n++)
				for (m = -1; m <= 1; m++) {
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

					tmpR += GetRPixel(image_tmp, a, b);
					tmpG += GetGPixel(image_tmp, a, b);
					tmpB += GetBPixel(image_tmp, a, b);
				}

			SetRPixel(image, x, y, tmpR / 9);
			SetGPixel(image, x, y, tmpG / 9);
			SetBPixel(image, x, y, tmpB / 9);
			tmpR = tmpG = tmpB = 0;	/* for next loop */
		}
	
	DeleteImage(image_tmp);
	image_tmp = NULL;
}

void EdgeDetection(double K, IMAGE *image)
{
	int x, y;
	unsigned int d0, d1;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	IMAGE *image_tmp;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	image_tmp = CreateImage(WIDTH, HEIGHT);
	

	for(x = 0; x < WIDTH - 1; x++){
		for(y = 0; y < HEIGHT - 1; y++){
			d0 = (GetRPixel(image, x, y) - GetRPixel(image, x + 1, y)) *
				 (GetRPixel(image, x, y) - GetRPixel(image, x + 1, y)) + 
				 (GetGPixel(image, x, y) - GetGPixel(image, x + 1, y)) *
				 (GetGPixel(image, x, y) - GetGPixel(image, x + 1, y)) +
				 (GetBPixel(image, x, y) - GetBPixel(image, x + 1, y)) *
				 (GetBPixel(image, x, y) - GetBPixel(image, x + 1, y));

			d1 = (GetRPixel(image, x, y) - GetRPixel(image, x, y + 1)) *
				 (GetRPixel(image, x, y) - GetRPixel(image, x, y + 1)) + 
				 (GetGPixel(image, x, y) - GetGPixel(image, x, y + 1)) *
				 (GetGPixel(image, x, y) - GetGPixel(image, x, y + 1)) +
				 (GetBPixel(image, x, y) - GetBPixel(image, x, y + 1)) *
				 (GetBPixel(image, x, y) - GetBPixel(image, x, y + 1));

			if(d0 > K * K || d1 > K * K)
			{
				SetRPixel(image_tmp, x, y, 255);
				SetGPixel(image_tmp, x, y, 255);
				SetBPixel(image_tmp, x, y, 255);
			}
			else
			{
				SetRPixel(image_tmp, x, y, 0);
				SetGPixel(image_tmp, x, y, 0);
				SetBPixel(image_tmp, x, y, 0);
			}
		}
	}

	for(x = 0; x < WIDTH - 1; x++){
		for(y = 0; y < HEIGHT - 1; y++){
			SetRPixel(image, x, y, GetRPixel(image_tmp, x, y));
			SetGPixel(image, x, y, GetGPixel(image_tmp, x, y));
			SetBPixel(image, x, y, GetBPixel(image_tmp, x, y));
		}
	}
	
	DeleteImage(image_tmp);
	image_tmp = NULL;

}

void Overlay(char f2name[SLEN], IMAGE *image, 
			 unsigned int x_offset, 
			 unsigned int y_offset)
{
	unsigned int HEIGHT2 = 0, WIDTH2 = 0;
	int             x, y;
	
/*  the second image */
	IMAGE	*image2;
        
/*  create the second image */
	GetImageSize(f2name, &WIDTH2, &HEIGHT2);
	image2 = CreateImage(WIDTH2, HEIGHT2);
	ReadImage(f2name, image2);

    for(y=0; y<HEIGHT2; y++){
    	for(x=0; x<WIDTH2;x++){
		   if(!(GetRPixel(image2, x, y) == 255 && GetGPixel(image2, x, y) == 255 && GetBPixel(image2, x, y) == 255) &&
			  !(GetRPixel(image2, x, y) == 102 && GetGPixel(image2, x, y) == 153 && GetBPixel(image2, x, y) == 204))
			{
				SetRPixel(image, x+x_offset, y+y_offset, GetRPixel(image2, x, y));
				SetGPixel(image, x+x_offset, y+y_offset, GetGPixel(image2, x, y));
				SetBPixel(image, x+x_offset, y+y_offset, GetBPixel(image2, x, y));
			}

        }	
    }    
	
	DeleteImage(image2);
	image2 = NULL;

}

/*Rotate 90 degrees clockwise*/
IMAGE *Rotate(IMAGE *image)
{
	int             x, y;
	unsigned int	tmp;
    unsigned int WIDTH;
	unsigned int HEIGHT;    
	IMAGE *image_tmp;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	image_tmp = CreateImage(WIDTH, HEIGHT);

	for(x = 0; x < WIDTH; x ++){
		for(y = 0; y < HEIGHT; y++){
			SetRPixel(image_tmp, x, y, GetRPixel(image, x, y));
			SetGPixel(image_tmp, x, y, GetGPixel(image, x, y));
			SetBPixel(image_tmp, x, y, GetBPixel(image, x, y));
		}
	}

	tmp = image->Width;
	image->Width = image->Height;
	image->Height = tmp;

	for(x = 0; x < WIDTH; x ++){
		for(y = 0; y < HEIGHT; y++){
			SetRPixel(image, HEIGHT -1 - y, x, GetRPixel(image_tmp, x, y));
			SetGPixel(image, HEIGHT -1 - y, x, GetGPixel(image_tmp, x, y));
			SetBPixel(image, HEIGHT -1 - y, x, GetBPixel(image_tmp, x, y));
		}
	}

	DeleteImage(image_tmp);
	image_tmp = NULL;
	return image;
}

/*Resize*/
IMAGE *Resize(	unsigned int percentage, IMAGE *image)
{
	unsigned int    x, y, x1, y1, x2, y2, i, j, tmpR, tmpG, tmpB;
    unsigned int 	WIDTHZ, HEIGHTZ;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	IMAGE *image_tmp;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	

	if(percentage <= 0 || percentage > 500){
		printf("Resizing percentage %d%% is out of the range, Sorry! \n", percentage);
		return image;
	}

	/*for(x = 0; x < WIDTH; x ++){
		for(y = 0; y < HEIGHT; y++){
			SetRPixel(image_tmp, x, y, GetRPixel(*image, x, y));
			SetGPixel(image_tmp, x, y, GetGPixel(*image, x, y));
			SetBPixel(image_tmp, x, y, GetBPixel(*image, x, y));
		}
	}*/

	WIDTHZ = WIDTH * percentage / 100;
	HEIGHTZ = HEIGHT * percentage / 100;
	image_tmp = CreateImage(WIDTHZ, HEIGHTZ);
	
	for(x = 0; x < WIDTHZ; x ++){
		for(y = 0; y < HEIGHTZ; y++){
			x1 = (unsigned int)(x / (percentage / 100.00));
			y1 = (unsigned int)(y / (percentage / 100.00));
			x2 = (unsigned int)((x + 1) / (percentage / 100.00));
			y2 = (unsigned int)((y + 1) / (percentage / 100.00));
			tmpR = tmpB = tmpG = 0;
			
			if(percentage < 100){
				for(i = x1; i < x2; i ++){
					for(j = y1; j < y2; j ++){
						tmpR += GetRPixel(image, i, j);
						tmpG += GetGPixel(image, i, j);
						tmpB += GetBPixel(image, i, j);
					}
				}
				SetRPixel(image_tmp, x, y, tmpR / ((x2 - x1) * (y2 - y1)));
				SetGPixel(image_tmp, x, y, tmpG / ((x2 - x1) * (y2 - y1)));
				SetBPixel(image_tmp, x, y, tmpB / ((x2 - x1) * (y2 - y1)));

			}
			else{
				SetRPixel(image_tmp, x, y, GetRPixel(image, x1, y1));
				SetGPixel(image_tmp, x, y, GetGPixel(image, x1, y1));
				SetBPixel(image_tmp, x, y, GetBPixel(image, x1, y1));
			}
		}
	}

	DeleteImage(image);

	return image_tmp;
}

/* auto test*/
void
AutoTest(const char *fname)
{
	IMAGE *image;
	unsigned int W, H;
	GetImageSize(fname, &W, &H);
	image = CreateImage(W, H);

	ReadImage(fname, image);
	BlackNWhite(image);
	SaveImage("bw", image);
	printf("Black & White tested!\n\n");

	ReadImage(fname, image);
	Negative(image);
	SaveImage("negative", image);
	printf("Negative tested!\n\n");


	ReadImage(fname, image);
	HFlip(image);
	SaveImage("hflip", image);
	printf("HFlip tested!\n\n");


	ReadImage(fname, image);
	HMirror(image);
	SaveImage("hmirror", image);
	printf("HMirror tested!\n\n");

    
    ReadImage(fname, image);
	VFlip(image);
	SaveImage("vflip", image);
	printf("VFlip tested!\n\n");

    
	ReadImage(fname, image);
	VMirror(image);
	SaveImage("vmirror", image);
	printf("VMirror tested!\n\n");


	ReadImage(fname, image);
	Aging(image);
	SaveImage("aging", image);
	printf("Aging tested!\n\n");


	ReadImage(fname, image);
	Blur(image);
	SaveImage("blur", image);
	printf("Blur tested!\n\n");

	ReadImage(fname, image);
	EdgeDetection(60, image);
	SaveImage("edge", image);
	printf("EdgeDetection tested!\n\n");

	ReadImage(fname, image);
	Rotate(image);	
	SaveImage("rotate", image);
	printf("Rotate 90 degrees clockwise tested!\n\n");
	DeleteImage(image);

	GetImageSize(fname, &W, &H);
	image = CreateImage(W, H);
	ReadImage(fname, image);
	image = Resize(150, image);	
	SaveImage("resizeb", image);
	printf("Resizing big in tested!\n\n");
	DeleteImage(image);

	GetImageSize(fname, &W, &H);
	image = CreateImage(W, H);
	ReadImage(fname, image);
	image = Resize(80, image);	
	SaveImage("resizes", image);
	printf("Resizing small out tested!\n\n");
	DeleteImage(image);

	GetImageSize(fname, &W, &H);
	image = CreateImage(W, H);
	ReadImage(fname, image);
	Overlay("rowing", image, 150, 335);	
	SaveImage("overlay", image);
	printf("Overlay tested!\n\n");
	DeleteImage(image);
	image = NULL;
}

/* EOF Advanced.c */
