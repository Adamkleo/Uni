// Adam Kaawach, Gabriel Ortega, grupo 59
// 100438770@alumnos.uc3m.es 100472219@alumnos.uc3m.es


%{                          // SECTION 1 Declarations for C-Bison
#include <stdio.h>
#include <ctype.h>            // tolower()
#include <string.h>           // strcmp() 
#include <stdlib.h>           // exit()

#define FF fflush(stdout);    // to force immediate printing 
#define MAX_LOCAL_VARS 100
#define MAX_LOCAL_VAR_NAME 50

int yylex();
void yyerror(char *message);
char *my_malloc(int);
char *gen_code(char *);
char *int_to_string(int);
char *char_to_string (char) ;
void print_output(char *s);
char temp [2048] ;
char vars[MAX_LOCAL_VARS][MAX_LOCAL_VAR_NAME];
int varCount = 0;

char current_function[32];

typedef struct s_attr {
    int value ;    // - Numeric value of a NUMBER 
    char *code ;   // - to pass IDENTIFIER names, and other translations 
    int multi;     // - Indicates if there are multiple sentences in a block
} t_attr ;

#define YYSTYPE t_attr     // stack of PDA has type t_attr



int contains_multiple_prints(const char* code) {
    int count = 0;
    const char* substring = "(prin1";

    // Check how many times "(prin1" appears in the string
    const char* tmp = code;
    while ((tmp = strstr(tmp, substring)) != NULL) {
        count++;
        tmp += strlen(substring);  // Move past the current found substring
    }

    // More than one prin1 call means it's a multi-print
    return count > 1;
}

void declareLocalVar(const char* varName) {
    strcpy(vars[varCount++], varName);
}

int isLocalVarDeclared(const char* varName) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i], varName) == 0) {
            return 1;
        }
    }
    return 0;
}

void clearLocalVars() {
    varCount = 0;
}


%}

// Definitions for explicit attributes

%token NUMBER        
%token IDENTIF       // Identificador=variable
%token INTEGER       // identifica el tipo entero
%token STRING
%token MAIN          // identifica el comienzo del proc. main
%token PUTS
%token PRINTF
%token AND          // tokens logical
%token OR  
%token LEQ          // lesser or equal
%token GEQ          // greater or equal
%token EQ           // EQ
%token NEQ          // NEQ
%token WHILE
%token IF
%token ELSE
%token FOR
%token RETURN



%right '='                    
%left OR
%left AND
%left EQ NEQ
%left '<' LEQ '>' GEQ
%left '+' '-'                 
%left '*' '/' '%'                
%left UNARY_SIGN   

%%                            // Section 3 Grammar - Semantic Actions


axiom:      global_declarations  function_declarations  main_declaration  { ; }
    ;





/*------------ GLOBAL VARIABLES DECLARATION  ------------*/


global_declarations: /* lambda */ { $$.code = gen_code("") ; }
            | variable_declarations ';' global_declarations  { printf ("%s\n ", $1.code) ; }
    ;

variable_declarations: INTEGER variable_list { $$.code = gen_code ($2.code); }
    ;


variable_list: IDENTIF global_assign            
            { 
            sprintf (temp, "(setq %s %s)", $1.code, $2.code) ;
            $$.code = gen_code (temp) ; }
            
            |  IDENTIF global_assign ',' variable_list  
            { 
            sprintf (temp, "(setq %s %s) %s", $1.code, $2.code, $4.code) ;
            $$.code = gen_code (temp) ; }
            
            | IDENTIF '[' NUMBER ']' { sprintf (temp, "(setq %s (make-array %d))", $1.code, $3.value) ;
                                               $$.code = gen_code (temp) ; }
            
            ;
        
global_assign:  '=' NUMBER                    { sprintf (temp, "%d", $2.value) ;
                                               $$.code = gen_code (temp) ; }
            | /* lambda */                         { sprintf(temp, "0") ;
                                               $$.code = gen_code (temp) ;}
            ;


/*------------ MAIN FUNCTION  ------------*/

