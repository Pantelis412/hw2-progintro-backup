#include <stdio.h>
#include <stdlib.h>
#define MIN_HEADER_SIZE 54
#define WIDTH 18
#define HEIGHT 22
#define BITS_PER_PIXEL 28


void change_header(){
char header[MIN_HEADER_SIZE];
char *other_data;
char *pixel_data;
int read = fread(header, MIN_HEADER_SIZE,1,stdin);/*we use fread to read the header of a bmp file*/
//we check if fread has read the proper number of bytes from a proper bmp file
if(read != 1){
fprintf(stderr, "Could not read headers");
exit(1);
}
//check if the bmp file starts with the magic header ('B' 'M')
if(header[0] != 'B' || header[1] != 'M'){
fprintf(stderr, "Wrong input");
exit(1);
}
//we check if the bmp file uses 24 bits per pixel
int bits;
bits=header[BITS_PER_PIXEL] + header[BITS_PER_PIXEL+1]*256;
if(bits != 24){
fprintf(stderr, "Wrong bits per pixel size");
exit(1);
}
int width, height;/*we save width and height of the bmp file in these integer type variables*/
width  = *(unsigned int*)&header[WIDTH];
height = *(unsigned int*)(header+HEIGHT);
//We swap width and height in the header
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
char *other_data;
char *pixel_data;
change_header();
rotateBMP();
writeBMP();
}
