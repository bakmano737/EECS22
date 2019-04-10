#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Movie.h"
#include "Image.h"
#include "ImageList.h"


/* allocate the memory spaces for the movie              */
/* and the memory spaces for the frame list. 			 */
/* return the pointer to the movie                       */
MOVIE *CreateMovie(unsigned int nFrames, unsigned int W, unsigned int H)
{
	MOVIE *movie = (MOVIE *)malloc(sizeof(MOVIE));

	movie->NumFrames 	= nFrames;
	movie->Width		= W;
	movie->Height		= H;

	movie->Frames = NewImageList();

	return movie;
}

/*release the memory spaces for the frames and the frame list. */
/*release the memory spaces for the movie.                     */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);

	DeleteImageList(movie->Frames);
	
	free(movie);
}

/* convert the YUV image into the RGB image */
void YUV2RGBImage(IMAGE *YUVImage, IMAGE *RGBImage)
{
	int x, y;
	int C, D, E, R, G, B;

	assert(YUVImage);
	assert(RGBImage);
	assert(YUVImage->Width == RGBImage->Width);
	assert(YUVImage->Height == RGBImage->Height);

	for(x = 0; x < YUVImage->Width; x ++){
		for(y = 0; y < YUVImage->Height; y ++){
			C = GetYPixel(YUVImage, x, y) - 16;
			D = GetUPixel(YUVImage, x, y) - 128;
			E = GetVPixel(YUVImage, x, y) - 128;

			R = (298 * C + 409 * E + 128) >> 8;
			G = (298 * C - 100 * D - 208 * E + 128) >> 8;
			B = (298 * C + 516 * D + 128) >> 8;

			R = R > 0 ? R : 0;
			G = G > 0 ? G : 0;
			B = B > 0 ? B : 0;

			R = R < 255 ? R : 255;
			G = G < 255 ? G : 255;
			B = B < 255 ? B : 255;

			SetRPixel(RGBImage, x, y, (unsigned char)R);
			SetGPixel(RGBImage, x, y, (unsigned char)G);
			SetBPixel(RGBImage, x, y, (unsigned char)B);
		}
	}
}

/* convert the RGB image into the YUV image */
void RGB2YUVImage(IMAGE *RGBImage, IMAGE *YUVImage)
{
	int x, y;
	int R, G, B, Y, U, V;

	assert(YUVImage);
	assert(RGBImage);
	assert(YUVImage->Width == RGBImage->Width);
	assert(YUVImage->Height == RGBImage->Height);

	for(x = 0; x < YUVImage->Width; x ++){
		for(y = 0; y < YUVImage->Height; y ++){
			R = GetRPixel(RGBImage, x, y);
			G = GetGPixel(RGBImage, x, y);
			B = GetBPixel(RGBImage, x, y);

			Y = (( 66 * R + 129 * G + 25 * B + 128) >> 8) + 16;

			Y = Y > 0 ? Y : 0;
			Y = Y < 255 ? Y : 255;

			SetYPixel(YUVImage, x, y, (unsigned char)Y);
		}
	}

	for(x = 0; x < YUVImage->Width; x += 2){
		for(y = 0; y < YUVImage->Height; y += 2){
			R = GetRPixel(RGBImage, x, y);
			G = GetGPixel(RGBImage, x, y);
			B = GetBPixel(RGBImage, x, y);

			U = (( (-38) * R - 74 * G + 112 * B + 128) >> 8) + 128;
			V = (( 112 * R - 94 * G - 18 * B + 128) >> 8) + 128;

			U = U > 0 ? U : 0;
			U = U < 255 ? U : 255;
			V = V > 0 ? V : 0;
			V = V < 255 ? V : 255;

			SetUPixel(YUVImage, x, y, (unsigned char)U);
			SetUPixel(YUVImage, x + 1, y, (unsigned char)U);
			SetUPixel(YUVImage, x, y + 1, (unsigned char)U);
			SetUPixel(YUVImage, x + 1, y + 1, (unsigned char)U);

			SetVPixel(YUVImage, x, y, (unsigned char)V);
			SetVPixel(YUVImage, x + 1, y, (unsigned char)V);
			SetVPixel(YUVImage, x, y + 1, (unsigned char)V);
			SetVPixel(YUVImage, x + 1, y + 1, (unsigned char)V);
		}
	}
}


