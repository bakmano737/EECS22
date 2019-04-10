/*********************************************************************/
/* DIPs.h: homework assignment #3, for EECS 22,  Fall 2011       	 */
/*                                                                   */
/* History:                                                          */
/* 10/07/11 Weiwei Chen  updated for EECS22 assignment3 FAll2011     */
/* 						 initial version                			 */
/*********************************************************************/
#ifndef DIPS_H#define DIPS_H

#include "Constants.h"
#include "Image.h"

/* change color image to black & white */
void BlackNWhite(IMAGE *image);

/* reverse image color */
void Negative(IMAGE *image);

/* flip image horizontally */
void HFlip(IMAGE *image);

/* mirror image horizontally */
void HMirror(IMAGE *image);

/* flip image vertically */
void VFlip(IMAGE *image);

/* mirror image vertically */
void VMirror(IMAGE *image);

#endif
