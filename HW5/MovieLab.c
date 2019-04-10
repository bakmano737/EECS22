/*********************************************************************/
/* MovieLab.c: homework assignment #5, for EECS 22,  Fall 2011       */
/*                                                                   */
/* History:                                                          */
/* 10/30/11 Weiwei Chen  updated for EECS22 assignment5 FAll2011     */
/* 10/30/11 Weiwei Chen	: initial template version                   */
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Movie.h"
#include "DIPs.h"

/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/*read one frame from the movie */
int ReadOneFrame(const char* fname, int nFrame, unsigned int W, unsigned H, IMAGE *frame);

/*read the movie frames from the input file */
int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned H, MOVIE *movie);

/* Print the command line parameter usage of the program*/
void PrintUsage();

/* type define the function pointer to the DIP function  */
typedef void MOP_F(IMAGE *image);

/* the function for perform DIP operations on the movie*/
void Movie_DIP_Operation(MOVIE *movie, MOP_F *MovieOP);

int main(int argc, char *argv[])
{
	int x = 0, n = 0, h = 0, v = 0, bw = 0, r = 0;
	char *fin = NULL, *fout = NULL;
	unsigned int Width = 0, Height = 0, NumFrames = 0;
	MOVIE *movie;

 /*entering while loop to check options entered*/
    while(x < argc)
	{
		if(0 == strcmp(&argv[x][0], "-i")) 
		{
			if(x < argc - 1)
			{
				fin = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				strcpy(fin, argv[x + 1]);
				strcat( fin, ".yuv");
			}/*fi*/
			else
			{
				printf("Missing argument for input name!");
				free(fin);
				free(fout);
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/
		if(0 == strcmp(&argv[x][0], "-o")) 
		{
			if(x < argc - 1)
			{
				fout = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				strcpy(fout, argv[x + 1]);
				strcat( fout, ".yuv");
			}/*fi*/
			else
			{
				printf("Missing argument for output name!");
				free(fin);
				free(fout);
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/
		if(0 == strcmp(argv[x], "-s")) 
		{
			if(argc < (x + 1) || (sscanf(argv[x + 1], "%dx%d", &Width, &Height) != 2) )
			{
				printf("No resolution information provided by -s parameter.\n");
				PrintUsage();
				free(fin);
				free(fout);
				return 5;
			}
			else if(Width == 0 || Height == 0){
				printf("Resolution information provided by -s parameter are not correct.\n");
				PrintUsage();
			}
			x += 2;
			continue;
		}/*fi*/
		if(0 == strcmp(argv[x], "-f")) 
		{
			if(argc < (x + 1) || (sscanf(argv[x + 1], "%d", &NumFrames) != 1) )
			{
				printf("No frame number information provided by -f parameter.\n");
				PrintUsage();
				free(fin);
				free(fout);
				return 5;
			}
			else if(NumFrames == 0){
				printf("Frame number information provided by -f parameter is not correct.\n");
				PrintUsage();
			}
			x += 2;
			continue;
		}/*fi*/
		if(0 == strcmp(&argv[x][0], "-n")) 
		{
			n = 1;
			x++;
			continue;
		}/*fi*/
		if(0 == strcmp(&argv[x][0], "-hf")) 
		{
			h = 1;
			x++;
			continue;
		}/*fi*/
		if(0 == strcmp(&argv[x][0], "-vf")) 
		{
			v = 1;
			x++;
			continue;
		}/*fi*/
		if(0 == strcmp(&argv[x][0], "-bw")) 
		{
			bw = 1;
			x++;
			continue;
		}/*fi*/
		if(0 == strcmp(&argv[x][0], "-rvs")) 
		{
			r = 1;
			x++;
			continue;
		}/*fi*/
		if(0 == strcmp(&argv[x][0], "-h")) 
		{ 
			PrintUsage();
			free(fin);
			free(fout);
			return 0;
		}/*fi*/
		x++;
	}/*elihw*/

	if(!fin){
		printf("Missing argument for input name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}
	
	if(!fout){
		printf("Missing argument for output name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}

	if(!fin){
		fin = (char *)malloc(sizeof(char) * (strlen(&argv[1][0]) + strlen(".yuv") + 1));
		strcpy(fin, argv[1]);
		strcat( fin, ".yuv");
	}
	
	if(!fout){
		fout = (char *)malloc(sizeof(char) * (strlen(&argv[1][0]) + strlen(".yuv") + 1));
		strcpy(fout, argv[1]);
		strcat( fout, ".yuv");
	}

	if(Width == 0 || Height == 0){
		printf("No resolution information provided by -s parameter.\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}

	if(NumFrames == 0){
		printf("No frame number information provided by -f parameter.\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}

		
	movie = CreateMovie(NumFrames, Width, Height);
	 
	ReadMovie(fin, NumFrames, Width, Height, movie);

	if(bw == 1){
		Movie_DIP_Operation(movie, BlackNWhite);
		printf("Operation BlackNWhite is done! \n");
	}
	else if(n == 1){
		Movie_DIP_Operation(movie, Negative);
		printf("Operation Negative is done! \n");
	}
	else if(h == 1){
		Movie_DIP_Operation(movie, HFlip);
		printf("Operation HFlip is done! \n");
	}
	else if(v == 1){
		Movie_DIP_Operation(movie, VFlip);
		printf("Operation VFlip is done! \n");
	}
	else if(r == 1){
		ReverseImageList(movie->Frames);
		printf("Operation ReverseMovie is done! \n");
	}


	SaveMovie(fout, movie);

	DeleteMovie(movie);
	movie = NULL;

	free(fin);
	free(fout);

	return 0;
}


void Movie_DIP_Operation(MOVIE *movie, MOP_F *MovieOP)
{
	IMAGE *rgbimage;
	IENTRY *curr;

	rgbimage = CreateImage(movie->Width, movie->Height);
	curr = movie->Frames->First;	

	while(curr){
		YUV2RGBImage(curr->Image, rgbimage);
		MovieOP(rgbimage);
		RGB2YUVImage(rgbimage, curr->Image);
		curr = curr->Next;
	}

	DeleteImage(rgbimage);
}

void PrintUsage()
{
	printf("\nFormat on command line is:\n"
	"MovieLab -i input_file_name -o output_file_name -f number_of_frames -s widthxheight -h|-bw|-n|-hf|-vf|-rvs\n"
	"-i\t\tto provide the input file name\n"
	"-o\t\tto provide the  output file name\n"
	"-f\t\tto determine how many frames desired in the input stream\n"
	"-s\t\tto resolution of the input stream (widthxheight)\n"
	"-bw\t\tto activate the conversion to black and white\n"
	"-n\t\tto activate the conversion to negative\n"
	"-hf\t\tto activate horizontal flip\n"
	"-vf\t\tto activate vertical flip\n"
	"-rvs\t\tto reverse the frame order of the input stream\n"
	"-h\t\tto show this usage information\n"
	);
}

int ReadOneFrame(const char *fname, int nFrame, unsigned int W, unsigned H, IMAGE *image)
{
   /*defining local variables*/
   FILE *file;

   unsigned int x, y;
   unsigned char ch;
   
   /*checking error*/
   assert(fname);
   assert(nFrame >= 0);
   assert(image);
   assert(image->Width == W && image->Height == H);

   /*opening file stream*/
   if(!(file = fopen(fname, "r"))){
      return 1;
   }

   /*find desired frame*/
   fseek(file, 1.5 * nFrame * W * H, SEEK_SET);

   for(y = 0; y < H; y ++){
      for(x = 0; x < W; x ++){
		ch = fgetc(file);
		SetYPixel(image, x, y, ch);
   	  }/*rof*/
   }
	

   for(y = 0; y < H ; y += 2){
	  for(x = 0; x < W ; x += 2){
         ch = fgetc(file);
		 SetUPixel(image, x, y, ch);
		 SetUPixel(image, x + 1, y, ch);
		 SetUPixel(image, x, y + 1, ch);
		 SetUPixel(image, x + 1, y + 1, ch);
      }
   }

   for(y = 0; y < H ; y += 2){
	  for(x = 0; x < W ; x += 2){
         ch = fgetc(file);
		 SetVPixel(image, x, y, ch);
		 SetVPixel(image, x + 1, y, ch);
		 SetVPixel(image, x, y + 1, ch);
		 SetVPixel(image, x + 1, y + 1, ch);
      }
   }
	
   /*checking for error*/
   if (ferror(file))
   {
	  printf("\nFile error while reading from file!\n");
	  return 2;
   }/*fi*/ 

   /*closing stream and terminating*/
   fclose(file);
   file = NULL;
   return 0;
}

/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	int x, y;
	FILE *file;
	IENTRY *currFrame;

   /*opening file stream*/
   if(!(file = fopen(fname, "w"))){
      return 1;
   }
	
   currFrame = movie->Frames->First;
   while(currFrame){
		for(y = 0; y < movie->Height; y ++){ 
			for(x = 0; x < movie->Width; x ++){
				fputc(GetYPixel(currFrame->Image, x, y), file);
			}
		}
		for(y = 0; y < movie->Height; y += 2){ 
			for(x = 0; x < movie->Width; x += 2){
				fputc(GetUPixel(currFrame->Image, x, y), file);
			}
		}
		for(y = 0; y < movie->Height; y += 2){ 
			for(x = 0; x < movie->Width; x += 2){
				fputc(GetVPixel(currFrame->Image, x, y), file);
			}
		}
		currFrame = currFrame->Next;
   }

   fclose(file);
   file = NULL;

   printf("The movie file %s has been written successfully! \n", fname);
   return 0;
}

/*read the movie frames from the input file */
int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned H, MOVIE *movie)
{
	int i;
	IMAGE *image;

	for(i = 0; i < nFrame; i ++){
		image = CreateImage(W, H);
		if(!ReadOneFrame(fname, i, W, H, image)){
			AppendImage(movie->Frames, image);
		}
		else
			return 1;
	}
	printf("The movie file %s has been read successfully! \n", fname);
	return 0;
}

