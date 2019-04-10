/*********************************************************************/ 
/* ImageList.h: header file for lists of Images				 		 */ 
/*                                                                   */
/* 10/27/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment5 FAll2011             */
/*********************************************************************/ 
#ifndef IMAGE_LIST_H
#define IMAGE_LIST_H

#include "Image.h"

typedef struct ImageList ILIST;
typedef struct ImageEntry IENTRY;

struct ImageList
{  int  Length;    /*Length of the list*/
   IENTRY *First;  /*pointer to the first entry*/
   IENTRY *Last;   /*pointer to the last entry*/
};

struct ImageEntry
{  IENTRY *Next;   /*pointer to the next entry*/
   IENTRY *Prev;   /*pointer to the previous entry*/
   ILIST  *List;   /*pointer to the list which this entry belongs to*/
   IMAGE  *Image;  /*pointer to the struct for an image*/
};

/* allocate a new image list */
ILIST *NewImageList(void);

/* delete a image list (and all entries) */
void DeleteImageList(ILIST *l);

/* insert a student into a list */
void AppendImage(ILIST *l, IMAGE *image);

/* reverse an image list */
void ReverseImageList(ILIST *l);

#endif /* IMAGE_LIST_H */

/* EOF */