main_declaration: MAIN { strcpy(current_function, "main");} '(' ')' '{' function_body '}' 
            { 
              printf ("(defun main () %s)\n", $6.code) ;
              clearLocalVars();
            }
        ;




/*------------ FUNCTIONS BLOCK  ------------*/


function_declarations: IDENTIF { strcpy(current_function, $1.code);} '(' args ')' '{'function_body '}' function_declarations 
            {   printf ("(defun %s (%s) %s)\n", $1.code, $4.code, $7.code) ;
              clearLocalVars();  }

            | /* lambda */ 
            {  $$.code = gen_code("") ;  }
        ;


args:       INTEGER IDENTIF rest_args { sprintf (temp, "%s", $2.code) ;
                                               $$.code = gen_code (temp) ; }
            | /* lambda */ {  $$.code = gen_code("") ;  }
            ;

rest_args:  ',' INTEGER IDENTIF rest_args { sprintf (temp, "%s %s", $3.code, $4.code) ;
                                               $$.code = gen_code (temp) ; }
            | /* lambda */ {  $$.code = gen_code("") ;  }
            ;



function_body: sentence ';' function_body 
                { sprintf (temp, "%s %s", $1.code, $3.code) ;
                $$.code = gen_code (temp) ;     
                }
                
            | sentence ';' { sprintf (temp, "%s", $1.code) ;
                                               $$.code = gen_code (temp) ; }
            | loop function_body { sprintf (temp, "%s %s", $1.code, $2.code) ;
                                               $$.code = gen_code (temp) ; }
            | loop                  { sprintf (temp, "%s", $1.code) ;
                                               $$.code = gen_code (temp) ;}
            | conditional function_body { sprintf (temp, "%s %s", $1.code, $2.code) ;
                                               $$.code = gen_code (temp) ; }
            | conditional            { sprintf (temp, "%s", $1.code) ; 
                                                $$.code = gen_code (temp) ; }
            | RETURN expression ';' function_body     { sprintf (temp, "(return-from %s %s)", current_function, $2.code) ;
                                               $$.code = gen_code (temp) ; }
            | RETURN expression ';' { sprintf (temp, "%s", $2.code) ; 
                                        $$.code = gen_code (temp) ; }
            ;



/* ------------ LOOPS ------------ */

loop:       WHILE '(' expression ')' '{' loop_body '}' 
                { sprintf (temp, "(loop while %s do %s)", $3.code, $6.code) ;
                $$.code = gen_code (temp) ; }
            
            | FOR '(' local_assign ';' expression ';' local_assign ')' '{' loop_body '}' 
                { sprintf (temp, "%s (loop while %s do %s %s)",$3.code, $5.code, $10.code, $7.code) ;
                $$.code = gen_code (temp) ; }
            
            ;




loop_body:  sentence ';' loop_body { sprintf (temp, "%s %s", $1.code, $3.code) ;
                                               $$.code = gen_code (temp) ; }
            | sentence ';' { sprintf (temp, "%s", $1.code) ;
                                               $$.code = gen_code (temp) ; }
            | loop { sprintf (temp, "%s", $1.code) ;
                                               $$.code = gen_code (temp) ; }
            | loop loop_body { sprintf (temp, "%s %s", $1.code, $2.code) ;
                                               $$.code = gen_code (temp) ; }
            | conditional { sprintf (temp, "%s", $1.code) ;
                                               $$.code = gen_code (temp) ; }
            | conditional loop_body { sprintf (temp, "%s %s", $1.code, $2.code) ;
                                               $$.code = gen_code (temp) ; }
            | RETURN expression ';' loop_body { sprintf (temp, "(return-from %s %s)", current_function, $2.code) ; 
                                               $$.code = gen_code (temp) ; }
            | RETURN expression ';' { sprintf (temp, "(return-from %s %s)", current_function, $2.code) ; 
                                               $$.code = gen_code (temp) ; }
            ;



