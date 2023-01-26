#include <stdio.h>
#include <string.h>

#define INT_MAX 256000
#define DEBUG1 if(0)
#define DEBUG2 if(0)
#define DEBUG3 if(0)
#define DEBUG4 if(0)
#define DEBUG5 if(0)
#define TRUE 1
#define FALSE 0


int reconG1(char sequence[]){
    int step0 = FALSE;
    int step1 = TRUE;
    int final = FALSE;
    if (sequence[0]=='b'){
        step0 = TRUE;
    }
    int acc=1;
    int len = strlen(sequence);
    while (acc<len && sequence[acc]!='\0'){
        DEBUG1{printf("acc/seq:%d - %d\n", acc, sequence[acc]);}
        if ((sequence[acc]!='a') && (acc<len-1)){
            DEBUG1{printf("FALSEOU!! len=%d\n", len);}
            step1=FALSE;
            break;
        }
        acc++;
    }
    if (step0==TRUE && step1==TRUE){final=TRUE;}

    return final;
}


int reconG2(char seq[]){
    int step0 = FALSE;
    int step1 = TRUE;
    int final = FALSE;
    if (seq[0]=='a' && seq[1]=='^'){
        step0 = TRUE;
    }
    int acc=2;
    int len = strlen(seq);
    while (acc<len && seq[acc]!='\0'){
        DEBUG2{printf("acc/seq:%d - %d\n", acc, seq[acc]);}
        if ((seq[acc]!='b') && (acc<len-1)){
            DEBUG2{printf("FALSEOU!! len=%d\n", len);}
            step1=FALSE;
            break;
        }
        acc++;
    }
    if (step0==TRUE && step1==TRUE){final=TRUE;}

    return final;
}


int reconG3(char seq[]){
    int final = FALSE;
    int step0 = FALSE;
    int len = strlen(seq);
    DEBUG3{printf("tam=%d\n",len);}
    if (seq[len-2]=='c'){step0=TRUE;}
    else{return FALSE;}

    int acc = 0;
    int step2 = FALSE;
    while (len>=4 && acc<len && seq[acc]!='\0'){
        int step1 = FALSE;
        if (seq[acc]=='a' && seq[acc+1]=='a' && seq[acc+2]=='b' && seq[acc+3]=='b'){
            DEBUG3{printf("FOI %d\n", acc);}
            step1 = TRUE;
            acc += 4;
        }
        else{break;}
        if (step1==TRUE && seq[acc]!='c' && acc<len){continue;}
        else if (step1==TRUE && seq[acc]=='c'){
            step2 = TRUE;
            break;
        }
    }

    if (step0==TRUE && step2==TRUE){final=TRUE;}
    return final;
}


int reconG4(char seq[]){
    int final = FALSE;
    int len = strlen(seq);
    DEBUG4{printf("len=%d\n", len);}
    DEBUG4{printf("seq elem=%c\n", seq[len-2]);}
    int step0 = TRUE;
    int step1 = FALSE;
    if (seq[0]!='a' && seq[len-2]!='a' && len>=4){step0=FALSE;}
    int acc0 = 0;
    while (seq[acc0]!='\0' && len>3 && acc0<len-2){
        if (seq[acc0]!='a' && seq[acc0+2]!='a'){
            DEBUG4{printf("FOI UM\n");}
            step1=FALSE;break;
        }
        if ((seq[acc0+1]=='*') ^ (seq[acc0+1]=='+')){
            DEBUG4{printf("FOI DOIS\nacc:%d\n",acc0);}
            step1=TRUE;
        }
        else{step1=FALSE;break;}
        acc0 += 2;
    }
    DEBUG4{printf("steps: %d-%d\n", step0, step1);}
    if (step0==TRUE && step1==TRUE){final=TRUE;}
    return final;
}


int reconG5(char seq[]){
    int final = FALSE;
    int len = strlen(seq);
    DEBUG5{printf("len=%i\n", len);}
    int step0=TRUE;
    int step1=TRUE;
    int acc0 = 0;
    while (acc0<len-2 && seq[acc0]!='\0'){
        if (seq[acc0]!='0'){
            if (seq[acc0]=='1'){break;}
            else{step0=FALSE;break;}
        }
        acc0+=1;
    }
    DEBUG5{printf("step0=%d, acc0=%d\n", step0, acc0);}
    int len1 = (acc0*2)-1;
    for (int i=acc0; i<len1; ++i){
        DEBUG5{printf("seq=%c\n", seq[i]);}
        if (seq[i]!='1'){step1=FALSE;break;}
        acc0 += 1;
    }
    DEBUG5{printf("seq_final=%i\n", seq[acc0]);}
    if (seq[acc0]==10 && step0==TRUE && step1==TRUE){final=TRUE;}
    return final;
}


int reconAllG(char seq[]){
    if (reconG1(seq)==TRUE || reconG2(seq)==TRUE || reconG3(seq)==TRUE || reconG4(seq)==TRUE || 
        reconG5(seq)==TRUE){return TRUE;}
    return FALSE;
}


int main(int agrc, char** argv){

    printf("Digite a sequência:\n");
    char seq[INT_MAX-1];
    fgets(seq,INT_MAX-1,stdin);
    printf("Sequência: %s", seq);
    printf("Resultado (1-reconhecível e 0-não reconhecível): %d.\n",reconAllG(seq));

    return 0;
}