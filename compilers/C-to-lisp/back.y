// Adam Kaawach, Gabriel Ortega, grupo 59
// 100438770@alumnos.uc3m.es 100472219@alumnos.uc3m.es


%{                          // SECCION 1 Declaraciones de C-Yacc

#include <stdio.h>
#include <ctype.h>            // declaraciones para tolower
#include <string.h>           // declaraciones para cadenas
#include <stdlib.h>           // declaraciones para exit ()

#define FF fflush(stdout);    // para forzar la impresion inmediata

int yylex () ;
int yyerror(char *mensaje);
char *my_malloc (int) ;
char *gen_code (char *) ;
char *int_to_string (int) ;
char *char_to_string (char) ;
void insert_space(char *input) ;

char temp [2048] ;

// Definitions for explicit attributes

typedef struct s_attr {
    int value ;    // - Numeric value of a NUMBER 
    char *code ;   // - to pass IDENTIFIER names, and other translations 

} t_attr ;

#define YYSTYPE t_attr     // stac

%}

// Definitions for explicit attributes

%token NUMBER        
%token IDENTIF       // Identificador=variable
%token STRING
%token MAIN          // identifica el comienzo del proc. main
%token PRINT
%token AND          // tokens logical
%token OR  
%token LEQ          // lesser or equal
%token GEQ          // greater or equal
%token NEQ          // NEQ
%token WHILE
%token IF
%token ELSE
%token FOR
%token RETURN
%token SETQ
%token SETF
%token DEFUN
%token VARIABLE
%token LOOP
%token DO
%token MOD
%token NOT
%token PROGN
%token PRIN1

%right '='                    
%left OR
%left AND
%left EQ NEQ
%left '<' LEQ '>' GEQ
%left '+' '-'                 
%left '/' '*' '%'                
%left UNARY_SIGN   

%%

axiom:  outer_sentence  { printf("%s\n", $1.code); };

outer_sentence
    : variable_declaration outer_sentence 
    {
        sprintf(temp, "%s\n%s", $1.code, $2.code); 
        $$.code = gen_code(temp);
    }
    | variable_assignation outer_sentence 
    {
        sprintf(temp, "%s\n%s", $1.code, $2.code);  
        $$.code = gen_code(temp);
    }
    | function outer_sentence 
    {
        sprintf(temp, "%s\n%s", $1.code, $2.code); 
        $$.code = gen_code(temp);
    }
    | main
    {
        sprintf(temp, "%s", $1.code);
        $$.code = gen_code(temp);
    }
    | /* empty */
    {
        $$.code = gen_code("");
    }
    ;

main: '(' DEFUN MAIN '(' ')' inner_sentence ')' 
    {
        sprintf(temp, ": main\n%s\n;", $6.code);  
        $$.code = gen_code(temp);
    }
    ;

function
    : '(' DEFUN IDENTIF '(' ')' inner_sentence ')' 
    {
        sprintf(temp, ": %s\n%s\n;", $3.code, $6.code);
        $$.code = gen_code(temp);
    }
    ;

inner_sentence
    : statement
    {
        sprintf(temp, "%s", $1.code);  
        $$.code = gen_code(temp);
    }
    |  statement inner_sentence
    {
        sprintf(temp, "%s%s", $1.code, $2.code);  
        $$.code = gen_code(temp);
    }
    ;

statement
    : variable_assignation   { $$.code = gen_code($1.code);}
    | print  { $$.code = gen_code($1.code);}
    | while  { $$.code = gen_code($1.code);}
    | conditional  { $$.code = gen_code($1.code);}
    ;


while: '(' LOOP WHILE logical_expression DO inner_sentence ')' 
    {
        sprintf(temp, "begin \n\t%swhile\n\t%s\nrepeat\n;", $6.code, $4.code);  
        $$.code = gen_code(temp);
    }
    ;

