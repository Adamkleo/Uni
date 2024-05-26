/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     IDENTIF = 259,
     STRING = 260,
     MAIN = 261,
     PRINT = 262,
     AND = 263,
     OR = 264,
     LEQ = 265,
     GEQ = 266,
     NEQ = 267,
     WHILE = 268,
     IF = 269,
     ELSE = 270,
     FOR = 271,
     RETURN = 272,
     SETQ = 273,
     SETF = 274,
     DEFUN = 275,
     VARIABLE = 276,
     LOOP = 277,
     DO = 278,
     MOD = 279,
     NOT = 280,
     PROGN = 281,
     PRIN1 = 282,
     EQ = 283,
     UNARY_SIGN = 284
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define IDENTIF 259
#define STRING 260
#define MAIN 261
#define PRINT 262
#define AND 263
#define OR 264
#define LEQ 265
#define GEQ 266
#define NEQ 267
#define WHILE 268
#define IF 269
#define ELSE 270
#define FOR 271
#define RETURN 272
#define SETQ 273
#define SETF 274
#define DEFUN 275
#define VARIABLE 276
#define LOOP 277
#define DO 278
#define MOD 279
#define NOT 280
#define PROGN 281
#define PRIN1 282
#define EQ 283
#define UNARY_SIGN 284