/* ------------ CONTROL FLOW ------------ */
/***********************************************************************
 *  Using the token IF and ELSE, we recognize the conditional structure
 *  We added an attribute that is 'multi' to indicate if there are multiple sentences
 *  in the block. Using the value of the multi attribute, we either print the sentences
 *  in alone or inside a progn block.
 ***********************************************************************/

conditional:
      IF '(' expression  ')' '{' conditional_body '}' rest_conditional
      {
          if ($6.multi || contains_multiple_prints($6.code)) {
              sprintf(temp, "(if %s (progn %s) %s)", $3.code, $6.code, $8.code);
          } else {
              sprintf(temp, "(if %s %s %s)", $3.code, $6.code, $8.code);
          }
        $$.code = gen_code(temp);
      }
    ;

rest_conditional: ELSE '{' conditional_body '}' 
      {
          if ($3.multi || contains_multiple_prints($3.code)) {
              sprintf(temp, "(progn %s)", $3.code);
          } else {
              sprintf(temp, "%s", $3.code);
          }
          $$.code = gen_code(temp);
      }
    | /* lambda */ { $$.code = gen_code(""); }
    ;
 

conditional_body:
      sentence ';' conditional_body 
      {
          sprintf(temp, "%s %s", $1.code, $3.code);
          $$.code = gen_code(temp);
          $$.multi = 1;  // Indicates multiple sentences
      }
    | sentence ';' 
      {
          sprintf(temp, "%s", $1.code);
          $$.code = gen_code(temp);
          $$.multi = 0;  // Indicates a single sentence
      }
    | conditional conditional_body 
      {
          sprintf(temp, "%s %s", $1.code, $2.code);
          $$.code = gen_code(temp);
          $$.multi = 1;  // Indicates multiple sentences
      }
    | conditional 
      {
          sprintf(temp, "%s", $1.code);
          $$.code = gen_code(temp);
          $$.multi = 0;  // Indicates a single sentence
      }
    | RETURN expression ';' conditional_body 
      {
          sprintf(temp, "(return-from %s %s)", current_function, $2.code);
          $$.code = gen_code(temp);
          $$.multi = 1;  // Indicates multiple sentences
      }
    | RETURN expression ';' 
      {
          sprintf(temp, "(return-from %s %s)", current_function, $2.code);
          $$.code = gen_code(temp);
          $$.multi = 0;  // Indicates a single sentence
      }
    | loop conditional_body 
      {
          sprintf(temp, "%s %s", $1.code, $2.code);
          $$.code = gen_code(temp);
          $$.multi = 1;  // Indicates multiple sentences
      }
    | loop 
      {
          sprintf(temp, "%s", $1.code);
          $$.code = gen_code(temp);
          $$.multi = 0;  // Indicates a single sentence
      }
    ;


/* ------------ SENTENCES, EXPRESSIONS, ... (used inside functions)  ------------ */

sentence:   local_var_declaration { sprintf (   temp, "%s", $1.code) ;
                                                $$.code = gen_code (temp) ;  }
                                                

            |  local_assign  { sprintf (temp, "%s", $1.code) ;
                                               $$.code = gen_code (temp) ; }

            | local_vector_assign  { sprintf (temp, "%s", $1.code) ;
                                               $$.code = gen_code (temp) ; }
                                               
            | PRINTF '(' STRING ',' print_list ')' { sprintf(temp, "%s", $5.code); 
                                                $$.code = gen_code(temp); }
            | PUTS '(' STRING ')'         { sprintf (temp, "(print \"%s\")", $3.code) ;
                                               $$.code = gen_code (temp) ; }      
            | function_call  { sprintf (temp, "%s", $1.code) ;
                                               $$.code = gen_code (temp) ; }
            
            ;


local_var_declaration: INTEGER local_var_list { $$.code = gen_code ($2.code); }
    ;

    
