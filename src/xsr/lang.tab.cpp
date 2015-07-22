/* A Bison parser, made by GNU Bison 3.0.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 6 "lang.y" /* yacc.c:339  */


#include <string>
#include <cstring>
#include <math.h>
#include <map>
#include "ast.h"
#include "lang.yystype.h"

typedef void* yyscan_t;
void yyerror (yyscan_t yyscanner, char const *msg);
void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg);
int yylex(YYSTYPE *yylval_param, yyscan_t yyscanner);
bool parseExpression(const std::string& inp);


#line 83 "lang.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "lang.tab.h".  */
#ifndef YY_YY_LANG_TAB_H_INCLUDED
# define YY_YY_LANG_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    AND = 258,
    OR = 259,
    LE = 260,
    GE = 261,
    EQUALS = 262,
    NOTEQUALS = 263,
    WHILE = 264,
    FOR = 265,
    IN = 266,
    OUT = 267,
    INOUT = 268,
    IF = 269,
    NONASSOC_IF = 270,
    ELSE = 271,
    IDENT = 272,
    CODE_STRING = 273,
    RETURN = 274,
    NUM_FLOAT = 275,
    NUM_INT = 276,
    ATTRIBUTE = 277,
    VARYING = 278,
    UNIFORM = 279,
    NATIVE_CODE = 280,
    NONASSOC_UNARY = 281
  };
#endif

/* Value type.  */



int yyparse (yyscan_t scanner, Ast* ast);

#endif /* !YY_YY_LANG_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 155 "lang.tab.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   266

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  164

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      40,    41,    30,    28,    39,    29,    34,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    36,    37,
      26,    38,    27,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    43,     2,     2,     2,     2,
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
      25,    35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    66,    66,    69,    70,    75,    86,    98,    99,   103,
     104,   105,   106,   115,   116,   117,   118,   119,   120,   121,
     122,   130,   131,   132,   139,   155,   156,   157,   162,   170,
     171,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   194,   199,   200,   210,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   238,   239,   246,
     250
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AND", "OR", "LE", "GE", "EQUALS",
  "NOTEQUALS", "WHILE", "FOR", "IN", "OUT", "INOUT", "IF", "NONASSOC_IF",
  "ELSE", "IDENT", "CODE_STRING", "RETURN", "NUM_FLOAT", "NUM_INT",
  "ATTRIBUTE", "VARYING", "UNIFORM", "NATIVE_CODE", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'['", "']'", "'.'", "NONASSOC_UNARY", "':'", "';'",
  "'='", "','", "'('", "')'", "'{'", "'}'", "$accept", "program",
  "grammar_elem", "grammar_list", "shader_gvar_type", "shader_globals",
  "fndecl_vardecl_var", "fndecl_vardecl", "function_decl",
  "vardecl_var_list", "vardecl", "stmt", "assign_stmt", "stmt_list",
  "expr", "expr_base", "fncall_args", "expr_fncall", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    60,    62,    43,    45,
      42,    47,    91,    93,    46,   281,    58,    59,    61,    44,
      40,    41,   123,   125
};
# endif