/* Copy the first part of user declarations.  */
#line 5 "back.y"
                          // SECCION 1 Declaraciones de C-Yacc

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



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 195 "back.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   184

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNRULES -- Number of states.  */
#define YYNSTATES  143

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    36,     2,     2,
      38,    39,    35,    32,     2,    33,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      30,    28,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    29,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    16,    17,    25,
      33,    35,    38,    40,    42,    44,    46,    54,    61,    66,
      68,    73,    75,    76,    81,    86,    91,    96,   102,   108,
     110,   116,   122,   128,   134,   140,   142,   148,   154,   160,
     166,   172,   178,   184,   190,   196,   206,   208,   211,   214,
     216
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    42,    -1,    52,    42,    -1,    53,    42,
      -1,    44,    42,    -1,    43,    -1,    -1,    38,    20,     6,
      38,    39,    45,    39,    -1,    38,    20,     4,    38,    39,
      45,    39,    -1,    46,    -1,    46,    45,    -1,    53,    -1,
      51,    -1,    47,    -1,    48,    -1,    38,    22,    13,    55,
      23,    45,    39,    -1,    38,    14,    55,    49,    50,    39,
      -1,    38,    26,    45,    39,    -1,    46,    -1,    38,    26,
      45,    39,    -1,    46,    -1,    -1,    38,     7,     5,    39,
      -1,    38,     7,    54,    39,    -1,    38,    27,    54,    39,
      -1,    38,    27,     5,    39,    -1,    38,    18,     4,    54,
      39,    -1,    38,    19,     4,    54,    39,    -1,    56,    -1,
      38,    32,    54,    54,    39,    -1,    38,    33,    54,    54,
      39,    -1,    38,    35,    54,    54,    39,    -1,    38,    34,
      54,    54,    39,    -1,    38,    24,    54,    54,    39,    -1,
      56,    -1,    38,     8,    55,    55,    39,    -1,    38,     9,
      55,    55,    39,    -1,    38,    28,    55,    55,    39,    -1,
      38,    12,    55,    55,    39,    -1,    38,    30,    55,    55,
      39,    -1,    38,    31,    55,    55,    39,    -1,    38,    10,
      55,    55,    39,    -1,    38,    11,    55,    55,    39,    -1,
      38,    25,    55,    55,    39,    -1,    38,    28,    38,    24,
      54,    54,    39,    54,    39,    -1,    57,    -1,    32,    57,
      -1,    33,    57,    -1,     4,    -1,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    75,    75,    78,    83,    88,    93,    99,   104,   112,
     120,   125,   133,   134,   135,   136,   140,   147,   152,   155,
     162,   165,   171,   178,   187,   192,   197,   211,   221,   228,
     232,   237,   242,   247,   252,   258,   262,   267,   272,   277,
     282,   287,   292,   297,   302,   307,   316,   317,   319,   323,
     326
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "IDENTIF", "STRING", "MAIN",
  "PRINT", "AND", "OR", "LEQ", "GEQ", "NEQ", "WHILE", "IF", "ELSE", "FOR",
  "RETURN", "SETQ", "SETF", "DEFUN", "VARIABLE", "LOOP", "DO", "MOD",
  "NOT", "PROGN", "PRIN1", "'='", "EQ", "'<'", "'>'", "'+'", "'-'", "'/'",
  "'*'", "'%'", "UNARY_SIGN", "'('", "')'", "$accept", "axiom",
  "outer_sentence", "main", "function", "inner_sentence", "statement",
  "while", "conditional", "if_block", "else_block", "print",
  "variable_declaration", "variable_assignation", "expression",
  "logical_expression", "term", "operand", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    61,   283,
      60,    62,    43,    45,    47,    42,    37,   284,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    42,    42,    43,    44,
      45,    45,    46,    46,    46,    46,    47,    48,    49,    49,
      50,    50,    50,    51,    51,    51,    51,    52,    53,    54,
      54,    54,    54,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    56,    56,    56,    57,
      57
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     1,     0,     7,     7,
       1,     2,     1,     1,     1,     1,     7,     6,     4,     1,
       4,     1,     0,     4,     4,     4,     4,     5,     5,     1,
       5,     5,     5,     5,     5,     1,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     9,     1,     2,     2,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       7,     0,     0,     2,     6,     7,     7,     7,     0,     0,
       0,     1,     5,     3,     4,     0,     0,     0,     0,    50,
      49,     0,     0,     0,     0,    29,    46,     0,     0,     0,
      47,    48,     0,     0,     0,     0,     0,    27,    28,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    10,    14,
      15,    13,    12,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,    11,     8,    34,    30,    31,    33,
      32,     0,     0,     0,     0,    35,     0,     0,     0,    23,
      24,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,    22,     0,    26,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,    36,    37,    42,    43,    39,
      44,     0,    38,    40,    41,    18,     0,    16,     0,    20,
       0,     0,    45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    47,    48,    49,    50,    92,
     109,    51,     6,    52,    24,    74,    75,    26
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -62
static const yytype_int16 yypact[] =
{
     -16,   -12,    34,   -62,   -62,   -16,   -16,   -16,    51,    63,
      54,   -62,   -62,   -62,   -62,    21,    21,    33,    35,   -62,
     -62,     8,     8,    55,    37,   -62,   -62,    38,    39,    44,
     -62,   -62,    21,    21,    21,    21,    21,   -62,   -62,    59,
      59,    21,    21,    21,    21,    21,   156,    61,    59,   -62,
     -62,   -62,   -62,    62,    64,    65,    67,    68,    72,     0,
      42,    86,    32,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,    80,    81,   143,    85,   -62,    42,    83,    96,   -62,
     -62,    42,    42,    42,    42,    42,    42,    53,    42,    42,
      91,   -62,    98,   114,   -62,   -62,    42,    42,    42,    42,
      42,    42,    84,    42,    42,    42,    59,   150,   -62,   100,
      59,   101,   117,   119,   120,   121,   122,    21,   123,   126,
     127,   128,    59,   -62,   140,   -62,   -62,   -62,   -62,   -62,
     -62,    21,   -62,   -62,   -62,   -62,   141,   -62,   142,   -62,
      21,   145,   -62
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -62,   -62,    56,   -62,   -62,   -38,   -61,   -62,   -62,   -62,
     -62,   -62,   -62,     9,     7,    45,   -15,    60
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      25,    25,    53,    19,    20,    71,     8,     9,    10,     7,
      64,    19,    20,    91,     7,     7,     7,    25,    25,    25,
      25,    25,     1,    27,    19,    20,    25,    25,    25,    25,
      25,   108,    21,    22,    11,    19,    20,    77,    23,    41,
      42,    43,    44,    45,    25,    19,    20,    25,    54,    55,
      56,    57,    58,    21,    22,    15,    19,    20,    17,    23,
      18,    12,    13,    14,    21,    22,    72,    16,   121,    78,
      23,    28,   124,    29,    21,    22,    37,    38,    39,    32,
      73,    30,    31,    40,   136,    21,    22,    33,    34,    35,
      36,   102,    81,    82,    83,    84,    85,    46,    59,    76,
      63,    65,    25,    66,    67,    60,    68,    69,   117,    86,
       9,    70,    87,    61,    88,    89,    25,   106,    62,    79,
      80,    93,    94,    90,   131,    25,    96,    97,    98,    99,
     100,   101,   103,   104,   105,    95,   107,   110,   138,   123,
     125,   111,   112,   113,   114,   115,   116,   141,   118,   119,
     120,    81,    82,    83,    84,    85,   126,    59,   127,   128,
     129,   130,   132,    59,    60,   133,   134,   135,    86,     9,
      60,    87,    61,    88,    89,     9,   122,    62,    61,   137,
     139,   140,     0,    62,   142
};

