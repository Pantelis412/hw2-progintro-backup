#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv){
    //we check if the user used 2 arguments when calling the program
    if (argc!=3) exit(1);
    FILE *fp1 = fopen(argv[1],"r");//we open the first file(argument) and we choose only to read it
    //we want to check the return value of fread to ensure that that file was opened succesfully
}