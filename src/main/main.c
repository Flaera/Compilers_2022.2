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
#define DEBUG3 if(0)


//classes of globals tokens
char PR[23][BIG_INT] = {
    "program\0", "if\0", "then\0", "else\0",
    "integer\0", "real\0", "boolean\0",
    "var:\0", "f\0", "fifo_of_integer\0", "fifo_of_real\0",
    "procedure\0", "function\0",
    "concatena_fifo\0", "inverte_fifo\0",
    "write\0", "read\0",
    "for\0", "to\0", "do\0", "repeat\0", "until\0", "while\0" 
};
char DS[8][2] = {
    ";\0",".\0",",\0","(\0",")\0","[\0","]\0", "#\0"
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
        new_node->next = NULL;
        if(fifo==NULL){
            fifo = new_node;
            // acc_adress++;
        }
        else{
            Node *aux = fifo;
            fifo = aux;
            while (aux->next!=NULL){
                acc+=1;
                aux = aux->next;
            }
            aux->next = new_node;
            // acc_adress++;
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
    for (int i=0; i<8; ++i){
        if (compareString(str,DS[i])){return 1;}
    }
    return 0;
}


int isPR(char str[]){
    for (int i=0; i<23; ++i){
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


int isDIGITO(char str[]){
    for (int i=0; i<10; ++i){
        if (compareString(str, DIGITO[i])){return 1;}
    }
    return 0;
}


int isDIGIT(char str[]){
    for (int i=0; i<9; ++i){
        if (compareString(str, DIGIT[i])){return 1;}
    }
    return 0;
}


int isBoolean(char str[]){
    for (int i=0; i<3; ++i){
        if (compareString(str, VALUES_BOLLEAN[i])){return 1;}
    }
    return 0;
}


int isID(char str[]){
    int i=0;
    while (str[i]!='\0'){
        if (!(str[i]>=97 && str[i]<=122)){return 0;}
        i++;
    }
    return 1;
}


void showTokens(Node* tokens){
    printf("TOKENS FIFO:\n");
    Node* aux = tokens;
    
    while (aux!=NULL){
        if (aux->error[0]=='N'){
            printf("## valor:%s|tipo:%s|endereco:%d|linha:%d|sentenca:%d ##\n",
                aux->value, aux->type,
                aux->adress, aux->line, aux->sentence);
        }
        aux = aux->next;
    }

    aux = tokens;
    while (aux!=NULL){
        if (aux->error[0]=='Y'){
            printf("## valor:%s|tipo:%s|endereco:%d|linha:%d|sentenca:%d ## | ERRO! \n",
                aux->value, aux->type,
                aux->adress, aux->line, aux->sentence);
        }
        aux = aux->next;
    }

    free(aux);
}


int tokenzingErrorChecker(Node* tokens){
    printf("TOKENS FIFO ERRORS:\n");
    Node* aux = tokens;
    int error = 0;
    while (aux!=NULL){
        if (aux->error[0]=='Y'){
            printf("## valor:%s|tipo:%s|endereco:%d|linha:%d|sentenca:%d ERROR ##\n",
                aux->value, aux->type,
                aux->adress, aux->line, aux->sentence);
            error=1;
        }
        aux = aux->next;
    }
    return error;
}


Node* tokenzing(Node* tokens, char* sequence_cp, int acc){
    int current_line = 0;
    int curr_sentence = 0;
    char* part = malloc(BIG_INT);
    int i = acc-2;
    while (i>=0){
        DEBUG3{printf("sequence:%c-%d\n", sequence_cp[i], sequence_cp[i]);}
        if (sequence_cp[i]=='\n'){current_line++;}
        if (sequence_cp[i]==';'){curr_sentence++;}

        int j = i;
        int l = 0;
        // while ((sequence_cp[j]>=97 && sequence_cp[j]<=122)){
        while ((sequence_cp[j]>=INIT && sequence_cp[j]<=END) && 
            (sequence_cp[j]>32 && sequence_cp[j]!=';') && sequence_cp[j]!='\t'
            && (sequence_cp[j]!='(' && sequence_cp[j]!=')')){
            part[l] = sequence_cp[j];
            j--;
            l++;
        }
        part[l]='\0';
        invertString(part);
        DEBUG3{printf("partGENERAL:%s-\n", part);}


        if (sequence_cp[i]==';' || sequence_cp[i]==',' || sequence_cp[i]=='.'
         || sequence_cp[i]=='(' || sequence_cp[i]==')' || sequence_cp[i]=='['
          || sequence_cp[i]==']' || sequence_cp[i]=='#'){
            part[0]=sequence_cp[i];part[1]='\0';
            DEBUG3{printf("partDS:%s-\n", part);}
            tokens=insertFifo(tokens,part,"DS\0",current_line,curr_sentence,"NO\0");
            i--;
            acc_adress++;
        }
        else if (sequence_cp[i]=='f' && sequence_cp[i-1]>=48 && sequence_cp[i-1]<=57){
            part[0]='f';
            part[1]='\0';
            tokens=insertFifo(tokens,part,"PR\0",current_line,curr_sentence,"NO\0");
            i--;
            acc_adress++;
        }
        else if (isID(part)){
            DEBUG3{printf("partPR-BOOLEAN-DC-ID:%s-\n", part);}

            if (isPR(part)){
                tokens=insertFifo(tokens,part,"PR\0",current_line,curr_sentence,"NO\0");
            }
            else if (isBoolean(part)){
                tokens=insertFifo(tokens,part,"BOOLEAN\0",current_line,curr_sentence,"NO\0");
            }
            else if (isDC(part)){
                tokens=insertFifo(tokens,part,"DC\0",current_line,curr_sentence,"NO\0");
            }
            else if (sequence_cp[i]=='\n' || sequence_cp[i]==' '){
                // part[0]=sequence_cp[i];
                // part[1]='\0';
                // tokens=insertFifo(tokens,part,"DS\0",current_line,curr_sentence,"NO\0");
                i--;
                continue;
            }
            else {
                tokens=insertFifo(tokens,part,"ID\0",current_line,curr_sentence,"NO\0");
            }
            i = i-l-1;
            acc_adress++;
        }
        else if (sequence_cp[i]==':' && sequence_cp[i-1]=='r' && sequence_cp[i-2]=='a'
         && sequence_cp[i-3]=='v'){
            part[0] = 'v';
            part[1] = 'a';
            part[2] = 'r';
            part[3] = ':';
            part[4] = '\0';
            DEBUG3{printf("partPRvar:%s-\n", part);}
            tokens=insertFifo(tokens,part,"PR\0",current_line,curr_sentence,"NO\0");
            i = i-4;
            acc_adress++;
        }
        else if (sequence_cp[i]==37||sequence_cp[i]==42
            ||sequence_cp[i]==43
            ||sequence_cp[i]==45
            ||sequence_cp[i]==47
            ||(sequence_cp[i]=='/' && sequence_cp[i-1]=='/')
            ||(sequence_cp[i]=='=' && sequence_cp[i-1]==':')){
            int j = i;
            int l = 0;
            part[l]=sequence_cp[j];
            l++;
            j--;
            if ((sequence_cp[i]=='/' && sequence_cp[i-1]=='/')
            ||(sequence_cp[i]=='=' && sequence_cp[i-1]==':')){
                part[l]=sequence_cp[i-1];
                l++;
                j--;
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
            acc_adress++;
        }
        else if (sequence_cp[i]=='='||sequence_cp[i]=='<'||sequence_cp[i]=='>'
        ||(sequence_cp[i]=='=' && sequence_cp[i-1]=='>')
        ||(sequence_cp[i]=='=' && sequence_cp[i-1]=='<')
        ||(sequence_cp[i]=='>' && sequence_cp[i-1]=='<'))
        {
            int j = i;
            int l = 0;
            part[l] = sequence_cp[i];
            l++;
            j--;
            if ((sequence_cp[i]=='=' && sequence_cp[i-1]=='>')
            ||(sequence_cp[i]=='=' && sequence_cp[i-1]=='<')
            ||(sequence_cp[i]=='>' && sequence_cp[i-1]=='<')){
                part[l] = sequence_cp[i-1];
                j--;
                l++;
            }
            part[l]='\0';
            invertString(part);
            DEBUG3{printf("partRO:%s-\n", part);}

            tokens=insertFifo(tokens,part,"RO\0",current_line,curr_sentence,"NO\0");
            i = i-l-1;
            acc_adress++;
        }
        else if (sequence_cp[i]>=48 && sequence_cp[i]<=57){
            int j = i;
            int l = 0;
            while ((sequence_cp[j]>=48 && sequence_cp[j]<=57)){
                part[l] = sequence_cp[j];
                j--;
                l++;
            }
            part[l]='\0';
            invertString(part);
            if (isDIGITO(part)){
                tokens=insertFifo(tokens,part,"DIGITO\0",current_line,curr_sentence,"NO\0");
            }
            else if (isDIGIT(part)){
                tokens=insertFifo(tokens,part,"DIGIT\0",current_line,curr_sentence,"NO\0");
            }
            i=i-l;
            acc_adress++;
        }
        else{
            DEBUG3{printf("partERROR:%s-%d-\n", part, i);}
            // programErrorMessageAnaLex(current_line);
            tokens = insertFifo(tokens,part,"ERRO\0",current_line,curr_sentence,"YES\0");
            i=i-l-1;
            acc_adress++;
        }
        part[0]='\0';
    }
    free(part);

    return tokens;
}


typedef struct tree{
    Node node_infos;
    int error;
    Node* next[BIG_INT];
} Tree;


int aSLRTopDownRight(Node* token, Tree* treeAS){
    //Tracking:
    //Rules of production:
    int error = 0;
    int acc = 0;
    if (compareString(*token->value, "program\0" && token!=NULL)){
        treeAS->node_infos = *token; // a palavra reservada "program"
        if (compareString((token->next)->type, "ID\0")){
            treeAS->next[acc]=token->next; // o que deveria ser o nome ou id
            acc++;
        }
        else{error=1;}
        if (compareString((token->next)->next->type, "DS\0")){
            // o ponto e virgula
            treeAS->next[acc]=(token->next)->next;
            acc++;
        }
        else{error=1;}
        treeAS->next[acc]=NULL;
        acc++;
        treeAS->error=0;
        if (token!=NULL){aSLRTopDownRight(treeAS->next[acc], treeAS);}
    }
    else if (compareString(*token->value, "begin\0")){
        if(token!=NULL){aSLRTopDownRight(treeAS->next[acc+1], treeAS);}
    }
    else if (compareString(*token->value,"var:\0")){
        treeAS->node_infos = *token;
        if (compareString(*token->next->type,"PR\0")){
            treeAS->next[acc] = token->next;
            acc++;
            if ((compareString(*token->next->next->type,"PR\0"))
             || (compareString(*token->next->next->type,"ID\0"))){
                treeAS->next[acc] = token->next->next;
                acc++;
                if (compareString(*token->next->next->type,"ID\0")
                && ((compareString(*token->next->next->next->type,"DS\0"))
                || (compareString(*token->next->next->next->type,"PR\0")))){
                    treeAS->next[acc] = token->next->next->next;
                    acc++;
                }
                else{error=1;}
            }
            else{error=1;}
        }else{error=1;}
        if (token!=NULL){aSLRTopDownRight(treeAS->next[acc], treeAS);}
    }else{error=1;}

    //Backtracking:
    if (error==1) {
        treeAS->error=1;
    }
    return 0;
}


int main(){
    printf("Lendo script...\n");
    DEBUG0{printf("Before fgets or getchar()\n");}
    char sequence_cp[BIG_INT];
    int acc = 0;
    do{
        sequence_cp[acc]=(char)getchar();
        DEBUG0{printf("-acc:%d|%c-", acc, sequence_cp[acc]);}
        acc+=1;
    }
    while ((sequence_cp[acc-1]>=INIT && sequence_cp[acc-1]<=END) || (sequence_cp[acc-1]==SPACE));
    sequence_cp[acc-1]='\0';
    printf("Script lido. Script:\n");
    printf("%s\n", sequence_cp);
    printf("----\n");

    //Tokenzing with fifo:
    Node* tokens = malloc(sizeof(Node));
    tokens = tokenzing(tokens, sequence_cp, acc);
    
    showTokens(tokens);
    int error = tokenzingErrorChecker(tokens);
    if (error==1){
        printf("LEXIC ERROR FINDED!\n");
    }
    else{
        printf("Analizing lexic complete no errors.\n");

        Tree *treeAS = malloc(sizeof(Tree));
        aSLRTopDownRight(tokens, treeAS);

        free(treeAS);
    }

    free(tokens);
    
    return 0;
}