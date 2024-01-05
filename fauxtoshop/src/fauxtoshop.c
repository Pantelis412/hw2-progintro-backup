#include <stdio.h>
#include <stdlib.h>
#define MIN_HEADER_SIZE 54
#define WIDTH 18
#define HEIGHT 22

void readBMP(){
char header[MIN_HEADER_SIZE];
char *other_data;
char *pixel_data;
int read = fread(header, MIN_HEADER_SIZE,1,stdin);
if(read != 1){
fprintf(stderr, "Could not read headers");
exit(1);

printf("First char: %c\n", header[0]);
printf("Second char: %c\n", header[1]);

if(header[0] != 'B' || header[1] != 'M'){
printf("Wrong input");
exit(1);
}
int width, height;
width  = *(unsigned int*)(header+WIDTH);
height = *(unsigned int*)(header+HEIGHT);


}
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
