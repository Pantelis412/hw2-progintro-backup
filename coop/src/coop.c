#include <stdio.h>
int InputFirstOne(void){
    int ch=getchar();
    while(ch!=EOF && ch!='C' && ch!='D'){/*make sure that the only acceptable value is one of these three*/
       ch = getchar(); // Update the value of ch to read the next character if the one previously read was not among these 3
    }
    return ch;
}
int main(void){
    int counter=0, cha;
    while(counter<1e+6){/*we have this condition to make sure that the max rounds to be played are 10^6*/
        if(counter % 1000 !=999){//every 1000 rounds we must play a 'C'
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
        cha=InputFirstOne();//we use this function to read a valid character from the opponent (stdin)
        if (cha==EOF) break;
        counter++;
    }
    return 0;

}