local_var_list: IDENTIF assign_content            
            { 
            sprintf (temp, "(setq %s_%s %s)", current_function, $1.code, $2.code) ;
            $$.code = gen_code (temp) ;  
            declareLocalVar($1.code); }
            
            |  IDENTIF assign_content ',' local_var_list  
            { 
            sprintf (temp, "(setq %s_%s %s) %s", current_function, $1.code, $2.code, $4.code) ;
            $$.code = gen_code (temp) ; 
            declareLocalVar($1.code);}
            
            | IDENTIF '[' NUMBER ']'  ',' local_var_list {  sprintf (temp, "(setq %s_%s (make-array %d)) %s", current_function, $1.code, $3.value, $6.code) ;
                                                            $$.code = gen_code (temp) ; 
                                                            declareLocalVar($1.code);}
            | IDENTIF '[' NUMBER ']' { sprintf (temp, "(setq %s_%s (make-array %d))", current_function, $1.code, $3.value) ;
                                               $$.code = gen_code (temp) ; 
                                               declareLocalVar($1.code);}
            ;


local_assign: IDENTIF assign_content {  if (isLocalVarDeclared($1.code)) sprintf (temp, "(setf %s_%s %s)", current_function, $1.code, $2.code);
                                        else sprintf (temp, "(setf %s %s)", $1.code, $2.code) ;
                                                $$.code = gen_code (temp) ; 
                                                                                              } 
                                               
            ;

local_vector_assign: vector_access assign_content { sprintf (temp, "(setf %s %s)", $1.code, $2.code) ;
                                               $$.code = gen_code (temp) ;}
            ;

vector_access: IDENTIF '[' expression ']' { if (isLocalVarDeclared($1.code)) sprintf (temp, "(aref %s_%s %s)", current_function, $1.code, $3.code);
                                               else sprintf (temp, "(aref %s %s)", $1.code, $3.code) ;
                                               $$.code = gen_code (temp) ; }
            ;

assign_content: '=' expression { sprintf (temp, "%s", $2.code) ;
                                               $$.code = gen_code (temp) ; }
            |  /* lambda */ { $$.code = gen_code ("0") ; }
            ;

function_call: IDENTIF '(' params ')' { sprintf (temp, "(%s %s)", $1.code, $3.code) ;
                                               $$.code = gen_code (temp) ; }
            ;

params:      STRING  { sprintf (temp, "\"%s\"", $1.code) ;
                                               $$.code = gen_code (temp) ; }
            | STRING ',' params { sprintf (temp, "\"%s\" %s", $1.code, $3.code) ;
                                               $$.code = gen_code (temp) ; }
            | expression { sprintf (temp, "%s", $1.code) ;
                                               $$.code = gen_code (temp) ; }
            | expression ',' params { sprintf (temp, "%s %s", $1.code, $3.code) ;
                                               $$.code = gen_code (temp) ; }
            | /* lambda */ { $$.code = gen_code("") ; }
            ;



print_list:   print_item                      {$$.code = gen_code($1.code);}
            | print_item ',' print_list         { sprintf(temp, "%s %s", $1.code, $3.code); 
                                                $$.code = gen_code(temp); }
            ;

print_item:   STRING { sprintf(temp, "(prin1 \"%s\")", $1.code);  
                        $$.code = gen_code(temp); }
            | expression { sprintf(temp, "(prin1 %s)", $1.code);   
                        $$.code = gen_code(temp); }
            ;



