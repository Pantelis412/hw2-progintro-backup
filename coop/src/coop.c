#include <stdio.h>
int InputFirstOne(void){
    int ch=getchar();
    while(ch!=EOF && ch!='C' && ch!='D'){
       ch = getchar(); // Update the value of ch to read the next character 
    }
    return ch;
}
int main(void){
    int counter =0, cha;
    while(counter<10){/*idea:   if ch=getchar()==EOF break;*/
        if(counter % 1000 !=999){
            putchar('D');
            fflush(stdout);
            putchar('\n');
            fflush(stdout);
            printf("%d\n",counter);
        }
        else{
            putchar('C');
            fflush(stdout);
            putchar('\n');
            fflush(stdout);
            printf("EWQ%d\n",counter);
        }
        cha=InputFirstOne();
        if (cha==EOF) break;
        counter++;
    }
    return 0;

}