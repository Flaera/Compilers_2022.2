#include <stdio.h>
#include <stdlib.h>
#define BIG_INT 100000
#define LOW_INT 100
//caracteres ables:
#define END 125
#define INIT 32
#define SPACE 10
//Debugers:
#define DEBUG0 if(0)
#define DEBUG1 if(0)
#define DEBUG3 if(1)


//classes of globals tokens
char PR[11][BIG_INT] = {
    "program\0", 
    "integer\0", "real\0", "boolean\0",
    "var\0", "fifo_of_integer\0", "fifo_of_real\0",
    "procedure\0", "function\0",
    "concatena_fifo\0", "inverte_fifo\0"
};
char DS[7][2] = {
    ";\0",".\0",",\0","(\0",")\0","[\0","]\0"
};
char DC[2][6] = {
    "begin\0", "end\0"
};
char MATH_OPERATORS[6][3] = {
    "+\0","-\0","*\0","/\0","//\0",":=\0"
};
char REL_OPERATORS[6][3] = {
    "=\0",">\0","<\0",">=\0","<=\0","<>\0"
};
char VALUES_BOLLEAN[3][6] = {"true\0", "false\0", "empty\0"};

int acc_adress = 0;


//Node of fifo
typedef struct node{
    char value[BIG_INT];
    char type[BIG_INT];
    char error[BIG_INT];
    int adress;
    int line;
    int sentence;
    struct node *next; // struct node *next = malloc(sizeof(node*BIG_INT));
}Node;


//Insert in fifo
Node* insertFifo(Node *fifo, char* new_value, char* new_type,
 int new_line, int new_sentence, char* new_error){
    Node *new_node = malloc(sizeof(Node));
    int acc=0;
    if (new_node!=NULL){
        int i = 0;
        while(new_value[i]!='\0'){new_node->value[i] = new_value[i];i++;}new_node->value[i]='\0';
        int j = 0;
        while(new_type[j]!='\0'){new_node->type[j] = new_type[j];j++;}new_node->type[j]='\0';
        int k=0;
        while(new_error[k]!='\0'){new_node->error[k] = new_error[k];k++;}new_node->error[k]='\0';
        new_node->sentence = new_sentence;
        new_node->adress = acc_adress;
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
    while (str0[acc]==str1[acc] && str0[acc]!='\0' && str1[acc]!='\0'){
        acc++;
    }
    if (str0[acc]=='\0'&&str1[acc]=='\0'){return 1;}
    return 0;
}


void invertString(char str[]){
    int acc = 0;
    char str1[BIG_INT];
    while(str[acc]!='\0'){
        str1[acc] = str[acc];
        acc++;
    }
    acc-=1;
    int i=0;
    while(acc>=0){
        str[i]=str1[acc];
        acc--;
        i++;
    }
    str1[i] = '\0';
    return;
}


void programErrorMessageAnaLex(int curr_line){
    printf("Erro de sintaxe no programa. Linha: %d.\n", curr_line);
}


int isDS(char str[]){
    for (int i=0; i<7; ++i){
        if (compareString(str,DS[i])==1){return 1;}
    }
    return 0;
}


int isPR(char str[]){
    for (int i=0; i<11; ++i){
        if (compareString(str,PR[i])==1){return 1;}
    }
    return 0;
}


int isDC(char str[]){
    for (int i=0; i<2; ++i){
        if (compareString(str, DC[i])){return 1;}
    }
    return 0;
}


void showTokens(Node* tokens){
    printf("TOKENS FIFO:\n");
    Node* aux = tokens;
    while (aux->next!=NULL){
        if (aux->error[0]=='N'){
            printf("## %s|%s|%d|%d|%d ## \n", aux->value, aux->type,
             aux->adress, aux->line, aux->sentence);
        }
        else{
            printf("## %s|%s|%d|%d|%d ## | ERRO!  \n", aux->value, aux->type,
             aux->adress, aux->line, aux->sentence);
        }
        aux = aux->next;
    }

    free(tokens);
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
    printf("Script lido. Script:\n");
    printf("%s\n", sequence_cp);
    printf("----\n");

    //Tokenzing with fifo:
    Node* tokens = malloc(sizeof(Node));
    int current_line = 0;
    int curr_sentence = 0;
    char* part = malloc(BIG_INT);
    int i = acc-2;
    while (i>=0){
        if (sequence_cp[i]=='\n'){current_line++;}
        if (sequence_cp[i]==';'){curr_sentence++;}

        if (sequence_cp[i]==';' || sequence_cp[i]==',' || sequence_cp[i]=='.'
         || sequence_cp[i]=='(' || sequence_cp[i]==')' || sequence_cp[i]=='['
          || sequence_cp[i]==']'){
            part[0]=sequence_cp[i];part[1]='\0';
            tokens=insertFifo(tokens,part,"DS\0",current_line,curr_sentence,"NO\0");
            acc_adress++;
            i--;
        }
        else if (sequence_cp[i]==' ' || sequence_cp[i]=='\t' || sequence_cp[i]=='\n'){
            int j = i-1;
            int l = 0;
            // DEBUG3{printf("AQUI\n");}
            while ((sequence_cp[j]>=97 && sequence_cp[j]<=122
             && sequence_cp[i]!=';' && sequence_cp[i]!=',' && sequence_cp[i]!='.'
              && sequence_cp[i]!='(' && sequence_cp[i]!=')' && sequence_cp[i]!='['
               && sequence_cp[i]!=']' && sequence_cp[i]!='\"')){
                part[l] = sequence_cp[j];
                j--;
                l++;
                // DEBUG3{printf("AQUI!!!!\n");}
            }
            part[l]='\0';
            invertString(part);
            DEBUG3{printf("part:%s-%d-%d-\n", part, j, l);}
            if (isDS(part)){
                tokens=insertFifo(tokens,part,"DS\0",current_line,curr_sentence,"NO\0");
            }
            else if (isPR(part)){
                tokens=insertFifo(tokens,part,"PR\0",current_line,curr_sentence,"NO\0");
            }
            else if (isDC(part)){
                tokens=insertFifo(tokens,part,"DC\0",current_line,curr_sentence,"NO\0");
            }
            i = i-l-1;
        }
        else{
            // DEBUG3{printf("-%d-\n", sequence_cp[i]);}
            programErrorMessageAnaLex(current_line);
            insertFifo(tokens,part,"ERRO\0",current_line,curr_sentence,"YES\0");
            i--;
        }
        acc_adress++;
    }
    free(part);

    // showTokens(tokens);

    return 0;
}