expression:   term                           { $$ = $1 ; }
            | expression '+' expression      { sprintf (temp, "(+ %s %s)", $1.code, $3.code) ;
                                               $$.code = gen_code (temp) ; }
            | expression '-' expression      { sprintf (temp, "(- %s %s)", $1.code, $3.code) ;
                                               $$.code = gen_code (temp) ; }
            | expression '*' expression      { sprintf (temp, "(* %s %s)", $1.code, $3.code) ;
                                               $$.code = gen_code (temp) ; }
            | expression '/' expression      { sprintf (temp, "(/ %s %s)", $1.code, $3.code) ;
                                               $$.code = gen_code (temp) ; }
            | expression '%' expression      { sprintf (temp, "(mod %s %s)", $1.code, $3.code); 
                                                  $$.code = gen_code (temp) ; }
            | expression AND expression      { sprintf (temp, "(and %s %s)", $1.code, $3.code) ; 
                                               $$.code = gen_code (temp) ; }
            | expression OR expression       { sprintf (temp, "(or %s %s)", $1.code, $3.code) ;
                                                  $$.code = gen_code (temp) ; }      
            | expression EQ expression       { sprintf (temp, "(= %s %s)", $1.code, $3.code) ;              
                                                  $$.code = gen_code (temp) ; }         
            | expression NEQ expression      { sprintf (temp, "(/= %s %s)", $1.code, $3.code) ;
                                                    $$.code = gen_code (temp) ; }   
            | expression '<' expression     { sprintf (temp, "(< %s %s)", $1.code, $3.code) ;   
                                                    $$.code = gen_code (temp) ; }
            | expression LEQ expression      { sprintf (temp, "(<= %s %s)", $1.code, $3.code) ;
                                                    $$.code = gen_code (temp) ; }
            | expression '>' expression      { sprintf (temp, "(> %s %s)", $1.code, $3.code) ;
                                                    $$.code = gen_code (temp) ; }
            | expression GEQ expression      { sprintf (temp, "(>= %s %s)", $1.code, $3.code) ;
                                                    $$.code = gen_code (temp) ; }     
            | '!' '(' expression ')'              { sprintf (temp, "(not %s)", $3.code) ;
                                                    $$.code = gen_code (temp) ; }
            ;
            
            
term:         operand                        { $$ = $1 ; }                          
            | '+' operand %prec UNARY_SIGN   { sprintf (temp, "(+ %s)", $2.code) ;
                                               $$.code = gen_code (temp) ; }
            | '-' operand %prec UNARY_SIGN   { sprintf (temp, "(- %s)", $2.code) ;
                                               $$.code = gen_code (temp) ; }    
            ;

operand:      IDENTIF                        { if (isLocalVarDeclared($1.code)) sprintf (temp, "%s_%s", current_function, $1.code);
                                                  else sprintf (temp, "%s", $1.code) ;
                                                $$.code = gen_code (temp) ; }
            | NUMBER                         { sprintf (temp, "%d", $1.value) ;
                                               $$.code = gen_code (temp) ; }
            | '(' expression ')'             { $$ = $2 ; }
            | function_call                  { sprintf (temp, "%s", $1.code) ;
                                               $$.code = gen_code (temp) ; }
            | vector_access                  { sprintf (temp, "%s", $1.code) ;
                                               $$.code = gen_code (temp) ; }
            ;


%%                            // SECTION 4    Code in C

int n_line = 1 ;

void yyerror (char *message)
{
    fprintf (stderr, "%s in line %d\n", message, n_line) ;
    printf ( "\n") ;
}

char *int_to_string (int n)
{
    sprintf (temp, "%d", n) ;
    return gen_code (temp) ;
}

char *char_to_string (char c)
{
    sprintf (temp, "%c", c) ;
    return gen_code (temp) ;
}

char *my_malloc (int nbytes)     // reserve n bytes of dynamic memory 
{
    char *p ;
    static long int nb = 0 ;     // used to count the memory  
    static int nv = 0 ;          // required in total 

    p = malloc (nbytes) ;
    if (p == NULL) {
      fprintf (stderr, "No memory left for additional %d bytes\n", nbytes) ;
      fprintf (stderr, "%ld bytes reserved in %d calls \n", nb, nv) ;  
      exit (0) ;
    }
    nb += (long) nbytes ;
    nv++ ;

    return p ;
}



/***************************************************************************/
/***************************** Keyword Section *****************************/
/***************************************************************************/

typedef struct s_keyword { // for the reserved words of C  
    char *name ;
    int token ;
} t_keyword ;

t_keyword keywords [] = {     // define the keywords 
    "main",        MAIN,      // and their associated token  
    "int",         INTEGER,
    "puts",        PUTS,
    "printf",      PRINTF,
    "&&",          AND,
    "||",          OR,
    "<=",          LEQ,
    ">=",          GEQ,
    "==",          EQ,
    "!=",          NEQ,
    "while",       WHILE,
    "if",          IF,
    "else",        ELSE,
    "for",         FOR,
    "return",      RETURN,
    NULL,          0          // 0 to mark the end of the table
} ;

