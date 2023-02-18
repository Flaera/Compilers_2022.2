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
char PR[13][BIG_INT] = {
    "program\0", 
    "integer\0", "real\0", "boolean\0",
    "var:\0", "fifo_of_integer\0", "fifo_of_real\0",
    "procedure\0", "function\0",
    "concatena_fifo\0", "inverte_fifo\0",
    "write\0", "read\0"
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
char DIGITO[10][2] = {"0\0","1\0","2\0","3\0","4\0","5\0","6\0","7\0","8\0","9\0"};
char DIGIT[9][2] = {"1\0","2\0","3\0","4\0","5\0","6\0","7\0","8\0","9\0"};

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
    if (str0[acc]=='\0' && str1[acc]=='\0'){
        // DEBUG3{printf("part-c:str0:%d, str1:%d\n",str0[acc],str1[acc]);}
        return 1;}
    // int acc1 = 0;
    // while (str0[acc]!='\0' && str1[acc1]!='\0'){
    //     if (str0[acc]!=str1[acc] || acc!=acc1){return 1;}
    //     if (str0[acc]!='\0'){acc++;}
    //     if (str1[acc]!='\0'){acc1++;}
    // }
    // if (str0[acc]=='\0' && str1[acc]=='\0'){
    //     DEBUG3{printf("part-c:str0:%d, str1:%d\n",str0[acc],str1[acc]);}
    //     return 1;
    // }
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


char* toString(char i, char* string){
    char* str = malloc(BIG_INT);
    str[0]=i;
    int acc = 1;
    while(string[acc]!='\0'){str[acc+1]=string[acc];acc++;}
    str[acc+1]='\0';
    return str;
}


void programErrorMessageAnaLex(int curr_line){
    printf("Erro de sintaxe no programa. Linha: %d.\n", curr_line);
}


int isDS(char str[]){
    for (int i=0; i<7; ++i){
        if (compareString(str,DS[i])){return 1;}
    }
    return 0;
}


int isPR(char str[]){
    for (int i=0; i<13; ++i){
        // DEBUG3{printf("AQUI MESMO!!!%s-%s\n", PR[i], str);}
        if (compareString(str,PR[i])){return 1;}
        // DEBUG3{printf("AQUI N DÀ\n");}
    }
    return 0;
}


int isDC(char str[]){
    for (int i=0; i<2; ++i){
        if (compareString(str, DC[i])){return 1;}
    }
    return 0;
}


int isMO(char str[]){
    for (int i=0; i<6; ++i){
        if (compareString(str, MATH_OPERATORS[i])){return 1;}
    }
    return 0;
}


int isRO(char str[]){
    for (int i=0; i<6; ++i){
        if (compareString(str, REL_OPERATORS[i])){return 1;}
    }
    return 0;
}


void showTokens(Node* tokens){
    printf("TOKENS FIFO:\n");
    Node* aux = tokens;
    
    while (aux->next!=NULL){
        if (aux->error[0]=='N'){
            printf("## valor:%s|tipo:%s|endereco:%d|linha:%d|sentenca:%d ##\n",
                aux->value, aux->type,
                aux->adress, aux->line, aux->sentence);
        }
        aux = aux->next;
    }
    if (aux->error[0]=='N'){
        printf("## valor:%s|tipo:%s|endereco:%d|linha:%d|sentenca:%d ##\n",
            aux->value, aux->type,
            aux->adress, aux->line, aux->sentence);
    }

    aux = tokens;
    while (aux->next!=NULL){
        if (aux->error[0]=='Y'){
            printf("## valor:%s|tipo:%s|endereco:%d|linha:%d|sentenca:%d ## | ERRO! \n",
                aux->value, aux->type,
                aux->adress, aux->line, aux->sentence);
        }
        aux = aux->next;
    }
    if (aux->error[0]=='Y'){
        printf("## valor:%s|tipo:%s|endereco:%d|linha:%d|sentenca:%d ## | ERRO! \n",
            aux->value, aux->type,
            aux->adress, aux->line, aux->sentence);
    }

    free(aux);
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
        DEBUG3{printf("sequence:%c\n", sequence_cp[i]);}
        if (sequence_cp[i]=='\n'){current_line++;}
        if (sequence_cp[i]==';'){curr_sentence++;}

        if (sequence_cp[i]==';' || sequence_cp[i]==',' || sequence_cp[i]=='.'
         || sequence_cp[i]=='(' || sequence_cp[i]==')' || sequence_cp[i]=='['
          || sequence_cp[i]==']'){
            part[0]=sequence_cp[i];part[1]='\0';
            DEBUG3{printf("partDS:%s-\n", part);}
            tokens=insertFifo(tokens,part,"DS\0",current_line,curr_sentence,"NO\0");
            i--;
        }
        else if (sequence_cp[i]=='f' && sequence_cp[i-1]>=48 && sequence_cp[i-1]<=57){
            tokens=insertFifo(tokens,"f\0","PR\0",current_line,curr_sentence,"NO\0");
            i--;
        }
        else if ((sequence_cp[i]>=97 && sequence_cp[i]<=122)){
            int j = i;
            int l = 0;
            while ((sequence_cp[j]>=97 && sequence_cp[j]<=122)){
                part[l] = sequence_cp[j];
                j--;
                l++;
            }
            invertString(part);
            DEBUG3{printf("partPR-DC:%s-\n", part);}

            if (isPR(part)){
                tokens=insertFifo(tokens,part,"PR\0",current_line,curr_sentence,"NO\0");
            }
            else if (isDC(part)){
                tokens=insertFifo(tokens,part,"DC\0",current_line,curr_sentence,"NO\0");
            }
            i = i-l-1;
        }
        else if (sequence_cp[i]==':' && sequence_cp[i-1]=='r' && sequence_cp[i-2]=='a'
         && sequence_cp[i-3]=='v'){
            // part = "var:\0";
            DEBUG3{printf("partPRvar:%s-\n", part);}
            tokens=insertFifo(tokens,part,"PR\0",current_line,curr_sentence,"NO\0");
            i=i-5;
        }
        else if (sequence_cp[i]==37||sequence_cp[i]==42
        
            ||sequence_cp[i]==187||sequence_cp[i]==188
            ||sequence_cp[i]==191||sequence_cp[i]==192||sequence_cp[i]==195
            ||sequence_cp[i]==197||sequence_cp[i]==200||sequence_cp[i]==201
            ||sequence_cp[i]==206||sequence_cp[i]==217||sequence_cp[i]==218
            ||sequence_cp[i]==43
            
            ||sequence_cp[i]==45
            ||sequence_cp[i]==193||sequence_cp[i]==194||sequence_cp[i]==196
            ||sequence_cp[i]==202||sequence_cp[i]==203||sequence_cp[i]==205
            
            ||sequence_cp[i]==47
            ||compareString(toString(sequence_cp[i],"/\0"),"//\0")
            ||compareString(toString(sequence_cp[i],"=\0"),":=\0")){
            int j = i;
            int l = 0;
            while ((sequence_cp[i]==37||sequence_cp[i]==42||sequence_cp[i]==43
            ||sequence_cp[i]==45||sequence_cp[i]==47)
            ||compareString(toString(sequence_cp[i],"/\0"),"//\0")
            ||compareString(toString(sequence_cp[i],"=\0"),":=\0")){
                part[l] = sequence_cp[j];
                j--;
                l++;
            }
            part[l]='\0';
            invertString(part);
            DEBUG3{printf("partMO:%s-\n", part);}

            if (isMO(part)){
                tokens=insertFifo(tokens,part,"MO\0",current_line,curr_sentence,"NO\0");
            }
            else{
                tokens=insertFifo(tokens,part,"ID\0",current_line,curr_sentence,"YES\0");
            }
            i = i-l-1;
        }
        else if (sequence_cp[i]=='='||sequence_cp[i]=='<'||sequence_cp[i]=='>'
        ||compareString(toString(sequence_cp[i],"=\0"),">=\0")
        ||compareString(toString(sequence_cp[i],"=\0"),"<=\0")
        ||compareString(toString(sequence_cp[i],">\0"),"<>\0")
        )
        {
            int j = i;
            int l = 0;
            while (sequence_cp[i]=='='||sequence_cp[i]=='<'||sequence_cp[i]=='>'
            ||compareString(toString(sequence_cp[i],"=\0"),">=\0")
            ||compareString(toString(sequence_cp[i],"=\0"),">=\0")
            ||compareString(toString(sequence_cp[i],">\0"),"<>\0")){
                part[l] = sequence_cp[j];
                j--;
                l++;
            }
            part[l]='\0';
            invertString(part);
            DEBUG3{printf("partRO:%s-\n", part);}

            if (isRO(part)){
                tokens=insertFifo(tokens,part,"RO\0",current_line,curr_sentence,"NO\0");
            }
            else{
                tokens=insertFifo(tokens,part,"ID\0",current_line,curr_sentence,"YES\0");
            }
            i = i-l-1;
        }
        else{
            // DEBUG3{printf("-%d-\n", sequence_cp[i]);}
            programErrorMessageAnaLex(current_line);
            tokens = insertFifo(tokens,part,"ERRO\0",current_line,curr_sentence,"YES\0");
            i=i-1;
        }
        part[0]='\0';
        acc_adress++;
    }
    free(part);

    showTokens(tokens);

    return 0;
}