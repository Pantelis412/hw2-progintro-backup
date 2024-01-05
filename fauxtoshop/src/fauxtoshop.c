#include <stdio.h>
#include <stdlib.h>
#define MIN_HEADER_SIZE 54
#define WIDTH 18
#define HEIGHT 22
#define BITS_PER_PIXEL 28


void readBMP(){/**/
char header[MIN_HEADER_SIZE];
char *other_data;
char *pixel_data;
int read = fread(header, MIN_HEADER_SIZE,1,stdin);/*we use fread to read the header of a bmp file*/
if(read != 1){/*we check if fread has read the proper number of bytes from a proper bmp file*/
fprintf(stderr, "Could not read headers");/*if not this message is printed and the program is terminated*/
exit(1);
}
if(header[0] != 'B' || header[1] != 'M'){/*check if the bmp file starts with the magic header ('B' 'M')*/
printf("Wrong input");/*if not this message is printed and the program is terminated*/
exit(1);
}
int width, height;/*we save width and height of the bmp file it these integer type variables*/
width  = *(unsigned int*)&header[WIDTH];
height = *(unsigned int*)(header+HEIGHT);
//We swap with and heigh in the header
*(unsigned int*)&header[WIDTH]=height;
*(unsigned int*)&header[HEIGHT]=width;
//we push those changes in stdout
fwrite(header, MIN_HEADER_SIZE,1,stdout);
}

void rotateBMP(){

}

void writeBMP(){

}
int main(){
char header[MIN_HEADER_SIZE];
char *other_data;
char *pixel_data;
readBMP();
rotateBMP();
writeBMP();
}
