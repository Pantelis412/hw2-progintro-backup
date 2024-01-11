#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  // we check if the user used 2 arguments when calling the program
  if (argc != 3) exit(1);
  FILE* fp1 = fopen(argv[1], "r");  // we open the first file(argument) and we choose only to read it
  if (fp1 == NULL) exit(1);  // we want to check the return value of fread to ensure that the file was opened succesfully
  // we do the same for the second file
  FILE* fp2 = fopen(argv[2], "r");
  if (fp2 == NULL) exit(1);


  //As long as fread is succesful, we store a character from file 1 in temp and if it has an acceptable value we add it in string1.
  //We reallocate the memory of the array by one cell so we have space to store the new character read by the fread comnmand.
  //If read is 0 it means that the fread has reached EndOfFile and the loop stops.
  //We add '\0' character after the last valid character of the array.
  char *string1 = NULL;
  char temp;
  int counter1 = 0;
  int read = fread(&temp,sizeof(char),1, fp1);
  // we check if fread has succesfully read a character from the first file
  if (read != 1) {
    fprintf(stderr, "Could not read a single character. The file was empty");
    exit(1);
  }
  while (read==1) { //we check that fread has succesfully read a character
    if (temp == 'A' || temp == 'G' || temp == 'T' || temp == 'C') {//we accpept only these 4 values
      string1 = (char*)realloc(string1, (counter1 + 1)*sizeof(char));//we reallocate the memory by 1 cell
      if (string1 == NULL) {//we check if the reallocation was succesful
        fprintf(stderr, "Not available memory\n");
        exit(1);
      }
      string1[counter1] = temp;//we add the character we read to the string1
      counter1 += 1;
    }
    read = fread(&temp, sizeof(char), 1, fp1);//we take the new character from the file
    //we check if fread has succesfully read 1 character from the first file
    if (read != 1 && read !=0) {
        fprintf(stderr, "Could not read a character");
        fprintf(stderr, "%d\n",read);
        exit(1);
  }
  }
  string1 = (char*)realloc(string1, (counter1 + 1)*sizeof(char));///we reallocate the memory by 1 cell
  if (string1 == NULL) {//we check if the reallocation was succesful
    fprintf(stderr, "Not available memory\n");
    exit(1);
  }
  string1[counter1] = '\0';//we ensure that the last element if the array is '\0'

  //We repeat this proccess for the second file

  char *string2 = NULL;
  int counter2 = 0;
  read = fread(&temp,sizeof(char),1, fp2);
  // we check if fread has succesfully read a character from the first file
  if (read != 1) {
    fprintf(stderr, "Could not read a single character. The file was empty");
    exit(1);
  }
  while (read==1) { //we check that fread has succesfully read a character
    if (temp == 'A' || temp == 'G' || temp == 'T' || temp == 'C') {//we accpept only these 4 values
      string2 = (char*)realloc(string2, (counter2 + 1)*sizeof(char));//we reallocate the memory by 1 cell
      if (string2 == NULL) {//we check if the reallocation was succesful
        fprintf(stderr, "Not available memory\n");
        exit(1);
      }
      string2[counter2] = temp;//we add the character we read to the string2
      counter2 += 1;
    }
    read = fread(&temp, sizeof(char), 1, fp2);//we take the new character from the file
    //we check if fread has succesfully read 1 character from the first file
    if (read != 1 && read !=0) {
        fprintf(stderr, "Could not read a character");
        fprintf(stderr, "%d\n",read);
        exit(1);
  }
  }
  string2 = (char*)realloc(string2, (counter2 + 1)*sizeof(char));///we reallocate the memory by 1 cell
  if (string2 == NULL) {//we check if the reallocation was succesful
    fprintf(stderr, "Not available memory\n");
    exit(1);
  }
  string2[counter2] = '\0';//we ensure that the last element if the array is '\0'

//we close file 1 and file 2 as we do not need them any more
fclose(fp1);
fclose(fp2);
//we call comparison function to compare the two strings we got from the files
//comparison();
//we free the two dynamic arrays 
  free(string2);
  free(string1);
  return 0;
}