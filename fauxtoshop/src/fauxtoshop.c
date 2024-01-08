#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN_HEADER_SIZE 54
#define WIDTH 18
#define HEIGHT 22
#define BITS_PER_PIXEL 28
#define OFFSET 10
#define FILE_SIZE 2
#define IMAGE_SIZE 34

int offset;
int o_padding;
int n_padding;
int o_width;
int o_height;

void change_header(){
char header[MIN_HEADER_SIZE];
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
o_width=width;
height = *(unsigned int*)(header+HEIGHT);
o_height=height;
//We swap width and height in the header
*(unsigned int*)&header[WIDTH]=height;
*(unsigned int*)&header[HEIGHT]=width;
offset=header[OFFSET] + header[OFFSET+1]*256 + header[OFFSET+2]*256*256+ header[OFFSET+3]*256*256*256;
//we calculate the new and the old padding based on the width and heigth of the header and we change the information about he file size and the image size of the header
int old_padding;
if (((3*width)%4)==0) old_padding=0;
else old_padding=4-((3*width)%4);
o_padding=old_padding;
old_padding*=height;
int new_padding;
if(((3*height)%4)==0) new_padding=0;
else new_padding=4-((3*height)%4);
n_padding=new_padding;
new_padding*=width;
*(unsigned int*)&header[FILE_SIZE]=*(unsigned int*)&header[FILE_SIZE] - old_padding + new_padding;
*(unsigned int*)&header[IMAGE_SIZE]=*(unsigned int*)&header[IMAGE_SIZE] - old_padding + new_padding;
//we push these changes in stdout
fwrite(header, MIN_HEADER_SIZE,1,stdout);
}

void change_otherdata(){
    int extra=offset-54;
    //if there are no other data the function doeas nothing 
    if (extra==0){}
    //else we dynamicly create an array in which we read the othere data(or the extra data of an extended header or both) and write it in our file
    else {
       char *other;
       other = (char*) malloc(extra);
       int read=fread(other,sizeof(char),extra,stdin);
       //we check if fread has read the proper number of bytes from "other data" of a proper bmp file
        if(read != extra){
            fprintf(stderr, "Could not read other data");
            exit(1);
        }
       fwrite(other,sizeof(char),extra,stdout);
       //if malloc was succesful we free the allocated memory
       if( other!=NULL) free(other);
    }
}

