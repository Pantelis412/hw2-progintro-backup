#include <stdio.h>
#include <stdlib.h>

void comparison(char* string1, char* string2, int counter1, int counter2) {
  int position, length = 0, max_length = 0, a, b, count = 0, k;
  for (int i = 0; i < counter1; i++) {//we compare a character from the first string to all characters of the second until we find a match
    for (int j = 0; j < counter2; j++) {
      if (string1[i] == string2[j]) {//When we find that match we check if the next character of the first string matches the next character of the second string. We do that here"***""
        length = 1;
        a = i;//we use different variables
        b = j;//insdie the loop
        if (counter1 - a > 0 && counter2 - b > 0) {//we check if both strings have available charcters to compare
          a++;
          b++;
        } else
          break;
        while (string1[a] == string2[b]) {//"***"
          length += 1;//we count the length of the match
          if (counter1 - a > 0 && counter2 - b > 0) {//we keep doing that as long as there are available characters in both strings and there is still a match
            a++;
            b++;
            
          } else
            break;
        }
      }
      if (max_length < length) {//when we do not have a match anymore, we check to see if our match is bigger in length than the greatest one we have.
        position = i;//if yes, we store the position of the string1's first character of the match in this variable
        max_length = length;
      }
    }
  }
  //when we are done with this process,
  //if there is a match we print the part of string1 from the starting point of the biggest match to the starting point of the biggest match plus the length of the biggest match
  if (length != 0) {
    for (k = position; k < position+max_length; k++) {
      printf("%c", string1[k]);
      count += 1;
    }
    printf("\n");
  } else {
    printf("There is no common chain");
  }
}

int main(int argc, char** argv) {
  // we check if the user used 2 arguments when calling the program
  if (argc != 3) exit(1);
  FILE* fp1 = fopen(
      argv[1],
      "r");  // we open the first file(argument) and we choose only to read it
  if (fp1 == NULL)
    exit(1);  // we want to check the return value of fread to ensure that the
              // file was opened succesfully
  // we do the same for the second file
  FILE* fp2 = fopen(argv[2], "r");
  if (fp2 == NULL) exit(1);

  // As long as fread is succesful, we store a character from file 1 in temp and
  // if it has an acceptable value we add it in string1. We reallocate the memory
  // of the array by one cell so we have space to store the new character read by
  // the fread comnmand. If read is 0 it means that the fread has reached
  // EndOfFile and the loop stops. We add '\0' character after the last valid
  // character of the array.
  char* string1 = NULL;
  char temp;
  int counter1 = 0;
  int read = fread(&temp, sizeof(char), 1, fp1);
  // we check if fread has succesfully read a character from the first file
  if (read != 1) {
    fprintf(stderr, "Could not read a single character. The file was empty");
    exit(1);
  }
  while (read == 1) {  // we check that fread has succesfully read a character
    if (temp == 'A' || temp == 'G' || temp == 'T' ||
        temp == 'C') {  // we accpept only these 4 values
      string1 = (char*)realloc(
          string1,
          (counter1 + 1) * sizeof(char));  // we reallocate the memory by 1 cell
      if (string1 == NULL) {  // we check if the reallocation was succesful
        fprintf(stderr, "Not available memory\n");
        exit(1);
      }
      string1[counter1] = temp;  // we add the character we read to the string1
      counter1 += 1;
    }
    read = fread(&temp, sizeof(char), 1,
                 fp1);  // we take the new character from the file
    // we check if fread has succesfully read 1 character from the first file
    if (read != 1 && read != 0) {
      fprintf(stderr, "Could not read a character");
      fprintf(stderr, "%d\n", read);
      exit(1);
    }
  }
  string1 = (char*)realloc(
      string1,
      (counter1 + 1) * sizeof(char));  /// we reallocate the memory by 1 cell
  if (string1 == NULL) {  // we check if the reallocation was succesful
    fprintf(stderr, "Not available memory\n");
    exit(1);
  }
  string1[counter1] =
      '\0';  // we ensure that the last element if the array is '\0'

  // We repeat this proccess for the second file

  char* string2 = NULL;
  int counter2 = 0;
  read = fread(&temp, sizeof(char), 1, fp2);
  // we check if fread has succesfully read a character from the first file
  if (read != 1) {
    fprintf(stderr, "Could not read a single character. The file was empty");
    exit(1);
  }
  while (read == 1) {  // we check that fread has succesfully read a character
    if (temp == 'A' || temp == 'G' || temp == 'T' ||
        temp == 'C') {  // we accpept only these 4 values
      string2 = (char*)realloc(
          string2,
          (counter2 + 1) * sizeof(char));  // we reallocate the memory by 1 cell
      if (string2 == NULL) {  // we check if the reallocation was succesful
        fprintf(stderr, "Not available memory\n");
        exit(1);
      }
      string2[counter2] = temp;  // we add the character we read to the string2
      counter2 += 1;
    }
    read = fread(&temp, sizeof(char), 1,
                 fp2);  // we take the new character from the file
    // we check if fread has succesfully read 1 character from the first file
    if (read != 1 && read != 0) {
      fprintf(stderr, "Could not read a character");
      fprintf(stderr, "%d\n", read);
      exit(1);
    }
  }
  string2 = (char*)realloc(
      string2,
      (counter2 + 1) * sizeof(char));  /// we reallocate the memory by 1 cell
  if (string2 == NULL) {  // we check if the reallocation was succesful
    fprintf(stderr, "Not available memory\n");
    exit(1);
  }
  string2[counter2] =
      '\0';  // we ensure that the last element if the array is '\0'

  // we close file 1 and file 2 as we do not need them any more
  fclose(fp1);
  fclose(fp2);
  // we call comparison function to compare the two strings we got from the
  // files
  comparison(string1, string2, counter1, counter2);
  // we free the two dynamic arrays
  free(string2);
  free(string1);
  return 0;
}