#define YYPACT_NINF -72

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-72)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -3,   -10,   -10,    -7,   -10,   -10,    22,   -72,    -3,   -72,
     -72,     3,    33,    44,    45,    71,    72,   -72,   -72,    63,
      55,    61,    56,    57,    65,    76,   -72,   -72,    95,    96,
      99,   103,   -72,   -24,   107,   -72,   -72,   108,   114,   118,
      66,    56,    94,   100,   101,   102,   105,    42,   -72,   140,
     -72,    42,    42,    42,   104,   -72,   -72,    42,    42,    42,
     -72,   180,   -72,   106,   111,   112,   -16,   226,   122,   140,
     110,   -72,   121,    86,    28,   -72,   -72,   -72,    42,   -72,
     -72,    49,    42,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,   128,    42,   131,    42,   125,
     143,   127,   -72,   130,   158,   113,   -72,   -72,   -72,   -72,
     -72,    42,   180,    19,   -72,   197,   197,    -1,    -1,   210,
     210,    -1,    -1,    87,    87,    67,    67,   167,   -72,   136,
     -14,   141,   138,    42,   148,   172,   -72,   149,   -72,   -72,
      42,   -72,   -72,   140,    42,   140,   -72,   174,   154,   176,
     180,   -72,   181,   201,   127,    42,   -72,    42,   140,   -72,
     178,   -72,   140,   -72
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     5,     2,     4,
       3,     7,     0,     0,     0,     0,     0,     1,     6,     0,
       0,     0,    21,     0,     0,     0,    10,    11,     0,     0,
       0,     0,    22,     0,     0,    12,     8,     0,     0,     0,
      13,     0,     0,     0,    15,    17,    19,     0,    23,     0,
       9,     0,     0,     0,    49,    62,    63,     0,     0,     0,
      14,    45,    64,     0,     0,     0,    49,     0,     0,     0,
       0,    43,     0,     0,     0,    16,    18,    20,    67,    66,
      65,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    25,
       0,    29,    41,     0,     0,     0,    31,    33,    24,    44,
      32,     0,    68,     0,    46,    51,    50,    54,    56,    53,
      52,    55,    57,    58,    59,    60,    61,     0,    48,     0,
       0,     0,     0,     0,     0,     0,    40,     0,    38,    42,
       0,    70,    47,     0,     0,     0,    26,     0,    27,     0,
      69,    35,     0,    36,    30,     0,    39,     0,     0,    28,
       0,    37,     0,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   212,   -72,    21,   -72,   189,   -72,   -72,    74,
     135,   -71,   -72,   153,   -47,   -46,   -72,   -72
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,    12,     9,    32,    33,    10,   101,
      70,    71,    72,    73,    74,    61,   113,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      60,    99,   109,    99,    75,    76,    77,    11,     1,     2,
      14,    79,    80,    81,     3,    41,   100,    42,   100,     4,
     103,     5,    17,    13,    78,    15,    16,    90,    91,    92,
      93,    94,   112,    95,   109,    19,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   129,
      20,   132,    82,    83,    84,    85,    86,    87,   140,    54,
     141,    21,    55,    56,   139,   110,   111,    28,    29,    30,
      57,    58,   151,    31,   153,    88,    89,    90,    91,    92,
      93,    94,    59,    95,    25,    22,   146,   161,    23,    24,
     114,   163,    26,    34,   150,    63,    64,   152,    27,    94,
      65,    95,    35,    66,    47,    67,    55,    56,   159,    36,
     160,    68,    37,    38,    57,    58,    39,    92,    93,    94,
      40,    95,    63,    64,    43,    44,    59,    65,    69,   108,
      66,    45,    67,    55,    56,    46,    49,    50,    68,    51,
      52,    57,    58,    53,    78,   128,    96,   106,   130,    63,
      64,    97,    98,    59,    65,    69,   138,    66,   107,    67,
      55,    56,   104,   133,   134,    68,   135,   136,    57,    58,
      82,    83,    84,    85,    86,    87,   137,   143,   144,   145,
      59,   147,    69,    82,    83,    84,    85,    86,    87,   148,
     149,    99,   155,    88,    89,    90,    91,    92,    93,    94,
     142,    95,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,   156,    95,    84,    85,   158,   157,   162,
      18,   154,   105,    88,    89,    90,    91,    92,    93,    94,
      48,    95,   131,     0,     0,     0,    88,    89,    90,    91,
      92,    93,    94,    54,    95,     0,    55,    56,     0,     0,
       0,     0,     0,     0,    57,    58,     0,     0,     0,     0,
       0,     0,     0,   102,     0,     0,    59
};

