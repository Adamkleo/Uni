%{
#include <stdio.h>

int yylex(void);
int yyerror(char *s);
#define YYSTYPE int 

%}

%token ZERO
%token ONE

%%

axiom: sentence '\n' { printf("Zeroes = %d\n", $1); } axiom
        |    { ; }
    ;

sentence: number sentence 
        {  
            $$ = $1 + $2;
        }
        | number 
        { 
            $$ = $1;
        }
    ;

number: ZERO { $$ = 1; }
        | ONE { $$ = 0; }
%%

int main(int argc, char **argv) {
    yyparse();
    return 0;
}

int yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

int yylex(void) {
    char c;
    do {
        c = getchar();
    } while (c == ' ');

    if (c == '0') {
        return ZERO;
    } else if (c == '1') {
        return ONE;
    } else if (c == '\n') {
        return '\n';
    }
}