#####################################################
# Makefile: Makefile for Assignment3 EECS22 Fall2011
#
# 10/10/11 Weiwei Chen: initial solution version                  
#
#####################################################

# design names
DESIGN = PhotoLab Test
IMAGES = bw.ppm negative.ppm hflip.ppm hmirror.ppm vflip.ppm vmirror.ppm \
		 aging.ppm blur.ppm edge.ppm \
		 overlay.ppm resizes.ppm resizeb.ppm rotate.ppm
CC = gcc
OPT = -ansi -Wall
#DEBUG = -DDEBUG

all: PhotoLab Test

#target to generate PhotoLab.o
PhotoLab.o: PhotoLab.c
	$(CC) -c PhotoLab.c -o PhotoLab.o $(OPT)

#target to generate DIPs.o
DIPs.o: DIPs.h DIPs.c
	$(CC) -c DIPs.c -o DIPs.o $(OPT)

#target to generate Advanced.o
Advanced.o: Advanced.h Advanced.c
	$(CC) -c Advanced.c -o Advanced.o $(OPT)

#target to generate Image.o
Image.o: Image.h Image.c
	$(CC) -c Image.c -o Image.o $(OPT)

#target to generate PhotoLab
PhotoLab: PhotoLab.o DIPs.o Advanced.o Image.o
	$(CC) PhotoLab.o DIPs.o Advanced.o Image.o -L. -lfileio -o PhotoLab $(OPT)

#target to generate Test.o
Test.o: Test.c
	$(CC) -c Test.c -o Test.o $(OPT)

#target to generate Test
Test: Test.o DIPs.o Advanced.o Image.o
	$(CC) Test.o DIPs.o Advanced.o Image.o -L. $(DEBUG) -lfileio -o Test $(OPT)

memcheck: Test
	valgrind --leak-check=full ./Test
	
#target to clean the directory
clean:
	rm -f *.o *.jpg $(DESIGN) $(IMAGES)
    