static const yytype_int16 yycheck[] =
{
      47,    17,    73,    17,    51,    52,    53,    17,    11,    12,
      17,    57,    58,    59,    17,    39,    32,    41,    32,    22,
      67,    24,     0,     2,    40,     4,     5,    28,    29,    30,
      31,    32,    78,    34,   105,    32,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    96,
      17,    98,     3,     4,     5,     6,     7,     8,    39,    17,
      41,    17,    20,    21,   111,    37,    38,    11,    12,    13,
      28,    29,   143,    17,   145,    26,    27,    28,    29,    30,
      31,    32,    40,    34,    21,    40,   133,   158,    17,    17,
      41,   162,    37,    36,   140,     9,    10,   144,    37,    32,
      14,    34,    37,    17,    38,    19,    20,    21,   155,    33,
     157,    25,    17,    17,    28,    29,    17,    30,    31,    32,
      17,    34,     9,    10,    17,    17,    40,    14,    42,    43,
      17,    17,    19,    20,    21,    17,    42,    37,    25,    38,
      38,    28,    29,    38,    40,    17,    40,    37,    17,     9,
      10,    40,    40,    40,    14,    42,    43,    17,    37,    19,
      20,    21,    40,    38,    21,    25,    39,    37,    28,    29,
       3,     4,     5,     6,     7,     8,    18,    41,    37,    41,
      40,    33,    42,     3,     4,     5,     6,     7,     8,    17,
      41,    17,    38,    26,    27,    28,    29,    30,    31,    32,
      33,    34,     5,     6,     7,     8,    26,    27,    28,    29,
      30,    31,    32,    37,    34,     5,     6,    16,    37,    41,
       8,   147,    69,    26,    27,    28,    29,    30,    31,    32,
      41,    34,    97,    -1,    -1,    -1,    26,    27,    28,    29,
      30,    31,    32,    17,    34,    -1,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    -1,    -1,    40
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    12,    17,    22,    24,    45,    46,    47,    49,
      52,    17,    48,    48,    17,    48,    48,     0,    46,    32,
      17,    17,    40,    17,    17,    21,    37,    37,    11,    12,
      13,    17,    50,    51,    36,    37,    33,    17,    17,    17,
      17,    39,    41,    17,    17,    17,    17,    38,    50,    42,
      37,    38,    38,    38,    17,    20,    21,    28,    29,    40,
      58,    59,    61,     9,    10,    14,    17,    19,    25,    42,
      54,    55,    56,    57,    58,    58,    58,    58,    40,    59,
      59,    59,     3,     4,     5,     6,     7,     8,    26,    27,
      28,    29,    30,    31,    32,    34,    40,    40,    40,    17,
      32,    53,    37,    58,    40,    57,    37,    37,    43,    55,
      37,    38,    59,    60,    41,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    17,    58,
      17,    54,    58,    38,    21,    39,    37,    18,    43,    58,
      39,    41,    33,    41,    37,    41,    58,    33,    17,    41,
      59,    55,    58,    55,    53,    38,    37,    37,    16,    58,
      58,    55,    41,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    48,    48,    49,
      49,    49,    49,    50,    50,    50,    50,    50,    50,    50,
      50,    51,    51,    51,    52,    53,    53,    53,    53,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    56,    57,    57,    58,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    60,    60,    60,
      61
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     2,     1,     4,     6,
       4,     4,     4,     2,     4,     3,     5,     3,     5,     3,
       5,     0,     1,     3,     8,     1,     3,     3,     5,     2,
       5,     2,     2,     2,     9,     5,     5,     7,     3,     5,
       3,     2,     3,     1,     2,     1,     3,     4,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     2,     2,     0,     1,     3,
       4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (scanner, ast, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, scanner, ast); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, yyscan_t scanner, Ast* ast)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (scanner);
  YYUSE (ast);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, yyscan_t scanner, Ast* ast)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner, ast);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, yyscan_t scanner, Ast* ast)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , scanner, ast);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner, ast); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, yyscan_t scanner, Ast* ast)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  YYUSE (ast);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, Ast* ast)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, scanner);
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 66 "lang.y" /* yacc.c:1646  */
    { ast->program = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 1347 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 69 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1353 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 70 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; }
#line 1359 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 76 "lang.y" /* yacc.c:1646  */
    { 
			// Create a list of program elements(only functions so far).
			(yyval.node) = ast->push<ProgramElem>(); 
			
			// A program element is not necessary a node. 
			// For example vertexAttribs/varyings/uniforms they just do a add themselves
			// to a container containing all the declarations.
			if((yyvsp[0].node) != nullptr) (yyval.node)->As<ProgramElem>().nodes.push_back((yyvsp[0].node)); 
		}
