/*********************************************************************/ 
/* FileIO.h: header file for I/O module	                             */ 
/*                                                                   */
/* 10/07/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment3 FAll2011             */
/*********************************************************************/ 
#ifndef FILE_IO_H
#define FILE_IO_H

#include "Constants.h"


/* read image from a file */
int ReadImage(  char fname[SLEN], 
                unsigned char R[WIDTH][HEIGHT], 
                unsigned char G[WIDTH][HEIGHT], 
                unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(  char fname[SLEN], 
                unsigned char R[WIDTH][HEIGHT], 
                unsigned char G[WIDTH][HEIGHT], 
                unsigned char B[WIDTH][HEIGHT]);

/* read Overlay image from a file */
int ReadImageW( char fname[SLEN], 
                unsigned char R[WIDTH2][HEIGHT2], 
                unsigned char G[WIDTH2][HEIGHT2], 
                unsigned char B[WIDTH2][HEIGHT2]);

#endif