void pixelarray(){
//Step 1, we create a dynamic 2D array to store the data from pixel array
char **array1;
array1= (char**) malloc(o_height*sizeof(char*));
if (array1==NULL){
    fprintf(stderr,"Not available memory\n");
    exit(1);
}
for(int i=0; i<(o_height);i++){
    array1[i]=(char*)malloc(((3*o_width)+o_padding)*sizeof(char));
    if (array1[i] == NULL){
    fprintf(stderr,"Not available memory\n");
    exit(1);
}
}
for (int i = 0; i < o_height; i++) {
    int read = fread(array1[i], sizeof(char), (3 * o_width) + o_padding, stdin);
    //we check if fread has read the proper number of bytes from "pixel array" of a proper bmp file
    if (read != (3 * o_width) + o_padding) {
        fprintf(stderr, "Could not read pixel array row %d\n", i);
        exit(1);
    }
}


//Step 2, we create a dynamic 2D array to remove the padding of array1 and then we free array1
char **array2;
array2= (char**) malloc(o_height*sizeof(char*));
if (array2==NULL){
    fprintf(stderr,"Not available memory\n");
    exit(1);
}
for(int i=0; i<(o_height);i++){
    array2[i]=(char*)malloc((3*o_width)*sizeof(char));
    if (array2[i] == NULL){
    fprintf(stderr,"Not available memory\n");
    exit(1);
}}
for(int i=0; i<o_height; i++){
    for (int j=0; j<3*o_width; j++){
        array2[i][j]=array1[i][j];
    }
}
//we free array1
for(int i=0; i<o_height; i++){
    free(array1[i]);
}
free(array1);




//attempt diavasmatos
char p='P';
for(int j=3*o_width-1; j>=0; j-=3){
    for(int i=0; i<o_height; i++){//it writes three bytes every time to correclty represent the pixels
        fwrite(&array2[i][j-2],sizeof(char),1,stdout);
        fwrite(&array2[i][j-1],sizeof(char),1,stdout);
        fwrite(&array2[i][j],sizeof(char),1,stdout);
    }
    for(int k=1; k<=n_padding; k++){
        fwrite(&p,sizeof(char),1,stdout);
    }

}

//Step 3, we create a dynamic 2D array in which we store the data of array2 but every 3 columns we add an extra filled with a radom character. I chose to fil it with 'N'.
//We know that width and height are multiples of three so the collumns of the array3 will be 3*width+(3*width)/3
//Then we free array2

/*char **array3;
array3= (char**) malloc(o_height*sizeof(char*));
if (array3==NULL){
    fprintf(stderr,"Not available memory\n");
    exit(1);
}
for(int i=0; i<(o_height);i++){
    array3[i]=(char*)malloc((3*o_width+o_width)*sizeof(char));
    if (array3[i] == NULL){
    fprintf(stderr,"Not available memory\n");
    exit(1);
}}
int counter;
for(int i=1; i<=o_height; i++){
    counter=0;
    for (int j=1; j<=3*o_width+o_width; j++){
        if(o_width%4==0){
        array3[i-1][j-1]='N';
        counter++;
        }
        else{
            array3[i-1][j-1]=array2[i-1][j-1-counter];
    }
    }
}*/
//we free array2
/*for(int i=0; i<o_height; i++){
    free(array2[i]);
}
free(array2);*/

//Step 4, we create dynamic 2D array and we use casting to transfer and rotate the data from array3 in quads
//Then we free array3

/*int n_width=4*o_height;
int n_height=o_width;
char **array4;
array4= (char**) malloc(n_height*sizeof(char*));
if (array4==NULL){
    fprintf(stderr,"Not available memory\n");
    exit(1);
}
for(int i=0; i<(n_height);i++){
    array4[i]=(char*)malloc((n_width)*sizeof(char));
    if (array4[i] == NULL){
    fprintf(stderr,"Not available memory\n");
    exit(1);
}}
int a=-1, b=-1;
for(int j=4*n_height -1; j>=0; j-=4){
    ++a;
    b=-1;
    for (int i=0; i<o_height; i++){
        ++b;
        *( int*)&array4[a][b]=*( int*)&array3[i][j];
    }
}
*/
//we free array3
/*for(int i=0; i<o_height; i++){
    free(array3[i]);
}
free(array3);
*/
//Step 5,we create a dynamic 2D array where we transfer data from array4 but we remove the useless bytes(those filled with 'N') from array4
//Then we free array4
/*char **array5;
array5= (char**) malloc(n_height*sizeof(char*));
if (array5==NULL){
    fprintf(stderr,"Not available memory\n");
    exit(1);
}
for(int i=0; i<(n_height);i++){
    array5[i]=(char*)malloc((n_width-o_height)*sizeof(char));*//*remember n_width is equal to 4*o_heigth*/
   /* if (array5[i] == NULL){
    fprintf(stderr,"Not available memory\n");
    exit(1);
}}
for(int i=1; i<=n_height; i++){
    counter=0;
    for (int j=1; j<=n_width; j++){
        if(n_width%4==0){
        counter++;
        }
        else{
            array5[i-1][j-1]=array4[i-1][j+counter];
    }
    }
}*/
//we free array4
/*for(int i=0; i<n_height; i++){
    free(array4[i]);
}
free(array4);*/
// Step 6, we add padding if there is need to do so, and then we push the data to stdout (row by row)
//we free array5 and array6
/*int new_width=n_width-o_height;
char **array6;
    array6= (char**) malloc(n_height*sizeof(char*));
    if (array6==NULL){
        fprintf(stderr,"Not available memory\n");
        exit(1);
}
    for(int i=0; i<(n_height);i++){
        array6[i]=(char*)malloc((n_width-o_height+n_padding)*sizeof(char));
        if (array6[i] == NULL){
            fprintf(stderr,"Not available memory\n");
            exit(1);
            }}
if (n_padding==0){}
else{  
    for (int i=0; i<n_height;i++){
        for (int j=new_width-n_padding; j<new_width; j++){
            array6[i][j]='P';
        }
    }
}
fwrite(array6,sizeof(char),(new_width+n_padding)*n_height,stdout);*/
//we free array5
/*for(int i=0; i<n_height; i++){
    free(array5[i]);
}
free(array5);
//we free array6
for(int i=0; i<n_height; i++){
    free(array6[i]);
}
free(array6);


*/}

int main(){
change_header();
change_otherdata();
pixelarray();
return 0;
}
