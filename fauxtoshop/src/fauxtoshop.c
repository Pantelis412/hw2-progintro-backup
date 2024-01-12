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

void change_header() {
  char header[MIN_HEADER_SIZE];
  int read = fread(header, MIN_HEADER_SIZE, 1, stdin); //we use fread to read the header of a bmp file
  // we check if fread has read the proper number of bytes from a proper bmp file
  if (read != 1) {
    fprintf(stderr, "Could not read headers");
    exit(1);
  }
  // check if the bmp file starts with the magic header ('B' 'M')
  if (header[0] != 'B' || header[1] != 'M') {
    fprintf(stderr, "Wrong input");
    exit(1);
  }
  // we check if the bmp file uses 24 bits per pixel
  int bits;
  bits = header[BITS_PER_PIXEL] + header[BITS_PER_PIXEL + 1] * 256;
  if (bits != 24) {
    fprintf(stderr, "Wrong bits per pixel size");
    exit(1);
  }
  int width, height; /*we save width and height of the bmp file in these integer
                        type variables*/
  width = *(unsigned int *)&header[WIDTH];
  o_width = width;
  height = *(unsigned int *)(header + HEIGHT);
  o_height = height;
  // We swap width and height in the header
  *(unsigned int *)&header[WIDTH] = height;
  *(unsigned int *)&header[HEIGHT] = width;
  offset = *(unsigned int *)&header[OFFSET];
  //we calculate the new and the old padding
  // based on the width and heigth of the header and we change the information
  // about he file size and the image size of the header
  int old_padding;
  if (((3 * width) % 4) == 0)
    old_padding = 0;
  else
    old_padding = 4 - ((3 * width) % 4);
  o_padding = old_padding;
  old_padding *= height;
  int new_padding;
  if (((3 * height) % 4) == 0)
    new_padding = 0;
  else
    new_padding = 4 - ((3 * height) % 4);
  n_padding = new_padding;
  new_padding *= width;
  *(unsigned int *)&header[FILE_SIZE] = *(unsigned int *)&header[FILE_SIZE] - old_padding + new_padding;
  *(unsigned int *)&header[IMAGE_SIZE] = *(unsigned int *)&header[IMAGE_SIZE] - old_padding + new_padding;
  // we push these changes in stdout
  fwrite(header, MIN_HEADER_SIZE, 1, stdout);
}

void change_otherdata() {
  int extra = offset - 54;
  // if there are no "other data" the function does nothing
  if (extra == 0) {
  }
  // else we dynamicly create an array in which we read the othere data(or the
  // extra data of an extended header or both) and write it in our file
  else {
    char *other;
    other = (char *)malloc(extra);
    int read = fread(other, sizeof(char), extra, stdin);
    // we check if fread has read the proper number of bytes from "other data"
    // of a proper bmp file
    if (read != extra) {
      fprintf(stderr, "Could not read other data");
      exit(1);
    }
    fwrite(other, sizeof(char), extra, stdout);
    // if malloc was succesful we free the allocated memory
    if (other != NULL) free(other);
  }
}

void pixelarray() {
  // Step 1, we create a dynamic 2D array to store the data from pixel array
  char **array1;
  array1 = (char **)malloc(o_height * sizeof(char *));
  if (array1 == NULL) {
    fprintf(stderr, "Not available memory\n");
    exit(1);
  }
  for (int i = 0; i < (o_height); i++) {
    array1[i] = (char *)malloc(((3 * o_width) + o_padding) * sizeof(char));
    if (array1[i] == NULL) {
      fprintf(stderr, "Not available memory\n");
      exit(1);
    }
  }
  for (int i = 0; i < o_height; i++) {
    int read = fread(array1[i], sizeof(char), (3 * o_width) + o_padding, stdin);
    // we check if fread has read the proper number of bytes from "pixel array"
    // of a proper bmp file
    if (read != (3 * o_width) + o_padding) {
      fprintf(stderr, "Could not read pixel array row %d\n", i);
      exit(1);
    }
  }

  //Step 2, we create a dynamic 2D array to remove the padding of array1, 
  //transfering all the columns from array1 to array2 except those they contain padding.
  //Then we free array1.
  char **array2;
  array2 = (char **)malloc(o_height * sizeof(char *));
  if (array2 == NULL) {
    fprintf(stderr, "Not available memory\n");
    exit(1);
  }
  for (int i = 0; i < (o_height); i++) {
    array2[i] = (char *)malloc((3 * o_width) * sizeof(char));
    if (array2[i] == NULL) {
      fprintf(stderr, "Not available memory\n");
      exit(1);
    }
  }
  for (int i = 0; i < o_height; i++) {
    for (int j = 0; j < 3 * o_width; j++) {
      array2[i][j] = array1[i][j];
    }
  }
  // we free array1
  for (int i = 0; i < o_height; i++) {
    free(array1[i]);
  }
  free(array1);

  //Step 3, we want to rotate the pixel array so that the image we make has rotated by 90 degrees right.
  //However, the pixel array is inverted so the first line we read actually depicts the bottom line of the picture.
  //Moreover, ervery pixel conists of three bytes,which means three consecutive elements of the array.
  //Thus, we want to 
  char p = 'P';
  for (int j = 3 * o_width - 1; j >= 0; j -= 3) {
    for (int i = 0; i < o_height; i++) {  // it writes three bytes every time to
                                          // correclty represent the pixels
      fwrite(&array2[i][j - 2], sizeof(char), 1, stdout);
      fwrite(&array2[i][j - 1], sizeof(char), 1, stdout);
      fwrite(&array2[i][j], sizeof(char), 1, stdout);
    }
    for (int k = 1; k <= n_padding; k++) {
      fwrite(&p, sizeof(char), 1, stdout);
    }
  }

  // we free array2
  for (int i = 0; i < o_height; i++) {
    free(array2[i]);
  }
  free(array2);
}

int main() {
  change_header();
  change_otherdata();
  pixelarray();
  return 0;
}
