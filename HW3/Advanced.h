/*********************************************************************/ 
/* Advanced.h: program file for advanced DIP operations	             */ 
/*                                                                   */
/* 10/07/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment3 FAll2011             */
/*********************************************************************/
#ifndef ADVANCED_H
#define ADVANCED_H

#include "Constants.h"


/* aging the image */
void Aging(     unsigned char R[WIDTH][HEIGHT], 
                unsigned char G[WIDTH][HEIGHT], 
                unsigned char B[WIDTH][HEIGHT]);

/* Decipher the Watermark */
void WaterMarkDecipher(unsigned char R[WIDTH][HEIGHT], 
						unsigned char G[WIDTH][HEIGHT], 
						unsigned char B[WIDTH][HEIGHT]);

/* blur the image */
void Blur(  unsigned char R[WIDTH][HEIGHT], 
            unsigned char G[WIDTH][HEIGHT], 
            unsigned char B[WIDTH][HEIGHT]);


/* detect the edge of the image */
void EdgeDetection( double K, 
                    unsigned char R[WIDTH][HEIGHT], 
                    unsigned char G[WIDTH][HEIGHT], 
                    unsigned char B[WIDTH][HEIGHT]);

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

#endif
