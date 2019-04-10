/*********************************************************************/
/* DIPs.c: homework assignment #3, for EECS 22,  Fall 2011       	 */
/*                                                                   */
/* History:                                                          */
/* 10/07/11 Weiwei Chen  updated for EECS22 assignment3 FAll2011     */
/* 						 initial version                			 */
/*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Constants.h"
#include "Image.h"
#include "FileIO.h"
#include "DIPs.h"

/* reverse image color */
void
BlackNWhite(IMAGE *image)
{

	int             x, y;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	unsigned int tmp;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			tmp = (GetRPixel(image, x, y) + GetGPixel(image, x, y) + GetBPixel(image, x, y)) / 3;
			SetRPixel(image, x, y, tmp);
			SetGPixel(image, x, y, tmp);
			SetBPixel(image, x, y, tmp);
		}
}

/* reverse image color */
void Negative(IMAGE *image)
{
    int x, y;
	unsigned int WIDTH;
	unsigned int HEIGHT;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

    for( y=0; y<HEIGHT; y++ ){
        for( x=0; x<WIDTH; x++ )
          {
			SetRPixel(image, x, y, 255 - GetRPixel(image, x, y));
			SetGPixel(image, x, y, 255 - GetGPixel(image, x, y));
			SetBPixel(image, x, y, 255 - GetBPixel(image, x, y));
          }
	}
}


/* flip image horizontally */
void
HFlip(IMAGE *image)
{
	int             x, y;
	unsigned char   r, g, b;
	unsigned int WIDTH;
	unsigned int HEIGHT;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH / 2; x++) {
			r = GetRPixel(image, WIDTH - 1 - x, y);
			g = GetGPixel(image, WIDTH - 1 - x, y);
			b = GetBPixel(image, WIDTH - 1 - x, y);

			SetRPixel(image, WIDTH - 1 - x, y, GetRPixel(image, x, y));
			SetGPixel(image, WIDTH - 1 - x, y, GetGPixel(image, x, y));
			SetBPixel(image, WIDTH - 1 - x, y, GetBPixel(image, x, y));

			SetRPixel(image, x, y, r);
			SetGPixel(image, x, y, g);
			SetBPixel(image, x, y, b);
		}
	}
}

/* mirror image horizontally */
void
HMirror(IMAGE *image)
{
	int             x, y;
	unsigned int WIDTH;
	unsigned int HEIGHT;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH / 2; x++) {
			SetRPixel(image, WIDTH - 1 - x, y, GetRPixel(image, x, y));
			SetGPixel(image, WIDTH - 1 - x, y, GetGPixel(image, x, y));
			SetBPixel(image, WIDTH - 1 - x, y, GetBPixel(image, x, y));
		}
	}
}

/* flip image vertically */
void
VFlip(IMAGE *image)
{
	int             x, y;
	unsigned char   r, g, b;
    unsigned int WIDTH;
	unsigned int HEIGHT;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	for (y = 0; y < HEIGHT/2; y++) {
		for (x = 0; x < WIDTH; x++) {

			r = GetRPixel(image, x, HEIGHT - 1 - y);
			g = GetGPixel(image, x, HEIGHT - 1 - y);
			b = GetBPixel(image, x, HEIGHT - 1 - y);

			SetRPixel(image, x, HEIGHT - 1 - y, GetRPixel(image, x, y));
			SetGPixel(image, x, HEIGHT - 1 - y, GetGPixel(image, x, y));
			SetBPixel(image, x, HEIGHT - 1 - y, GetBPixel(image, x, y));

			SetRPixel(image, x, y, r);
			SetGPixel(image, x, y, g);
			SetBPixel(image, x, y, b);
		}
	}
}

/* mirror image vertically */
void
VMirror(IMAGE *image)
{
	int             x, y;
	unsigned int WIDTH;
	unsigned int HEIGHT;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;
    
	for (y = 0; y < HEIGHT / 2; y++) {
		for (x = 0; x < WIDTH; x++) {
			SetRPixel(image, x, HEIGHT - 1 - y, GetRPixel(image, x, y));
			SetGPixel(image, x, HEIGHT - 1 - y, GetGPixel(image, x, y));
			SetBPixel(image, x, HEIGHT - 1 - y, GetBPixel(image, x, y));
		}
	}
}

/* EOF DIPs.c */
