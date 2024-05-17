%{ 

#include <stdio.h>
#define YYSTYPE int
int yyerror(char *mensaje);
int yylex();

%}

%%
axiom: '\n' { ; } | lines { printf("%d\n", $1); } '\n' axiom; 
	;

lines: line lines { $$ = $1 + $2; }
    | line { $$ = $1; }

line: '(' list ')' { $$ = 1 + $2; } 
    ;

list:  line list { $$ = $1 + $2; }
    |  { $$ = 0; }
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
	return c ;
}

int main () { 
	yyparse () ;
}