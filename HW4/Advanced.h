/*********************************************************************/ 
/* Advanced.h: program file for advanced DIP operations	             */ 
/*                                                                   */
/* 10/19/11 Weiwei Chen: Add Overlay, Rotate, Resize					 */
/*						 for EECS22 assignment4 Fall2011			 */
/* 10/07/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment3 FAll2011             */
/*********************************************************************/
#ifndef ADVANCED_H#define ADVANCED_H
#include "Constants.h"
#include "Image.h"

/* aging the image */
void Aging(IMAGE *image);

/* Decipher the Watermark */
/*void WaterMarkDecipher(unsigned int WIDTH, 
			unsigned int HEIGHT, 
			unsigned char *R, 
			unsigned char *G, 
			unsigned char *B);
*/

/* blur the image */
void Blur(IMAGE *image);

/* detect the edge of the image */
void EdgeDetection( double K, IMAGE *image);

/*Rotate 90 degrees clockwise*/
IMAGE *Rotate(IMAGE *image);

/*Resize*/
IMAGE *Resize(	unsigned int percentage, IMAGE *image);

/*Overaly a small image onto the original big image*/
void Overlay(char f2name[SLEN],IMAGE *image,
			 unsigned int x_offset, unsigned int y_offset);

/* Test all functions */
void AutoTest(const char *fname);

#endif
