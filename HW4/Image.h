/*********************************************************************/ 
/* Image.h: header file for basic image manipulations				 */ 
/*                                                                   */
/* 10/20/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment4 FAll2011             */
/*********************************************************************/ 
#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
	unsigned int Width;		/* image width */
	unsigned int Height; 	/* image height */
	unsigned char *R;		/* pointer to the memory storing all the R intensity values */
	unsigned char *G;		/* pointer to the memory storing all the G intensity values */
	unsigned char *B;		/* pointer to the memory storing all the B intensity values */
}IMAGE;

/*Get the color intensity of the Red channel of pixel (x, y) in image */
unsigned char GetRPixel(IMAGE *image, unsigned int x,  unsigned int y);

/*Get the color intensity of the Green channel of pixel (x, y) in image */
unsigned char GetGPixel(IMAGE *image, unsigned int x,  unsigned int y);

/*Get the color intensity of the Blue channel of pixel (x, y) in image */
unsigned char GetBPixel(IMAGE *image, unsigned int x,  unsigned int y);

/*Set the color intensity of the Red channel of pixel (x, y) in image with value r*/
void SetRPixel(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r);

/*Set the color intensity of the Green channel of pixel (x, y) in image with value g */
void SetGPixel(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g);

/*Set the color intensity of the Blue channel of pixel (x, y) in image with value b */
void SetBPixel(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b);

/* allocate the memory spaces for the image              */
/* and the memory spaces for the color intensity values. */
/* return the pointer to the image                       */
IMAGE *CreateImage(unsigned int Width, unsigned int Height);

/*release the memory spaces for the pixel color intensity values */
/*release the memory spaces for the image                        */
void DeleteImage(IMAGE *image);

#endif