conditional: '(' IF logical_expression  if_block else_block  ')'
    { sprintf(temp, "%s if %s %s then", $3.code, $4.code, $5.code);
     $$.code = gen_code(temp); }
    ;

if_block:  '(' PROGN inner_sentence ')'   
        { sprintf(temp, "\n%s\n", $3.code); 
                $$.code = gen_code(temp);}
        | statement   
        { 
            sprintf(temp, "\n%s\n", $1.code); 
            $$.code = gen_code(temp); 
        }
        ;

else_block:  '(' PROGN inner_sentence ')'   
        { sprintf(temp, "\nelse %s\n", $3.code); 
                $$.code = gen_code(temp);}
        | statement   
        { 
            sprintf(temp, "\nelse %s\n", $1.code); 
            $$.code = gen_code(temp); 
            }
        | /* empty */
        { 
            $$.code = gen_code(""); 
        }
        ;


print
    : '(' PRINT STRING ')' 
    {
        char modified_string[64];
        strcpy(modified_string, $3.code);
        insert_space(modified_string); 
        sprintf(temp, ".%s\n", modified_string);  
        $$.code = gen_code(temp);
    }
    |
    '(' PRINT expression ')' 
    {
        sprintf(temp, "%s .\n", $3.code);  
        $$.code = gen_code(temp);
    }
    | '(' PRIN1 expression ')'
    {
        sprintf(temp, "%s .\n", $3.code);  
        $$.code = gen_code(temp);
    }
    | '(' PRIN1 STRING ')'
    {
        char modified_string[64];
        strcpy(modified_string, $3.code);
        insert_space(modified_string); 
        sprintf(temp, "%s .\n", modified_string);  
        $$.code = gen_code(temp);
    }
    ;




variable_declaration
    : '(' SETQ IDENTIF expression ')' 
    {

        sprintf(temp, "variable %s\n%d %s !\n", $3.code, $4.value, $3.code); 
        $$.code = gen_code(temp);
    }

    ;

variable_assignation
    : '(' SETF IDENTIF expression ')' 
    {
        sprintf(temp, "%s %s !\n", $4.code, $3.code);  
        $$.code = gen_code(temp);
    }
    ;