t_keyword *search_keyword (char *symbol_name)
{                       // Search symbol names in the keyword table
                        // and return a pointer to token register
    int i ;
    t_keyword *sim ;

    i = 0 ;
    sim = keywords ;
    while (sim [i].name != NULL) {
	    if (strcmp (sim [i].name, symbol_name) == 0) {
                                   // strcmp(a, b) returns == 0 if a==b  
            return &(sim [i]) ;
        }
        i++ ;
    }

    return NULL ;
}

 
/***************************************************************************/
/******************** Section for the Lexical Analyzer  ********************/
/***************************************************************************/

char *gen_code (char *name)   // copy the argument to an  
{                             // string in dynamic memory  
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
    int  c ;
    unsigned char cc ;
    char expandable_ops [] =  "!<=>|/%&+-*" ;
    char temp_str [256] ;
    t_keyword *symbol ;

    do { 
        c = getchar () ; 
        if (c == '#') { // Ignore the lines starting with # (#define, #include) 
            do { // WARNING that it may malfunction if a line contains # 
                c = getchar () ; 
            } while (c != '\n') ; 
        } 
        if (c == '/') { // character / can be the beginning of a comment. 
            cc = getchar () ; 
            if (cc != '/') { // If the following char is / is a comment, but.... 
                ungetc (cc, stdin) ; 
            } else { 
                c = getchar () ; // ... 
                if (c == '@') { // Lines starting with //@ are transcribed
                    do { // This is inline code (embedded code in C).
                        c = getchar () ; 
                        putchar (c) ; 
                    } while (c != '\n') ; 
                } else { // ==> comment, ignore the line 
                    while (c != '\n') { 
                        c = getchar () ; 
                    } 
                } 
            } 
        } 
        if (c == '\n') 
            n_line++ ; 
    } while (c == ' ' || c == '\n' || c == 10 || c == 13 || c == '\t') ;

    if (c == '\"') {
        i = 0 ;
        do {
            c = getchar () ;
            temp_str [i++] = c ;
        } while (c != '\"' && i < 255) ;
        if (i == 256) {
            printf ("WARNING: string with more than 255 characters in line %d\n", n_line) ; 
        } // we should read until the next “, but, what if it is  missing? 
        temp_str [--i] = '\0' ;
        yylval.code = gen_code (temp_str) ;
        return (STRING) ;
    }

    if (c == '.' || (c >= '0' && c <= '9')) {
        ungetc (c, stdin) ;
        scanf ("%d", &yylval.value) ;
//         printf ("\nDEV: NUMBER %d\n", yylval.value) ;       
        return NUMBER ;
    }

    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        i = 0 ;
        while (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') || c == '_') && i < 255) {
        temp_str [i++] = tolower (c) ; // ALL TO SMALL LETTERS
        c = getchar () ; 
    } 
    temp_str [i] = '\0' ; // End of string  
    ungetc (c, stdin) ; // return excess char  

    yylval.code = gen_code (temp_str) ; 
    symbol = search_keyword (yylval.code) ;
    if (symbol == NULL) { // is not reserved word -> iderntifrier  
//               printf ("\nDEV: IDENTIF %s\n", yylval.code) ;    // PARA DEPURAR
            return (IDENTIF) ;
        } else {
//               printf ("\nDEV: OTRO %s\n", yylval.code) ;       // PARA DEPURAR
            return (symbol->token) ;
        }
    }

    if (strchr (expandable_ops, c) != NULL) { // // look for c in expandable_ops
        cc = getchar () ;
        sprintf (temp_str, "%c%c", (char) c, (char) cc) ;
        symbol = search_keyword (temp_str) ;
        if (symbol == NULL) {
            ungetc (cc, stdin) ;
            yylval.code = NULL ;
            return (c) ;
        } else {
            yylval.code = gen_code (temp_str) ; // although it is not used   
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
