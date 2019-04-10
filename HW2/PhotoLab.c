/*********************************************************************/
/* PhotoLab.c: homework assignment #2, for EECS 22,  Fall 2011       */
/*                                                                   */
/* History:                                                          */
/* 09/27/11 Weiwei Chen  updated for EECS22 assignment2 Fall2011     */
/* 11/07/10 Xu Han 		 ColorCorrect() added;bug fix in             */
/*                               pnmtojpeg.tcsh to gen. index.html   */
/* 11/11/09 Yitao Guo 		 updated for Fall 2009                   */
/* 11/10/08 Bin Zhang 		 updated for Fall 2008                   */
/* 11/16/07 Gunar Schirner   use script in ~eecs10/bin for jpg conv. */
/* 11/14/07 Yue Zhang &                                              */
/* Suman Chitturi   updated for Fall 2007                            */
/* 11/29/06 Gunar Schirner   Minor bug fix in Grey()                 */
/* 11/02/06 Zhihe Zhang      New functions added; old functions      */
/* and program modified.                                             */
/* 11/10/05 Liang Zhang      modify WritePhotoPPM, add filter and    */
/* paint_area functions                                              */
/* 11/10/05 Donghua Deng     add Overlay and ShiftOverlay functions  */
/* 12/05/04 Liang Zhang:     solution                                */
/* 11/11/04 Rainer Doemer:   update for EECS 10 formatting style     */
/* 11/10/04 Rustam Sengupta: initial template version                */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*** global definitions ***/
#define WIDTH  640		/* Image width */
#define HEIGHT 425		/* image height */
#define SLEN    80		/* maximum length of file names */
/*** function declarations ***/

/* print a menu */
void            PrintMenu();

/* read image from a file */
int             ReadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int             SaveImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* change color image to black & white */
void            BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* reverse image color */
void            Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* flip image horizontally */
void            HFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* mirror image horizontally */
void            HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* flip image vertically */
void            VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* mirror image vertically */
void            VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* Test all functions */
void            AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

int             main()
{
	/*
	 * Two dimensional arrays to hold the current image data. One array
	 * for each color component
	 */
	unsigned char   R[WIDTH][HEIGHT];
	unsigned char   G[WIDTH][HEIGHT];
	unsigned char   B[WIDTH][HEIGHT];

	char            fname[SLEN];
	int             choice;

	PrintMenu();
	printf("please make your choice: ");
	scanf("%d", &choice);

	while (choice != 13) {
		switch (choice) {
		case 1:
			printf("Please input the file name to load: ");
			scanf("%s", fname);
			ReadImage(fname, R, G, B);
			break;
		case 2:
			printf("Please input the file name to save: ");
			scanf("%s", fname);
			SaveImage(fname, R, G, B);
			break;
		case 3:
			BlackNWhite(R, G, B);
	                printf("\"Black & White\" operation is done!\n");
			break;
		case 4:
                        Negative(R,G,B);
			break;
		case 5:
			HFlip(R, G, B);
			printf("\"HFlip\" operation is done!\n");
			break;
		case 6:
			HMirror(R, G, B);
			printf("\"HMirror\" operation is done!\n");
			break;
        case 7:
            VFlip(R, G, B);
            printf("\"VFlip\" operation is done!\n");
            break;
        case 8:
            VMirror(R, G, B);
            printf("\"VMirror\" operation is done!\n");
            break;
        case 9:
                        AutoTest(R, G, B);
			break;
		case 10:
			break;
		default:
			printf("Invalid selection!\n");
			break;
		}

		PrintMenu();
		printf("please make your choice: ");
		scanf("%d", &choice);
	}

	return 0;
}

int
ReadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE           *File;
	char            Type[SLEN];
	int             Width, Height, MaxValue;
	int             x, y;
	char            ftype[] = ".ppm";
        char            fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/

        strcpy(fname_tmp, fname);
	strcat(fname_tmp, ftype);

	File = fopen(fname_tmp, "r");
	if (!File) {
		printf("\nCannot open file \"%s\" for reading!\n", fname);
		return 1;
	}
	fscanf(File, "%79s", Type);
	if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
		printf("\nUnsupported file format!\n");
		return 2;
	}
	fscanf(File, "%d", &Width);
	if (Width != WIDTH) {
		printf("\nUnsupported image width %d!\n", Width);
		return 3;
	}
	fscanf(File, "%d", &Height);
	if (Height != HEIGHT) {
		printf("\nUnsupported image height %d!\n", Height);
		return 4;
	}
	fscanf(File, "%d", &MaxValue);
	if (MaxValue != 255) {
		printf("\nUnsupported image maximum value %d!\n", MaxValue);
		return 5;
	}
	if ('\n' != fgetc(File)) {
		printf("\nCarriage return expected!\n");
		return 6;
	}
	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			R[x][y] = fgetc(File);
			G[x][y] = fgetc(File);
			B[x][y] = fgetc(File);
		}
	if (ferror(File)) {
		printf("\nFile error while reading from file!\n");
		return 7;
	}
	printf("%s was read successfully!\n", fname_tmp);
	fclose(File);
	return 0;
}

