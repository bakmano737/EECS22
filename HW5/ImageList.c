/*********************************************************************/ 
/* ImageList.c: source code file for lists of Images				 */ 
/*                                                                   */
/* 10/27/11 Weiwei Chen: initial solution version                    */
/*                       for EECS22 assignment5 FAll2011             */
/*********************************************************************/ 

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* allocate a new image list */
ILIST *NewImageList(void)
{
	ILIST *newlist = (ILIST *)malloc(sizeof(ILIST));

	newlist->First = NULL;
	newlist->Last = NULL;
	newlist->Length = 0;

	return newlist;
}

/* delete an image list (and all entries) */
void DeleteImageList(ILIST *l)
{
	IENTRY *curr, *succ;

	assert(l);
	curr = l->First;
	while(curr){
		succ = curr->Next;
		assert(curr->List == l);
		DeleteImage(curr->Image);
		curr->Image = NULL;
		free(curr);
		curr = succ;
	}

	free(l);
}

/* insert an image into a list */
void AppendImage(ILIST *l, IMAGE *image)
{
	IENTRY *newentry;

	assert(l);

	newentry 		= (IENTRY *)malloc(sizeof(IENTRY));
	newentry->Prev 	= NULL;
	newentry->Next 	= NULL;
	newentry->List 	= l;
	newentry->Image = image;
	
	if(!l->First){
		l->First = l->Last = newentry;
	}
	else{
		l->Last->Next = newentry;
		newentry->Prev = l->Last;
		l->Last = newentry;
	}
	l->Length ++;
}

/* reverse an image list */
void ReverseImageList(ILIST *l)
{
	IENTRY *curr, *currTail, *succ;

	if(l->First){
		l->Last = l->First;
		currTail = l->First;
		curr = currTail->Next;
		currTail->Next = NULL;

		while(curr){
			succ = curr->Next;
			currTail->Prev = curr;
			curr->Next = currTail;
			currTail = curr;
			curr = succ;
		}
		
		currTail->Prev = NULL;
		l->First = currTail;
	}

}