#line 1373 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 87 "lang.y" /* yacc.c:1646  */
    { 
			if ((yyvsp[0].node) != nullptr) (yyvsp[-1].node)->As<ProgramElem>().nodes.push_back((yyvsp[0].node)); 
			(yyval.node) = (yyvsp[-1].node);
		}
#line 1382 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 98 "lang.y" /* yacc.c:1646  */
    { (yyval.typeDesc) = TypeDesc((yyvsp[0].str_val)); }
#line 1388 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 99 "lang.y" /* yacc.c:1646  */
    { (yyval.typeDesc) = TypeDesc((yyvsp[-3].str_val), (yyvsp[-1].int_val)); }
#line 1394 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 103 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->vertexAttribs.push_back({(yyvsp[-4].typeDesc), (yyvsp[-3].str_val), (yyvsp[-1].str_val)}); }
#line 1400 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 104 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->stageInputVaryings.push_back({(yyvsp[-2].typeDesc), (yyvsp[-1].str_val)}); }
#line 1406 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 105 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->stageOutputVaryings.push_back({(yyvsp[-2].typeDesc), (yyvsp[-1].str_val)}); }
#line 1412 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 106 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = nullptr; ast->uniforms.push_back({(yyvsp[-2].typeDesc), (yyvsp[-1].str_val)}); }
#line 1418 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 115 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-1].str_val)), (yyvsp[0].str_val), nullptr, FNAT_In   ); }
#line 1424 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 116 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-3].str_val)), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_In   ); }
#line 1430 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 117 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-1].str_val)), (yyvsp[0].str_val), nullptr, FNAT_In	); }
#line 1436 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 118 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-3].str_val)), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_In	); }
#line 1442 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 119 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-1].str_val)), (yyvsp[0].str_val), nullptr, FNAT_Out  ); }
#line 1448 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 120 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-3].str_val)), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_Out  ); }
#line 1454 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 121 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-1].str_val)), (yyvsp[0].str_val), nullptr, FNAT_InOut); }
#line 1460 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 122 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FnDeclArgVarDecl>(TypeDesc((yyvsp[-3].str_val)), (yyvsp[-2].str_val), (yyvsp[0].node)     , FNAT_InOut); }
#line 1466 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 130 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncDecl>(); }
#line 1472 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 131 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncDecl>(); ((FuncDecl*)(yyval.node))->args.push_back((yyvsp[0].node)); }
#line 1478 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 132 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->As<FuncDecl>().args.push_back((yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1484 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 139 "lang.y" /* yacc.c:1646  */
    { 
		auto& funcDecl = (yyvsp[-4].node)->As<FuncDecl>();
		funcDecl.retType = TypeDesc((yyvsp[-7].str_val));
		funcDecl.name = (yyvsp[-6].str_val);
		funcDecl.stmt = (yyvsp[-1].node);
		(yyval.node) = (yyvsp[-4].node);
	}
#line 1496 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 155 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<VarDecl>(TypeDesc(), (yyvsp[0].str_val), nullptr); }
#line 1502 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 156 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<VarDecl>(TypeDesc(), (yyvsp[-2].str_val), (yyvsp[0].node)); }
#line 1508 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 157 "lang.y" /* yacc.c:1646  */
    { 
			(yyvsp[-2].node)->As<VarDecl>().ident.push_back((yyvsp[0].str_val));
			(yyvsp[-2].node)->As<VarDecl>().expr.push_back(nullptr);
			(yyval.node) = (yyvsp[-2].node);
		}
#line 1518 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 162 "lang.y" /* yacc.c:1646  */
    { 
			(yyval.node) = (yyvsp[-4].node); 
			(yyval.node)->As<VarDecl>().ident.push_back((yyvsp[-2].str_val));
			(yyval.node)->As<VarDecl>().expr.push_back((yyvsp[0].node));
		}
#line 1528 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 170 "lang.y" /* yacc.c:1646  */
    { (yyvsp[0].node)->As<VarDecl>().type = TypeDesc((yyvsp[-1].str_val)); (yyval.node) = (yyvsp[0].node); }