int
SaveImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE           *File;
	int             x, y;
	char            SysCmd[SLEN * 5];

	char            ftype[] = ".ppm";
	char            fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
        char            fname_tmp2[SLEN];

	strcpy(fname_tmp, fname);
        strcpy(fname_tmp2, fname);
	strcat(fname_tmp2, ftype);

	File = fopen(fname_tmp2, "w");
	if (!File) {
		printf("\nCannot open file \"%s\" for writing!\n", fname);
		return 1;
	}
	fprintf(File, "P6\n");
	fprintf(File, "%d %d\n", WIDTH, HEIGHT);
	fprintf(File, "255\n");

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			fputc(R[x][y], File);
			fputc(G[x][y], File);
			fputc(B[x][y], File);
		}

	if (ferror(File)) {
		printf("\nFile error while writing to file!\n");
		return 2;
	}
	fclose(File);
	printf("%s was saved successfully. \n", fname_tmp2);

	/*
	 * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
	 * and make it world readable
	 */
	sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg.tcsh %s",
		fname_tmp2);
	if (system(SysCmd) != 0) {
		printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
		return 3;
	}
	printf("%s.jpg was stored for viewing. \n", fname_tmp);

	return (0);
}

/* print a menu */
void
PrintMenu()
{
	printf("\n--------------------------------\n");
	printf(" 1:  Load a PPM image\n");
	printf(" 2:  Save an image in PPM and JPEG format\n");
	printf(" 3:  Change a color image to black and white\n");
	printf(" 4:  Make a negative of an image\n");
	printf(" 5:  Flip an image horizontally\n");
	printf(" 6:  Mirror an image horizontally\n");
    printf(" 7:  Flip an image vertically (5 bonus points)\n");
	printf(" 8:  Mirror an image vertically (5 bonus points)\n");
    printf(" 9:  Test all functions\n");  
	printf("10:  Exit\n");
}

/* reverse image color */
void
BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int             x, y;

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			R[x][y] = G[x][y] = B[x][y]
				= (R[x][y] + G[x][y] + B[x][y]) / 3;
		}
}

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y;

    for( y=0; y<HEIGHT; y++ )
        for( x=0; x<WIDTH; x++ )
          {
            R[x][y]=255-R[x][y];
            G[x][y]=255-G[x][y];
            B[x][y]=255-B[x][y];
          }
    printf( "\"Negative\" operation is done!\n" );
}


/* flip image horizontally */
void
HFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int             x, y;
	unsigned char   r, g, b;

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH / 2; x++) {
			r = R[WIDTH - 1 - x][y];
			g = G[WIDTH - 1 - x][y];
			b = B[WIDTH - 1 - x][y];

			R[WIDTH - 1 - x][y] = R[x][y];
			G[WIDTH - 1 - x][y] = G[x][y];
			B[WIDTH - 1 - x][y] = B[x][y];

			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	}
}

/* mirror image horizontally */
void
HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int             x, y;

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH / 2; x++) {
			R[WIDTH - 1 - x][y] = R[x][y] ;
			G[WIDTH - 1 - x][y] = G[x][y] ;
			B[WIDTH - 1 - x][y] = B[x][y] ;
		}
	}
}

/* flip image vertically */
void
VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int             x, y;
	unsigned char   r, g, b;
    
	for (y = 0; y < HEIGHT/2; y++) {
		for (x = 0; x < WIDTH; x++) {
			r = R[x][HEIGHT - 1 - y];
			g = G[x][HEIGHT - 1 - y];
			b = B[x][HEIGHT - 1 - y];
            
			R[x][HEIGHT - 1 - y] = R[x][y];
			G[x][HEIGHT - 1 - y] = G[x][y];
			B[x][HEIGHT - 1 - y] = B[x][y];
            
			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	}
}

/* mirror image vertically */
void
VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int             x, y;
    
	for (y = 0; y < HEIGHT / 2; y++) {
		for (x = 0; x < WIDTH; x++) {
			R[x][HEIGHT - 1 - y] = R[x][y] ;
			G[x][HEIGHT - 1 - y] = G[x][y] ;
			B[x][HEIGHT - 1 - y] = B[x][y] ;
		}
	}
}

/* auto test*/
void
AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	char            fname[SLEN] = "sailing";
    char            sname[SLEN];

	ReadImage(fname, R, G, B);
	BlackNWhite(R, G, B);
    strcpy(sname, "bw");
	SaveImage(sname, R, G, B);
	printf("Black & White tested!\n\n");

	ReadImage(fname, R, G, B);
	Negative(R, G, B);
        strcpy(sname, "negative");
	SaveImage(sname, R, G, B);
	printf("Negative tested!\n\n");

	ReadImage(fname, R, G, B);
	HFlip(R, G, B);
    strcpy(sname, "hflip");
	SaveImage(sname, R, G, B);
	printf("HFlip tested!\n\n");

	ReadImage(fname, R, G, B);
	HMirror(R, G, B);
        strcpy(sname, "hmirror");
	SaveImage(sname, R, G, B);
	printf("HMirror tested!\n\n");
    
    ReadImage(fname, R, G, B);
	VFlip(R, G, B);
    strcpy(sname, "vflip");
	SaveImage(sname, R, G, B);
	printf("VFlip tested!\n\n");
    
	ReadImage(fname, R, G, B);
	VMirror(R, G, B);
    strcpy(sname, "vmirror");
	SaveImage(sname, R, G, B);
	printf("VMirror tested!\n\n");

}

