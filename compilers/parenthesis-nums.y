%{ 

#include <stdio.h>
#define YYSTYPE int
int yyerror(char *mensaje);
int yylex();

%}

%token NUMBER

%%

axiom: '\n' { ; } | lines { printf("%d\n", $1); } '\n' axiom; 
	;

lines: line lines { $$ = $1 + $2; }
    | line { $$ = $1; }

line: '(' list ')' { $$ = $2; }
    ;

list:  line list { $$ = $1 + $2; }
    |  { $$ = 0; }
    | NUMBER { $$ = $1; }
    ;

%%

int yyerror (char *mensaje) {
	fprintf (stderr, "%s\n", mensaje) ;
}




int yylex () {
	unsigned char c ;
	int valor ;
	do {
		c = getchar () ;
	} while (c == ' ') ;



    if (c >= '0' && c <= '9') {
        ungetc(c, stdin);
        scanf("%d", &valor);
        yylval = valor;
        return (NUMBER);
    }

    return c;
}

int main () { 
	yyparse () ;
}