#include <stdlib.h>
#include <stdio.h>


int main(){

    char str0[256];
    char str1[256];

    fgets(str0, 256, stdin);
    fgets(str1, 256, stdin);

    int acc0 = 0;
    while (str0[acc0]!='\0'){
        acc0++;
    }
    int acc1 = 0;
    while (str1[acc1]!='\0'){
        acc1++;
    }
    int acc2 = 0;
    while (acc2 <= acc1){
        str0[acc0+acc2] = str1[acc2];
        acc2++;
    }
    str0[acc0+acc2]='\0';

    printf("String: -%s-\n", str0);
}