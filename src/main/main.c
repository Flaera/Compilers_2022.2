#include <stdio.h>
#include <stdlib.h>
#define BIG_INT 100000
//caracteres ables:
#define END 125
#define INIT 32
#define SPACE 10
//Debugers:
#define DEBUG0 if(0)
#define DEBUG1 if(1)


//classes of globals tokens
char PR[14][BIG_INT] = {
    "program\0", 
    "integer\0", "real\0", "boolean\0",
    "program\0", "begin\0", "end\0",
    "var\0", "fifo_of_integer\0", "fifo_of_real\0",
    "procedure\0", "function\0",
    "concatena_fifo\0", "inverte_fifo\0"
    };
char DS[6] = {
    ';','.','(',')','[',']'
};
char MATH_OPERATORS[6][3] = {
    "+\0","-\0","*\0","/\0","//\0",":=\0"
};
char REL_OPERATORS[6][3] = {
    "=\0",">\0","<\0",">=\0","<=\0","<>\0"
};
char VALUES_BOLLEAN[3][10] = {"true\0", "false\0", "empty\0"};

int acc_adress = 0;


//Node of fifo
typedef struct node{
    char value[BIG_INT];
    char type[BIG_INT];
    int adress;
    int line;
    struct node *next; // struct node *next = malloc(sizeof(node*BIG_INT));
}Node;


//Insert in fifo
Node* insertFifo(Node *fifo, char new_value, char new_type, int new_line){
    Node *new_node = malloc(sizeof(Node));
    int acc=0;
    if (new_node!=NULL){
        *new_node->value = new_value;
        *new_node->type = new_type;
        *new_node->type = acc_adress;
        new_node->line = new_line;
        new_node->next = NULL;
        if(fifo==NULL){
            fifo = new_node;
            acc_adress++;
        }
        else{
            Node *aux = fifo;
            fifo = aux;
            while (aux->next!=NULL){
                acc+=1;
                aux = aux->next;
            }
            aux->next = new_node;
            acc_adress++;
        }
    }
    else{printf("Incapaz de alocar memoria. Erro.\n");}
    return fifo;
}


Node* removeFifo(Node *fifo){
    DEBUG1{printf("OI!-%c-\n", *fifo->value);}
    Node *rem = fifo;
    if (rem!=NULL){
        Node *aux = rem->next;
        fifo = aux;
        acc_adress--;
        return fifo;
        DEBUG1{printf("OIIIIIIIIII-%c-\n", *(fifo->next)->value);}
    }
    else{printf("Lista vazia. Erro.\n");}
    rem->next=NULL;
    return rem;
}


Node* findFifo(Node *fifo, char searched){
    if (fifo!=NULL){
        Node *aux = fifo;
        while(*aux->value!=searched && aux->next!=NULL){
            aux = aux->next;
            if (*aux->value==searched){return aux;}
        }
    }
    else{printf("Lista vazia. Erro.\n");}
    return NULL;
}


Node* invertFifo(Node *fifo){ //IN ANALINSING
    int acc0 = 0;
    char sequence[BIG_INT];
    Node *aux = fifo;
    Node *new_fifo_inverted = fifo;
    while(aux->next!=NULL){
        sequence[acc0] = *aux->value;
        acc0+=1;
        aux = aux->next;
        new_fifo_inverted->next = aux->next;
    }
    aux = fifo;
    while(acc0>=0){
        *new_fifo_inverted->value = sequence[acc0];
        DEBUG1{printf("seq=%c\n", *new_fifo_inverted->value);}
        if (acc0==0){new_fifo_inverted->next=NULL;break;}
        else{new_fifo_inverted->next = aux;}
        acc0-=1;
    }
    return new_fifo_inverted;
}


Node* concatenaFifo(Node* fifo0, Node* fifo1){ //IN ANALINSING
    Node* aux = fifo0;
    while(aux->next!=NULL){
        aux = aux->next;
    }
    aux->next = fifo1;
    return fifo0;
}


int compareString(char* str0, char* str1){
    int acc = 0;
    //DEVELOPER TODAY
}


int main(){
    printf("Lendo script...\n");
    DEBUG0{printf("Before fgets or getchar()\n");}
    char sequence_cp[BIG_INT];
    int acc = 0;
    do {
        sequence_cp[acc]=(char)getchar();
        DEBUG0{printf("-acc:%d|%c-", acc, sequence_cp[acc]);}
        acc+=1;
    } while((sequence_cp[acc-1]>=INIT && sequence_cp[acc-1]<=END) || (sequence_cp[acc-1]==SPACE));
    sequence_cp[acc-1]='\0';
    printf("Script lido.\n");
    
    

    return 0;
}