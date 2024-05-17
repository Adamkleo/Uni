%{ 

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>  // For character checks

#define YYSTYPE int
int yyerror(char *mensaje);
int yylex();

#define Tint 1
#define Treal 2

typedef struct s_attr {
  int int_val;
  double real_val;
  int type;
} t_attr;

#define YYSTYPE t_attr

%}


%token INTEGER
%token REAL

%%

axiom: '\n' { ; } | expression 
        { if ($1.type == Tint) {
            printf("Result: %d\n", $1.int_val);
        } else {
            printf("Result: %lf\n", $1.real_val);
        }
        
        }
         '\n' axiom;
	;

expression: number { $$ = $1; }
        | number '+' expression {
             if ($1.type == Tint && $3.type == Tint) {
                $$.type = Tint;
                $$.int_val = $1.int_val + $3.int_val;
            } else  if ($1.type == Treal && $3.type == Treal) {
                $$.type = Treal;
                $$.real_val = $1.real_val + $3.real_val ;
            } else if ($1.type == Tint && $3.type == Treal) {
                $$.type = Treal;
                $$.real_val = (double) $1.int_val + $3.real_val;
            } else  if ($1.type == Treal && $3.type == Tint) {
                $$.type = Treal;
                $$.real_val = $1.real_val + (double) $3.int_val;
            } 
            }


number: REAL { $$.real_val = $1.real_val;
                $$.type = Treal; }
        | INTEGER { $$.int_val = $1.int_val;
                $$.type = Tint; }
    ;
%%

int yyerror (char *mensaje) {
	fprintf (stderr, "%s\n", mensaje) ;
}

int yylex () {
	unsigned char c ;
  unsigned char str[256];
  int int_val;
  double real_val;
  
	do {
		c = getchar () ;
	} while (c == ' ') ;


  if (c >= '0' && c <= '9') {
    ungetc(c, stdin);
    scanf("%s", str);
    if (strchr(str, '.') != NULL) {
      sscanf(str, "%lf", &real_val);
      yylval.real_val = real_val;
      return (REAL);
    } else {
        sscanf(str, "%d", &int_val);
        yylval.int_val = int_val;
        return (INTEGER);
    }
  }
  return c;
}

int main () { 
	yyparse () ;
}