#line 1534 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 171 "lang.y" /* yacc.c:1646  */
    { (yyvsp[0].node)->As<VarDecl>().type = TypeDesc((yyvsp[-4].str_val), (yyvsp[-2].int_val)); (yyval.node) = (yyvsp[0].node); }
#line 1540 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 179 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->hasSemicolon = true; ; (yyval.node) = (yyvsp[-1].node); }
#line 1546 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 180 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->hasSemicolon = true; (yyval.node) = (yyvsp[-1].node); }
#line 1552 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 181 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->hasSemicolon = true; (yyval.node) = (yyvsp[-1].node); }
#line 1558 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 182 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtFor>((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1564 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 183 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtWhile>((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1570 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 184 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtIf>((yyvsp[-2].node), (yyvsp[0].node), nullptr); }
#line 1576 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 185 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtIf>((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1582 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 186 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->inBlock = true; (yyval.node) = (yyvsp[-1].node); }
#line 1588 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 187 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtNativeCode>((yyvsp[-2].str_val)); }
#line 1594 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 188 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtReturn>((yyvsp[-1].node)); }
#line 1600 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 189 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtReturn>(); }
#line 1606 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 194 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<Assign>((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1612 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 199 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<StmtList>(); (yyval.node)->As<StmtList>().nodes.push_back((yyvsp[0].node)); }
#line 1618 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 200 "lang.y" /* yacc.c:1646  */
    { 
			(yyval.node) = (yyvsp[-1].node);
			(yyvsp[-1].node)->As<StmtList>().nodes.push_back( {(yyvsp[0].node)} );
		}
#line 1627 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 210 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); ast->addDeduct((yyvsp[0].node)); }
#line 1633 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 212 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->inParens = true; (yyval.node) = (yyvsp[-1].node); }
#line 1639 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 213 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprIndexing>((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1645 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 214 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprMemberAccess>((yyvsp[-2].node), (yyvsp[0].str_val)); }
#line 1651 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 215 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<Ident>((yyvsp[0].str_val)); }
#line 1657 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 216 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Or, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1663 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 217 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_And, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1669 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 218 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_NEquals, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1675 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 219 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Equals, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1681 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 220 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_LEquals, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1687 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 221 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Less, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1693 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 222 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_GEquals, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1699 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 223 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Greater, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1705 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 224 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Add, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1711 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 225 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Sub, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1717 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 226 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Mul, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1723 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 227 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprBin>(EBT_Div, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1729 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 228 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprLiteral>((yyvsp[0].float_val)); }
#line 1735 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 229 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<ExprLiteral>((yyvsp[0].int_val)); }
#line 1741 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 230 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1747 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 231 "lang.y" /* yacc.c:1646  */
    { (yyvsp[0].node)->exprSign *= -1; (yyval.node) = (yyvsp[0].node); }
#line 1753 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 232 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1759 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 238 "lang.y" /* yacc.c:1646  */
    { (yyval.node) = ast->push<FuncCall>(); }
#line 1765 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 240 "lang.y" /* yacc.c:1646  */
    { 
				Node* fnCall = ast->push<FuncCall>();
				fnCall->As<FuncCall>().args.push_back((yyvsp[0].node)); 
				(yyval.node) = fnCall;
			}
#line 1775 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 246 "lang.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->As<FuncCall>().args.push_back((yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1781 "lang.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 250 "lang.y" /* yacc.c:1646  */
    { 
			(yyvsp[-1].node)->As<FuncCall>().fnName = (yyvsp[-3].str_val);
			(yyval.node) = (yyvsp[-1].node); 
		}
#line 1790 "lang.tab.cpp" /* yacc.c:1646  */
    break;


#line 1794 "lang.tab.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (scanner, ast, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (scanner, ast, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval, scanner, ast);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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
                  yystos[yystate], yyvsp, scanner, ast);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, ast, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner, ast);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, scanner, ast);
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
  return yyresult;
}
#line 259 "lang.y" /* yacc.c:1906  */


void yyerror (yyscan_t yyscanner, char const *msg){
    fprintf(stderr, "%s\n", msg);
}

void yyerror (yyscan_t yyscanner, Ast* ast, char const *msg) {
	yyerror(yyscanner, msg);
}
