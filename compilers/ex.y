%{ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



int yyerror(char *mensaje);
int yylex();

typedef struct s_attr {
    int value;
    char *code;
} t_attr;

#define YYSTYPE t_attr

typedef struct {
    char varname[50];
    char scope[10];
    char type[5];
} VariableInfo;

// Array to store variable information
VariableInfo variables[100];
int currentSize = 0;

void insertVariable(const char *varname, const char *scope, const char *type) {
    if (currentSize < 100) {
        snprintf(variables[currentSize].varname, sizeof(variables[currentSize].varname), "%s", varname);
        snprintf(variables[currentSize].scope, sizeof(variables[currentSize].scope), "%s", scope);
        snprintf(variables[currentSize].type, sizeof(variables[currentSize].type), "%s", type);
        currentSize++;
    } else {
        printf("Error: Variable storage is full.\n");
    }
}



%}

%token ID
%token NUMBER
%token NUM LOG

%left '+' '-'
%left '*' '/'

%%

axiom:
    | axiom statement '\n'
    ;

statement:
      type id_list ';' 
    | ID '=' expression ';'
    ;

id_list:
      ID { insertVariable($1.code, "global", $-1.code); }
    | id_list ',' ID { insertVariable($3.code, "global", $-1.code); }
    ;


type:
      NUM  { $$.code = $1.code; }
    | LOG  { $$.code = $1.code; }
    ;

expression:
      expression '+' term 
    | expression '-' term
    | expression '*' term
    | expression '/' term
    | term
    ;

term:
      ID
    | NUMBER
    ;

%%

int yyerror (char *mensaje) {
	fprintf (stderr, "%s\n", mensaje) ;
}

int yylex() {
    unsigned char c;
    char buffer[100];  
    int buf_index = 0;
    int valor;

    
    do {
        c = getchar();
    } while (c == ' ');

    
    if (isdigit(c)) {
        ungetc(c, stdin);
        scanf("%d", &valor);
        yylval.value = valor;
        return NUMBER;
    }

    
    if (isalpha(c)) {
        do {
            buffer[buf_index++] = c;
            if (buf_index >= 99) break; 
            c = getchar();
        } while (isalpha(c) || isdigit(c) || c == '_');  
        ungetc(c, stdin);  

        buffer[buf_index] = '\0';  

        if (strcmp(buffer, "num") == 0) {
            yylval.code = strdup(buffer);
            return NUM;  
        } else if (strcmp(buffer, "log") == 0) {
            yylval.code = strdup(buffer);
            return LOG;  
        }

        yylval.code = strdup(buffer);
        return ID;
    }


    
    return c;
}


int main () { 
	yyparse () ;
        for (int i = 0; i < currentSize; i++) {
        printf("Variable %d: %s, Scope: %s, Type: %s\n",
               i+1, variables[i].varname, variables[i].scope, variables[i].type);
    }

}