expression: term 
    {
        $$.code = $1.code;
    }
    | '(' '+' expression expression ')' 
    {
        sprintf(temp, "%s %s +", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' '-' expression expression ')' 
    {
        sprintf(temp, "%s %s -", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' '*' expression expression ')' 
    {
        sprintf(temp, "%s %s *", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' '/' expression expression ')' 
    {
        sprintf(temp, "%s %s /", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' MOD expression expression ')' 
    {
        sprintf(temp, "%s %s mod", $3.code, $4.code);
        $$.code = gen_code(temp);
    }

logical_expression: term
    {
        $$.code = $1.code;
    }
    | '(' AND logical_expression logical_expression ')' 
    {
        sprintf(temp, "%s %s and", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' OR logical_expression logical_expression ')' 
    {
        sprintf(temp, "%s %s or", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' '=' logical_expression logical_expression ')' 
    {
        sprintf(temp, "%s %s =", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' NEQ logical_expression logical_expression ')' 
    {
        sprintf(temp, "%s %s = 0=", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' '<' logical_expression logical_expression ')' 
    {
        sprintf(temp, "%s %s <", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' '>' logical_expression logical_expression ')' 
    {
        sprintf(temp, "%s %s >", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' LEQ logical_expression logical_expression ')' 
    {
        sprintf(temp, "%s %s <=", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' GEQ logical_expression logical_expression ')' 
    {
        sprintf(temp, "%s %s >=", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' NOT logical_expression logical_expression ')' 
    {
        sprintf(temp, "%s %s 0=", $3.code, $4.code);
        $$.code = gen_code(temp);
    }
    | '(' '=' '(' MOD expression expression ')' expression ')' 
    {
        sprintf(temp, "%s %s mod %s =", $4.code, $5.code, $8.code);
        $$.code = gen_code(temp);
    }
    ;
    


term:         operand                        { $$ = $1 ; }                          
            | '+' operand %prec UNARY_SIGN   { sprintf (temp, "+%s", $2.code) ;
                                               $$.code = gen_code (temp) ; }
            | '-' operand %prec UNARY_SIGN   { sprintf (temp, "-%s", $2.code) ;
                                               $$.code = gen_code (temp) ; }    
            ;

operand:      IDENTIF                        { sprintf (temp, "%s @", $1.code);
                                                  
                                                $$.code = gen_code (temp) ; }
            | NUMBER                         { sprintf (temp, "%d", $1.value) ;
                                               $$.code = gen_code (temp) ; }
            ;

%%

              // SECCION 4    Codigo en C

int n_line = 1 ;

void insert_space(char *input) {
    int length = strlen(input);
    if (length > 0 && input[0] == '"') {
        memmove(input + 2, input + 1, length - 1 + 1); 
        input[1] = ' ';
    }
}



int yyerror(char *mensaje)
{
    fprintf (stderr, "%s en la linea %d", mensaje, n_line) ;
    printf ( "\n") ;	// bye
    return 0;
}

char *int_to_string(int n)
{
    sprintf (temp, "%d", n) ;
    return gen_code (temp) ;
}

char *char_to_string(char c)
{
    sprintf (temp, "%c", c) ;
    return gen_code (temp) ;
}

char *my_malloc(int nbytes)       // reserva n bytes de memoria dinamica
{
    char *p ;
    static long int nb = 0;        // sirven para contabilizar la memoria
    static int nv = 0 ;            // solicitada en total

    p = malloc (nbytes) ;
    if (p == NULL) {
        fprintf (stderr, "No queda memoria para %d bytes mas\n", nbytes) ;
        fprintf (stderr, "Reservados %ld bytes en %d llamadas\n", nb, nv) ;
        exit (0) ;
    }
    nb += (long) nbytes ;
    nv++ ;

    return p ;
}


/***************************************************************************/
/********************** Seccion de Palabras Reservadas *********************/
/***************************************************************************/

typedef struct s_keyword { // para las palabras reservadas de C
    char *name ;
    int token ;
} t_keyword ;

t_keyword keywords [] = { // define las palabras reservadas y los
    "main",        MAIN,           // y los token asociados
    "print",      PRINT,      
    "setq",        SETQ,
    "setf",         SETF,
    "defun",       DEFUN,
    "variable",    VARIABLE,
    "loop",        LOOP,
    "and",          AND,
    "or",            OR,
    "<=",           LEQ,
    ">=",           GEQ,
    "while",       WHILE,
    "do",          DO,
    "/=",         NEQ,
    "mod",       MOD,
    "not",       NOT,
    "progn",    PROGN,
    "if",           IF,
    "prin1",         PRIN1,
    NULL,          0               // para marcar el fin de la tabla
} ;

t_keyword *search_keyword(char *symbol_name)
{                                  // Busca n_s en la tabla de pal. res.
                                   // y devuelve puntero a registro (simbolo)
    int i ;
    t_keyword *sim ;

    i = 0 ;
    sim = keywords ;
    while (sim [i].name != NULL) {
	    if (strcmp (sim [i].name, symbol_name) == 0) {
		                             // strcmp(a, b) devuelve == 0 si a==b
            return &(sim [i]) ;
        }
        i++ ;
    }

    return NULL ;
}

 
/***************************************************************************/
/******************* Seccion del Analizador Lexicografico ******************/
/***************************************************************************/

char *gen_code(char *name)     // copia el argumento a un
{                                      // string en memoria dinamica
    char *p ;
    int l ;
	
    l = strlen (name)+1 ;
    p = (char *) my_malloc (l) ;
    strcpy (p, name) ;
	
    return p ;
}


int yylex ()
{
    int i ;
    unsigned char c ;
    unsigned char cc ;
    char ops_expandibles [] = "!<=>|%/&+-*" ;
    char temp_str [256] ;
    t_keyword *symbol ;

    do {
        c = getchar () ;

        if (c == '#') {	// Ignora las lineas que empiezan por #  (#define, #include)
            do {		//	OJO que puede funcionar mal si una linea contiene #
                c = getchar () ;
            } while (c != '\n') ;
        }

        if (c == '/') {	// Si la linea contiene un / puede ser inicio de comentario
            cc = getchar () ;
            if (cc != '/') {   // Si el siguiente char es /  es un comentario, pero...
                ungetc (cc, stdin) ;
            } else {
                c = getchar () ;	// ...
                if (c == '@') {	// Si es la secuencia //@  ==> transcribimos la linea
                    do {		// Se trata de codigo inline (Codigo embebido en C)
                        c = getchar () ;
                        putchar (c) ;
                    } while (c != '\n') ;
                } else {		// ==> comentario, ignorar la linea
                    while (c != '\n') {
                        c = getchar () ;
                    }
                }
            }
        } else if (c == '\\') c = getchar () ;
		
        if (c == '\n')
            n_line++ ;

    } while (c == ' ' || c == '\n' || c == 10 || c == 13 || c == '\t') ;

    if (c == '\"') {
        i = 0;
        temp_str[i++] = '\"'; // añadir la commilla inicial
        do {
            c = getchar();
            temp_str[i++] = c;
        } while (c != '\"' && i < 254); // dejando espacio para la commilla final
        if (i == 255) {
            printf("AVISO: string con mas de 255 caracteres en linea %d\n", n_line);
           temp_str[i-1] = '\"'; // añadir comilla final si se llega al límite de tamaño
        } else if (c != '\"') {
            temp_str[i-1] = '\"'; // añadir comilla final si no está presente
        }
        temp_str[i] = '\0';
        yylval.code = gen_code(temp_str);
        return (STRING);
    }

    if (c == '.' || (c >= '0' && c <= '9')) {
        ungetc (c, stdin) ;
        scanf ("%d", &yylval.value) ;
//         printf ("\nDEV: NUMBER %d\n", yylval.value) ;        // PARA DEPURAR
        return NUMBER ;
    }

    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        i = 0 ;
        while (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') || c == '_') && i < 255) {
            temp_str [i++] = tolower (c) ;
            c = getchar () ;
        }
        temp_str [i] = '\0' ;
        ungetc (c, stdin) ;

        yylval.code = gen_code (temp_str) ;
        symbol = search_keyword (yylval.code) ;
        if (symbol == NULL) {    // no es palabra reservada -> identificador antes vrariabre
//               printf ("\nDEV: IDENTIF %s\n", yylval.code) ;    // PARA DEPURAR
            return (IDENTIF) ;
        } else {
//               printf ("\nDEV: OTRO %s\n", yylval.code) ;       // PARA DEPURAR
            return (symbol->token) ;
        }
    }

    if (strchr (ops_expandibles, c) != NULL) { // busca c en ops_expandibles
        cc = getchar () ;
        sprintf (temp_str, "%c%c", (char) c, (char) cc) ;
        symbol = search_keyword (temp_str) ;
        if (symbol == NULL) {
            ungetc (cc, stdin) ;
            yylval.code = NULL ;
            return (c) ;
        } else {
            yylval.code = gen_code (temp_str) ; // aunque no se use
            return (symbol->token) ;
        }
    }

//    printf ("\nDEV: LITERAL %d #%c#\n", (int) c, c) ;      // PARA DEPURAR
    if (c == EOF || c == 255 || c == 26) {
//         printf ("tEOF ") ;                                // PARA DEPURAR
        return (0) ;
    }

    return c ;
}


int main ()
{
    yyparse () ;
}