static const yytype_int16 yycheck[] =
{
      15,    16,    40,     3,     4,     5,    18,    19,    20,     0,
      48,     3,     4,    74,     5,     6,     7,    32,    33,    34,
      35,    36,    38,    16,     3,     4,    41,    42,    43,    44,
      45,    92,    32,    33,     0,     3,     4,     5,    38,    32,
      33,    34,    35,    36,    59,     3,     4,    62,    41,    42,
      43,    44,    45,    32,    33,     4,     3,     4,     4,    38,
       6,     5,     6,     7,    32,    33,    59,     4,   106,    62,
      38,    38,   110,    38,    32,    33,    39,    39,    39,    24,
      38,    21,    22,    39,   122,    32,    33,    32,    33,    34,
      35,    38,     8,     9,    10,    11,    12,    38,     7,    13,
      39,    39,   117,    39,    39,    14,    39,    39,    24,    25,
      19,    39,    28,    22,    30,    31,   131,    26,    27,    39,
      39,    76,    39,    38,   117,   140,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    39,    38,    23,   131,    39,
      39,    96,    97,    98,    99,   100,   101,   140,   103,   104,
     105,     8,     9,    10,    11,    12,    39,     7,    39,    39,
      39,    39,    39,     7,    14,    39,    39,    39,    25,    19,
      14,    28,    22,    30,    31,    19,    26,    27,    22,    39,
      39,    39,    -1,    27,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,    41,    42,    43,    44,    52,    53,    18,    19,
      20,     0,    42,    42,    42,     4,     4,     4,     6,     3,
       4,    32,    33,    38,    54,    56,    57,    54,    38,    38,
      57,    57,    24,    32,    33,    34,    35,    39,    39,    39,
      39,    54,    54,    54,    54,    54,    38,    45,    46,    47,
      48,    51,    53,    45,    54,    54,    54,    54,    54,     7,
      14,    22,    27,    39,    45,    39,    39,    39,    39,    39,
      39,     5,    54,    38,    55,    56,    13,     5,    54,    39,
      39,     8,     9,    10,    11,    12,    25,    28,    30,    31,
      38,    46,    49,    55,    39,    39,    55,    55,    55,    55,
      55,    55,    38,    55,    55,    55,    26,    38,    46,    50,
      23,    55,    55,    55,    55,    55,    55,    24,    55,    55,
      55,    45,    26,    39,    45,    39,    39,    39,    39,    39,
      39,    54,    39,    39,    39,    39,    45,    39,    54,    39,
      39,    54,    39
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 75 "back.y"
    { printf("%s\n", (yyvsp[(1) - (1)]).code); ;}
    break;

  case 3:
#line 79 "back.y"
    {
        sprintf(temp, "%s\n%s", (yyvsp[(1) - (2)]).code, (yyvsp[(2) - (2)]).code); 
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 4:
#line 84 "back.y"
    {
        sprintf(temp, "%s\n%s", (yyvsp[(1) - (2)]).code, (yyvsp[(2) - (2)]).code);  
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 5:
#line 89 "back.y"
    {
        sprintf(temp, "%s\n%s", (yyvsp[(1) - (2)]).code, (yyvsp[(2) - (2)]).code); 
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 6:
#line 94 "back.y"
    {
        sprintf(temp, "%s", (yyvsp[(1) - (1)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 7:
#line 99 "back.y"
    {
        (yyval).code = gen_code("");
    ;}
    break;

  case 8:
#line 105 "back.y"
    {
        sprintf(temp, ": main\n%s\n;", (yyvsp[(6) - (7)]).code);  
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 9:
#line 113 "back.y"
    {
        sprintf(temp, ": %s\n%s\n;", (yyvsp[(3) - (7)]).code, (yyvsp[(6) - (7)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 10:
#line 121 "back.y"
    {
        sprintf(temp, "%s", (yyvsp[(1) - (1)]).code);  
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 11:
#line 126 "back.y"
    {
        sprintf(temp, "%s%s", (yyvsp[(1) - (2)]).code, (yyvsp[(2) - (2)]).code);  
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 12:
#line 133 "back.y"
    { (yyval).code = gen_code((yyvsp[(1) - (1)]).code);;}
    break;

  case 13:
#line 134 "back.y"
    { (yyval).code = gen_code((yyvsp[(1) - (1)]).code);;}
    break;

  case 14:
#line 135 "back.y"
    { (yyval).code = gen_code((yyvsp[(1) - (1)]).code);;}
    break;

  case 15:
#line 136 "back.y"
    { (yyval).code = gen_code((yyvsp[(1) - (1)]).code);;}
    break;

  case 16:
#line 141 "back.y"
    {
        sprintf(temp, "begin \n\t%swhile\n\t%s\nrepeat\n;", (yyvsp[(6) - (7)]).code, (yyvsp[(4) - (7)]).code);  
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 17:
#line 148 "back.y"
    { sprintf(temp, "%s if %s %s then", (yyvsp[(3) - (6)]).code, (yyvsp[(4) - (6)]).code, (yyvsp[(5) - (6)]).code);
     (yyval).code = gen_code(temp); ;}
    break;

  case 18:
#line 153 "back.y"
    { sprintf(temp, "\n%s\n", (yyvsp[(3) - (4)]).code); 
                (yyval).code = gen_code(temp);;}
    break;

  case 19:
#line 156 "back.y"
    { 
            sprintf(temp, "\n%s\n", (yyvsp[(1) - (1)]).code); 
            (yyval).code = gen_code(temp); 
        ;}
    break;

  case 20:
#line 163 "back.y"
    { sprintf(temp, "\nelse %s\n", (yyvsp[(3) - (4)]).code); 
                (yyval).code = gen_code(temp);;}
    break;

  case 21:
#line 166 "back.y"
    { 
            sprintf(temp, "\nelse %s\n", (yyvsp[(1) - (1)]).code); 
            (yyval).code = gen_code(temp); 
            ;}
    break;

  case 22:
#line 171 "back.y"
    { 
            (yyval).code = gen_code(""); 
        ;}
    break;

  case 23:
#line 179 "back.y"
    {
        char modified_string[64];
        strcpy(modified_string, (yyvsp[(3) - (4)]).code);
        insert_space(modified_string); 
        sprintf(temp, ".%s\n", modified_string);  
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 24:
#line 188 "back.y"
    {
        sprintf(temp, "%s .\n", (yyvsp[(3) - (4)]).code);  
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 25:
#line 193 "back.y"
    {
        sprintf(temp, "%s .\n", (yyvsp[(3) - (4)]).code);  
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 26:
#line 198 "back.y"
    {
        char modified_string[64];
        strcpy(modified_string, (yyvsp[(3) - (4)]).code);
        insert_space(modified_string); 
        sprintf(temp, "%s .\n", modified_string);  
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 27:
#line 212 "back.y"
    {

        sprintf(temp, "variable %s\n%d %s !\n", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).value, (yyvsp[(3) - (5)]).code); 
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 28:
#line 222 "back.y"
    {
        sprintf(temp, "%s %s !\n", (yyvsp[(4) - (5)]).code, (yyvsp[(3) - (5)]).code);  
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 29:
#line 229 "back.y"
    {
        (yyval).code = (yyvsp[(1) - (1)]).code;
    ;}
    break;

  case 30:
#line 233 "back.y"
    {
        sprintf(temp, "%s %s +", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 31:
#line 238 "back.y"
    {
        sprintf(temp, "%s %s -", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 32:
#line 243 "back.y"
    {
        sprintf(temp, "%s %s *", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 33:
#line 248 "back.y"
    {
        sprintf(temp, "%s %s /", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 34:
#line 253 "back.y"
    {
        sprintf(temp, "%s %s mod", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 35:
#line 259 "back.y"
    {
        (yyval).code = (yyvsp[(1) - (1)]).code;
    ;}
    break;

  case 36:
#line 263 "back.y"
    {
        sprintf(temp, "%s %s and", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 37:
#line 268 "back.y"
    {
        sprintf(temp, "%s %s or", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 38:
#line 273 "back.y"
    {
        sprintf(temp, "%s %s =", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 39:
#line 278 "back.y"
    {
        sprintf(temp, "%s %s = 0=", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 40:
#line 283 "back.y"
    {
        sprintf(temp, "%s %s <", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 41:
#line 288 "back.y"
    {
        sprintf(temp, "%s %s >", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 42:
#line 293 "back.y"
    {
        sprintf(temp, "%s %s <=", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 43:
#line 298 "back.y"
    {
        sprintf(temp, "%s %s >=", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 44:
#line 303 "back.y"
    {
        sprintf(temp, "%s %s 0=", (yyvsp[(3) - (5)]).code, (yyvsp[(4) - (5)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 45:
#line 308 "back.y"
    {
        sprintf(temp, "%s %s mod %s =", (yyvsp[(4) - (9)]).code, (yyvsp[(5) - (9)]).code, (yyvsp[(8) - (9)]).code);
        (yyval).code = gen_code(temp);
    ;}
    break;

  case 46:
#line 316 "back.y"
    { (yyval) = (yyvsp[(1) - (1)]) ; ;}
    break;

  case 47:
#line 317 "back.y"
    { sprintf (temp, "+%s", (yyvsp[(2) - (2)]).code) ;
                                               (yyval).code = gen_code (temp) ; ;}
    break;

  case 48:
#line 319 "back.y"
    { sprintf (temp, "-%s", (yyvsp[(2) - (2)]).code) ;
                                               (yyval).code = gen_code (temp) ; ;}
    break;

  case 49:
#line 323 "back.y"
    { sprintf (temp, "%s @", (yyvsp[(1) - (1)]).code);
                                                  
                                                (yyval).code = gen_code (temp) ; ;}
    break;

  case 50:
#line 326 "back.y"
    { sprintf (temp, "%d", (yyvsp[(1) - (1)]).value) ;
                                               (yyval).code = gen_code (temp) ; ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1872 "back.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 330 "back.y"


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

