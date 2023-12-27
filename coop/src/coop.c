#include <stdio.h>
int InputFirstOne(void){/*getchar will only accept one character for the main programm*/
    int ch=getchar();
    while(ch!=EOF && ch!='C' && ch!='D'){/*make sure that the only acceptable value is one of these three*/
       ch = getchar(); // Update the value of ch to read the next character 
    }
    return ch;
}
int main(void){
    int counter=0, cha;
    while(counter<1e+6){/*we have this condition to make sure that*/
        if(counter % 1000 !=999){
            putchar('D');
            fflush(stdout);
            putchar('\n');
            fflush(stdout);
        }
        else{
            putchar('C');
            fflush(stdout);
            putchar('\n');
            fflush(stdout);
        }
        cha=InputFirstOne();
        if (cha==EOF) break;
        counter++;
    }
    return 0;

}