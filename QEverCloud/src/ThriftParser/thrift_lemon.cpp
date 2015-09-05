/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 6 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"

#include <assert.h>
#include "Parser.h"
#include "ParserHelper.h"
#include <QtDebug>
#line 14 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 91
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE  QString* 
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  Containertype* yy16;
  QString* yy19;
  QList<Parser::Function>* yy29;
  Parser::Function* yy30;
  Listtype* yy37;
  QPair<QString, QString>* yy38;
  Maptype* yy71;
  Fieldtype* yy85;
  QList<QPair<QString, QString>>* yy97;
  QList<QSharedPointer<Parser::ConstValue>>* yy98;
  Parser::ConstValue* yy108;
  Parser::Field* yy109;
  Parser::Field::RequiredFlag yy110;
  int yy112;
  QList<Parser::Field>* yy123;
  bool yy137;
  Definitiontype* yy142;
  Settype* yy149;
  QList<QPair<QSharedPointer<Parser::ConstValue>, QSharedPointer<Parser::ConstValue>>>* yy150;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 2000
#endif
#define ParseARG_SDECL  Parser* pParser ;
#define ParseARG_PDECL , Parser* pParser 
#define ParseARG_FETCH  Parser* pParser  = yypParser->pParser 
#define ParseARG_STORE yypParser->pParser  = pParser 
#define YYNSTATE 198
#define YYNRULE 97
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
#define YY_ACTTAB_COUNT (449)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   170,  296,  118,   10,    9,    8,    7,    6,    5,    4,
 /*    10 */     3,    2,    1,  112,  170,  144,   92,   45,  140,  139,
 /*    20 */   138,  129,  117,  166,  165,  164,  163,  162,  161,  160,
 /*    30 */   159,  106,  145,   90,  103,  101,  198,  166,  165,  164,
 /*    40 */   163,  162,  161,  160,  159,  106,  136,   90,  103,  101,
 /*    50 */   197,   10,    9,    8,    7,    6,    5,    4,    3,    2,
 /*    60 */     1,  112,  196,   10,    9,    8,    7,    6,    5,    4,
 /*    70 */     3,    2,    1,  112,  195,   10,    9,    8,    7,    6,
 /*    80 */     5,    4,    3,    2,    1,  112,  194,   10,    9,    8,
 /*    90 */     7,    6,    5,    4,    3,    2,    1,  112,  193,   10,
 /*   100 */     9,    8,    7,    6,    5,    4,    3,    2,    1,  112,
 /*   110 */   192,   10,    9,    8,    7,    6,    5,    4,    3,    2,
 /*   120 */     1,  112,  191,   10,    9,    8,    7,    6,    5,    4,
 /*   130 */     3,    2,    1,  112,  190,   10,    9,    8,    7,    6,
 /*   140 */     5,    4,    3,    2,    1,  112,  189,   10,    9,    8,
 /*   150 */     7,    6,    5,    4,    3,    2,    1,  112,  188,   10,
 /*   160 */     9,    8,    7,    6,    5,    4,    3,    2,    1,  112,
 /*   170 */   166,  165,  164,  163,  162,  161,  160,  159,  106,   90,
 /*   180 */   187,  103,  101,  130,  116,  169,  115,  114,  186,   49,
 /*   190 */    64,   13,  113,   20,   75,  130,   48,  169,   72,   70,
 /*   200 */    68,  185,  135,   84,   66,  168,  167,  158,  157,  156,
 /*   210 */    96,   43,   53,   90,  127,   81,  184,  168,  167,  158,
 /*   220 */   157,  156,  180,  131,   39,  179,   26,  111,   90,  169,
 /*   230 */   122,   90,   25,  105,  182,  169,  180,  110,   47,  179,
 /*   240 */    24,  176,  104,  173,  169,   38,   25,   17,  182,  168,
 /*   250 */   167,  158,  157,  156,  107,  168,  167,  158,  157,  156,
 /*   260 */    18,  181,   27,  155,  168,  167,  158,  157,  156,  102,
 /*   270 */    16,  169,  134,   85,   12,  181,   27,  100,  154,  169,
 /*   280 */   178,  177,   91,  108,  169,   15,  152,   78,  153,  169,
 /*   290 */    97,  168,  167,  158,  157,  156,  150,   43,   53,  168,
 /*   300 */   167,  158,  157,  156,  168,  167,  158,  157,  156,  168,
 /*   310 */   167,  158,  157,  156,   19,   99,   21,   98,  180,   93,
 /*   320 */    76,  179,   94,   89,   44,   23,  151,   87,   25,  146,
 /*   330 */   182,   73,   43,   53,   63,  168,  167,  158,  157,  156,
 /*   340 */   168,  167,  158,  157,  156,   23,  121,   90,  107,   48,
 /*   350 */   143,  178,  177,  109,   23,  119,   51,  181,   27,  137,
 /*   360 */   107,  120,   90,   88,  183,   62,   22,  127,  141,   50,
 /*   370 */   125,  178,  177,  174,  178,  177,  133,  171,   61,   83,
 /*   380 */   178,  177,  175,   60,   59,   80,  178,  177,   58,  172,
 /*   390 */   178,  177,  178,  177,  178,  177,  178,  177,  126,   77,
 /*   400 */    36,  124,   74,  123,   42,   71,   69,   57,   67,   46,
 /*   410 */    56,   55,   35,   34,   54,   33,   32,   41,   31,   40,
 /*   420 */    30,   29,   28,  149,  148,   95,   37,  147,  142,   79,
 /*   430 */    52,  127,   82,  297,  297,  297,   86,  297,  297,  297,
 /*   440 */   297,  297,   14,  297,   65,   11,  132,  297,  128,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     6,   46,   47,   48,   49,   50,   51,   52,   53,   54,
 /*    10 */    55,   56,   57,   58,    6,   68,   69,   70,   20,   21,
 /*    20 */    73,   27,    1,   29,   30,   31,   32,   33,   34,   35,
 /*    30 */    36,   37,   14,   15,   40,   41,    0,   29,   30,   31,
 /*    40 */    32,   33,   34,   35,   36,   37,   14,   15,   40,   41,
 /*    50 */    47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
 /*    60 */    57,   58,   47,   48,   49,   50,   51,   52,   53,   54,
 /*    70 */    55,   56,   57,   58,   47,   48,   49,   50,   51,   52,
 /*    80 */    53,   54,   55,   56,   57,   58,   47,   48,   49,   50,
 /*    90 */    51,   52,   53,   54,   55,   56,   57,   58,   47,   48,
 /*   100 */    49,   50,   51,   52,   53,   54,   55,   56,   57,   58,
 /*   110 */    47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
 /*   120 */    57,   58,   47,   48,   49,   50,   51,   52,   53,   54,
 /*   130 */    55,   56,   57,   58,   47,   48,   49,   50,   51,   52,
 /*   140 */    53,   54,   55,   56,   57,   58,   47,   48,   49,   50,
 /*   150 */    51,   52,   53,   54,   55,   56,   57,   58,   47,   48,
 /*   160 */    49,   50,   51,   52,   53,   54,   55,   56,   57,   58,
 /*   170 */    29,   30,   31,   32,   33,   34,   35,   36,   37,   15,
 /*   180 */     3,   40,   41,   59,    2,   61,    4,    5,    3,   25,
 /*   190 */     8,    9,    6,   11,   12,   59,    8,   61,   16,   17,
 /*   200 */    18,    6,   14,   79,   22,   81,   82,   83,   84,   85,
 /*   210 */    62,   63,   64,   15,   26,   79,    7,   81,   82,   83,
 /*   220 */    84,   85,    3,   25,   10,    6,    7,   59,   15,   61,
 /*   230 */    14,   15,   13,   59,   15,   61,    3,    6,   25,    6,
 /*   240 */     7,   44,   59,   14,   61,   19,   13,    7,   15,   81,
 /*   250 */    82,   83,   84,   85,   60,   81,   82,   83,   84,   85,
 /*   260 */    38,   42,   43,   39,   81,   82,   83,   84,   85,   59,
 /*   270 */    38,   61,   76,   77,   78,   42,   43,   59,   39,   61,
 /*   280 */    86,   87,   59,   89,   61,   38,    6,   59,   39,   61,
 /*   290 */     6,   81,   82,   83,   84,   85,   62,   63,   64,   81,
 /*   300 */    82,   83,   84,   85,   81,   82,   83,   84,   85,   81,
 /*   310 */    82,   83,   84,   85,    9,   61,   11,   12,    3,    6,
 /*   320 */    61,    6,   17,   18,   13,   60,   14,   22,   13,   15,
 /*   330 */    15,   62,   63,   64,   13,   81,   82,   83,   84,   85,
 /*   340 */    81,   82,   83,   84,   85,   60,   14,   15,   60,    8,
 /*   350 */     7,   86,   87,   88,   60,   14,    6,   42,   43,   19,
 /*   360 */    60,   14,   15,    6,   60,   13,   60,   26,   60,    6,
 /*   370 */    60,   86,   87,   88,   86,   87,    7,   89,   13,    6,
 /*   380 */    86,   87,   88,   24,   24,    6,   86,   87,   24,   89,
 /*   390 */    86,   87,   86,   87,   86,   87,   86,   87,    6,    6,
 /*   400 */    10,    6,    6,   14,   13,    6,    6,   13,    6,    6,
 /*   410 */    13,   13,   67,   67,   13,   67,   67,   75,   67,   75,
 /*   420 */    67,   67,   67,   65,    7,   10,   10,   66,   72,   23,
 /*   430 */     6,   26,   28,   90,   90,   90,   74,   90,   90,   90,
 /*   440 */    90,   90,   71,   90,   74,   78,   80,   90,   80,
};
#define YY_SHIFT_USE_DFLT (-7)
#define YY_SHIFT_COUNT (118)
#define YY_SHIFT_MIN   (-6)
#define YY_SHIFT_MAX   (424)
static const short yy_shift_ofst[] = {
 /*     0 */   182,  182,  182,  182,  182,  182,  182,  182,  182,  182,
 /*    10 */   182,   -6,   -6,    8,    8,    8,    8,    8,    8,    8,
 /*    20 */   141,  141,  233,  219,  315,  315,  315,  315,  347,  332,
 /*    30 */   216,  213,  198,  164,   32,   18,  315,  315,  315,  315,
 /*    40 */   341,  188,  424,  424,  424,   -2,  406,  404,  405,  404,
 /*    50 */   406,  416,  415,  417,   -7,   -7,   -7,   -7,   -7,   -7,
 /*    60 */    -7,   -7,   -7,   -7,  305,  401,  403,  398,  402,  397,
 /*    70 */   400,  394,  399,  389,  391,  396,  395,  390,  393,  392,
 /*    80 */   364,  379,  360,  359,  373,  369,  365,  363,  352,  357,
 /*    90 */   340,  350,  343,  321,  313,  314,  312,  311,  284,  280,
 /*   100 */   249,  247,  239,  232,  224,  240,  222,  226,  229,  197,
 /*   110 */   214,  231,  209,  195,  186,  185,  177,   36,   21,
};
#define YY_REDUCE_USE_DFLT (-54)
#define YY_REDUCE_COUNT (63)
#define YY_REDUCE_MIN   (-53)
#define YY_REDUCE_MAX   (371)
static const short yy_reduce_ofst[] = {
 /*     0 */   -45,  111,   99,   87,   75,   63,   51,   39,   27,   15,
 /*    10 */     3,  136,  124,  228,  223,  218,  210,  183,  174,  168,
 /*    20 */   259,  254,  300,  294,  288,  194,  285,  265,  -53,  -53,
 /*    30 */   -53,  -53,  -53,  -53,  -53,  -53,  310,  308,  306,  304,
 /*    40 */   196,  196,  269,  234,  148,  371,  370,  368,  367,  366,
 /*    50 */   362,  356,  361,  358,  344,  355,  354,  353,  351,  349,
 /*    60 */   348,  342,  346,  345,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   199,  199,  199,  199,  199,  199,  199,  199,  199,  199,
 /*    10 */   199,  295,  295,  295,  295,  295,  295,  295,  295,  295,
 /*    20 */   295,  295,  292,  288,  292,  292,  288,  288,  239,  239,
 /*    30 */   239,  239,  239,  239,  239,  239,  295,  295,  295,  295,
 /*    40 */   257,  257,  221,  221,  221,  244,  249,  261,  257,  261,
 /*    50 */   249,  241,  227,  224,  251,  234,  234,  234,  234,  234,
 /*    60 */   234,  251,  234,  234,  295,  295,  295,  295,  295,  295,
 /*    70 */   295,  295,  295,  295,  295,  295,  295,  295,  295,  295,
 /*    80 */   295,  295,  295,  295,  295,  253,  295,  295,  295,  295,
 /*    90 */   295,  295,  236,  295,  295,  295,  295,  295,  295,  295,
 /*   100 */   295,  295,  295,  295,  295,  295,  295,  295,  295,  295,
 /*   110 */   295,  295,  213,  295,  295,  295,  295,  295,  295,  247,
 /*   120 */   232,  230,  229,  219,  218,  216,  250,  258,  256,  260,
 /*   130 */   259,  262,  255,  254,  252,  248,  233,  243,  240,  246,
 /*   140 */   245,  242,  238,  237,  235,  231,  228,  226,  225,  223,
 /*   150 */   222,  220,  217,  280,  279,  278,  277,  276,  275,  274,
 /*   160 */   273,  272,  271,  270,  269,  268,  267,  266,  265,  264,
 /*   170 */   263,  294,  293,  291,  290,  289,  287,  286,  285,  284,
 /*   180 */   283,  282,  281,  215,  214,  212,  211,  210,  209,  208,
 /*   190 */   207,  206,  205,  204,  203,  202,  201,  200,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "END_OF_FILE",   "INCLUDE",       "STRING_VALUE",
  "CPP_INCLUDE",   "NAMESPACE",     "IDENTIFIER",    "LISTSEP",     
  "DOC_COMMENT",   "CONST",         "EQ",            "TYPEDEF",     
  "ENUM",          "CURLY_OPEN",    "CURLY_CLOSE",   "INTEGER_VALUE",
  "UNION",         "EXCEPTION",     "STRUCT",        "COLON",       
  "REQUIRED",      "OPTIONAL",      "SERVICE",       "EXTENDS",     
  "PAREN_OPEN",    "PAREN_CLOSE",   "ONEWAY",        "VOID",        
  "THROWS",        "BOOL",          "BYTE",          "I16",         
  "I32",           "I64",           "DOUBLE",        "STRING",      
  "BINARY",        "MAP",           "LT",            "GT",          
  "SET",           "LIST",          "DOUBLE_VALUE",  "BRACKET_OPEN",
  "BRACKET_CLOSE",  "error",         "thrift",        "body",        
  "include",       "cppinclude",    "namespace",     "const",       
  "typedef",       "enum",          "struct",        "union",       
  "exception",     "service",       "constbody",     "fieldtype",   
  "constvalue",    "definitiontype",  "enumbody",      "enumitem",    
  "enumvalue",     "enumsep",       "enuminit",      "fieldlist",   
  "field",         "fieldbody",     "fieldidoption",  "fieldreq",    
  "fieldinitializer",  "fieldid",       "extends",       "functionlist",
  "function",      "functionbody",  "oneway",        "functiontype",
  "throws",        "basetype",      "containertype",  "maptype",     
  "settype",       "listtype",      "constlist",     "constmap",    
  "constvaluelist",  "constmapvaluelist",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "thrift ::= body END_OF_FILE",
 /*   1 */ "body ::=",
 /*   2 */ "body ::= include body",
 /*   3 */ "body ::= cppinclude body",
 /*   4 */ "body ::= namespace body",
 /*   5 */ "body ::= const body",
 /*   6 */ "body ::= typedef body",
 /*   7 */ "body ::= enum body",
 /*   8 */ "body ::= struct body",
 /*   9 */ "body ::= union body",
 /*  10 */ "body ::= exception body",
 /*  11 */ "body ::= service body",
 /*  12 */ "include ::= INCLUDE STRING_VALUE",
 /*  13 */ "cppinclude ::= CPP_INCLUDE STRING_VALUE",
 /*  14 */ "namespace ::= NAMESPACE IDENTIFIER IDENTIFIER",
 /*  15 */ "const ::= constbody",
 /*  16 */ "const ::= constbody LISTSEP",
 /*  17 */ "constbody ::= DOC_COMMENT CONST fieldtype IDENTIFIER EQ constvalue",
 /*  18 */ "constbody ::= CONST fieldtype IDENTIFIER EQ constvalue",
 /*  19 */ "typedef ::= DOC_COMMENT TYPEDEF definitiontype IDENTIFIER",
 /*  20 */ "typedef ::= TYPEDEF definitiontype IDENTIFIER",
 /*  21 */ "enum ::= ENUM IDENTIFIER CURLY_OPEN enumbody CURLY_CLOSE",
 /*  22 */ "enum ::= DOC_COMMENT ENUM IDENTIFIER CURLY_OPEN enumbody CURLY_CLOSE",
 /*  23 */ "enumbody ::=",
 /*  24 */ "enumbody ::= enumitem enumbody",
 /*  25 */ "enumitem ::= enumvalue enumsep",
 /*  26 */ "enumsep ::=",
 /*  27 */ "enumsep ::= LISTSEP",
 /*  28 */ "enumvalue ::= IDENTIFIER enuminit",
 /*  29 */ "enuminit ::=",
 /*  30 */ "enuminit ::= EQ INTEGER_VALUE",
 /*  31 */ "union ::= UNION IDENTIFIER CURLY_OPEN fieldlist CURLY_CLOSE",
 /*  32 */ "exception ::= EXCEPTION IDENTIFIER CURLY_OPEN fieldlist CURLY_CLOSE",
 /*  33 */ "exception ::= DOC_COMMENT EXCEPTION IDENTIFIER CURLY_OPEN fieldlist CURLY_CLOSE",
 /*  34 */ "struct ::= STRUCT IDENTIFIER CURLY_OPEN fieldlist CURLY_CLOSE",
 /*  35 */ "struct ::= DOC_COMMENT STRUCT IDENTIFIER CURLY_OPEN fieldlist CURLY_CLOSE",
 /*  36 */ "fieldlist ::=",
 /*  37 */ "fieldlist ::= fieldlist field",
 /*  38 */ "field ::= fieldbody",
 /*  39 */ "field ::= fieldbody LISTSEP",
 /*  40 */ "fieldbody ::= fieldidoption fieldreq fieldtype IDENTIFIER fieldinitializer",
 /*  41 */ "fieldidoption ::=",
 /*  42 */ "fieldidoption ::= fieldid",
 /*  43 */ "fieldinitializer ::=",
 /*  44 */ "fieldinitializer ::= EQ constvalue",
 /*  45 */ "fieldid ::= INTEGER_VALUE COLON",
 /*  46 */ "fieldreq ::=",
 /*  47 */ "fieldreq ::= REQUIRED",
 /*  48 */ "fieldreq ::= OPTIONAL",
 /*  49 */ "service ::= SERVICE IDENTIFIER extends CURLY_OPEN functionlist CURLY_CLOSE",
 /*  50 */ "service ::= DOC_COMMENT SERVICE IDENTIFIER extends CURLY_OPEN functionlist CURLY_CLOSE",
 /*  51 */ "extends ::=",
 /*  52 */ "extends ::= EXTENDS IDENTIFIER",
 /*  53 */ "functionlist ::=",
 /*  54 */ "functionlist ::= functionlist function",
 /*  55 */ "function ::= functionbody",
 /*  56 */ "function ::= functionbody LISTSEP",
 /*  57 */ "functionbody ::= oneway functiontype IDENTIFIER PAREN_OPEN fieldlist PAREN_CLOSE throws",
 /*  58 */ "functionbody ::= DOC_COMMENT oneway functiontype IDENTIFIER PAREN_OPEN fieldlist PAREN_CLOSE throws",
 /*  59 */ "oneway ::=",
 /*  60 */ "oneway ::= ONEWAY",
 /*  61 */ "functiontype ::= fieldtype",
 /*  62 */ "functiontype ::= VOID",
 /*  63 */ "throws ::=",
 /*  64 */ "throws ::= THROWS PAREN_OPEN fieldlist PAREN_CLOSE",
 /*  65 */ "fieldtype ::= IDENTIFIER",
 /*  66 */ "fieldtype ::= definitiontype",
 /*  67 */ "definitiontype ::= basetype",
 /*  68 */ "definitiontype ::= containertype",
 /*  69 */ "basetype ::= BOOL",
 /*  70 */ "basetype ::= BYTE",
 /*  71 */ "basetype ::= I16",
 /*  72 */ "basetype ::= I32",
 /*  73 */ "basetype ::= I64",
 /*  74 */ "basetype ::= DOUBLE",
 /*  75 */ "basetype ::= STRING",
 /*  76 */ "basetype ::= BINARY",
 /*  77 */ "containertype ::= maptype",
 /*  78 */ "containertype ::= settype",
 /*  79 */ "containertype ::= listtype",
 /*  80 */ "maptype ::= MAP LT fieldtype LISTSEP fieldtype GT",
 /*  81 */ "settype ::= SET LT fieldtype GT",
 /*  82 */ "listtype ::= LIST LT fieldtype GT",
 /*  83 */ "constvalue ::= INTEGER_VALUE",
 /*  84 */ "constvalue ::= DOUBLE_VALUE",
 /*  85 */ "constvalue ::= STRING_VALUE",
 /*  86 */ "constvalue ::= IDENTIFIER",
 /*  87 */ "constvalue ::= constlist",
 /*  88 */ "constvalue ::= constmap",
 /*  89 */ "constlist ::= BRACKET_OPEN constvaluelist BRACKET_CLOSE",
 /*  90 */ "constvaluelist ::=",
 /*  91 */ "constvaluelist ::= constvalue constvaluelist",
 /*  92 */ "constvaluelist ::= constvalue LISTSEP constvaluelist",
 /*  93 */ "constmap ::= CURLY_OPEN constmapvaluelist CURLY_CLOSE",
 /*  94 */ "constmapvaluelist ::=",
 /*  95 */ "constmapvaluelist ::= constvalue COLON constvalue constmapvaluelist",
 /*  96 */ "constmapvaluelist ::= constvalue COLON constvalue LISTSEP constmapvaluelist",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
      /* TERMINAL Destructor */
    case 1: /* END_OF_FILE */
    case 2: /* INCLUDE */
    case 3: /* STRING_VALUE */
    case 4: /* CPP_INCLUDE */
    case 5: /* NAMESPACE */
    case 6: /* IDENTIFIER */
    case 7: /* LISTSEP */
    case 8: /* DOC_COMMENT */
    case 9: /* CONST */
    case 10: /* EQ */
    case 11: /* TYPEDEF */
    case 12: /* ENUM */
    case 13: /* CURLY_OPEN */
    case 14: /* CURLY_CLOSE */
    case 15: /* INTEGER_VALUE */
    case 16: /* UNION */
    case 17: /* EXCEPTION */
    case 18: /* STRUCT */
    case 19: /* COLON */
    case 20: /* REQUIRED */
    case 21: /* OPTIONAL */
    case 22: /* SERVICE */
    case 23: /* EXTENDS */
    case 24: /* PAREN_OPEN */
    case 25: /* PAREN_CLOSE */
    case 26: /* ONEWAY */
    case 27: /* VOID */
    case 28: /* THROWS */
    case 29: /* BOOL */
    case 30: /* BYTE */
    case 31: /* I16 */
    case 32: /* I32 */
    case 33: /* I64 */
    case 34: /* DOUBLE */
    case 35: /* STRING */
    case 36: /* BINARY */
    case 37: /* MAP */
    case 38: /* LT */
    case 39: /* GT */
    case 40: /* SET */
    case 41: /* LIST */
    case 42: /* DOUBLE_VALUE */
    case 43: /* BRACKET_OPEN */
    case 44: /* BRACKET_CLOSE */
{
#line 18 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy0);
#line 660 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 59: /* fieldtype */
{
#line 279 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy85); 
#line 366 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy85); 
#line 669 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 60: /* constvalue */
    case 72: /* fieldinitializer */
{
#line 452 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy108);
#line 677 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 61: /* definitiontype */
{
#line 381 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy142); 
#line 684 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 62: /* enumbody */
{
#line 113 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy97);
#line 691 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 63: /* enumitem */
    case 64: /* enumvalue */
{
#line 126 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy38);
#line 699 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 66: /* enuminit */
    case 81: /* basetype */
{
#line 141 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy19);
#line 707 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 67: /* fieldlist */
    case 80: /* throws */
{
#line 189 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy123);
#line 715 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 68: /* field */
    case 69: /* fieldbody */
{
#line 202 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy109);
#line 723 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 75: /* functionlist */
{
#line 289 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy29); 
#line 730 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 76: /* function */
    case 77: /* functionbody */
{
#line 302 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy30); 
#line 738 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 79: /* functiontype */
{
#line 344 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy85);
#line 745 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 83: /* maptype */
{
#line 423 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy71);
#line 752 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 84: /* settype */
{
#line 434 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy149);
#line 759 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 85: /* listtype */
{
#line 443 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy37);
#line 766 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 87: /* constmap */
    case 89: /* constmapvaluelist */
{
#line 520 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy150);
#line 774 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    case 88: /* constvaluelist */
{
#line 497 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy98);
#line 499 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
delete (yypminor->yy98);
#line 783 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
}
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
#line 29 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"

    pParser->setErrorFlag("Stack overflow");
#line 968 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 46, 2 },
  { 47, 0 },
  { 47, 2 },
  { 47, 2 },
  { 47, 2 },
  { 47, 2 },
  { 47, 2 },
  { 47, 2 },
  { 47, 2 },
  { 47, 2 },
  { 47, 2 },
  { 47, 2 },
  { 48, 2 },
  { 49, 2 },
  { 50, 3 },
  { 51, 1 },
  { 51, 2 },
  { 58, 6 },
  { 58, 5 },
  { 52, 4 },
  { 52, 3 },
  { 53, 5 },
  { 53, 6 },
  { 62, 0 },
  { 62, 2 },
  { 63, 2 },
  { 65, 0 },
  { 65, 1 },
  { 64, 2 },
  { 66, 0 },
  { 66, 2 },
  { 55, 5 },
  { 56, 5 },
  { 56, 6 },
  { 54, 5 },
  { 54, 6 },
  { 67, 0 },
  { 67, 2 },
  { 68, 1 },
  { 68, 2 },
  { 69, 5 },
  { 70, 0 },
  { 70, 1 },
  { 72, 0 },
  { 72, 2 },
  { 73, 2 },
  { 71, 0 },
  { 71, 1 },
  { 71, 1 },
  { 57, 6 },
  { 57, 7 },
  { 74, 0 },
  { 74, 2 },
  { 75, 0 },
  { 75, 2 },
  { 76, 1 },
  { 76, 2 },
  { 77, 7 },
  { 77, 8 },
  { 78, 0 },
  { 78, 1 },
  { 79, 1 },
  { 79, 1 },
  { 80, 0 },
  { 80, 4 },
  { 59, 1 },
  { 59, 1 },
  { 61, 1 },
  { 61, 1 },
  { 81, 1 },
  { 81, 1 },
  { 81, 1 },
  { 81, 1 },
  { 81, 1 },
  { 81, 1 },
  { 81, 1 },
  { 81, 1 },
  { 82, 1 },
  { 82, 1 },
  { 82, 1 },
  { 83, 6 },
  { 84, 4 },
  { 85, 4 },
  { 60, 1 },
  { 60, 1 },
  { 60, 1 },
  { 60, 1 },
  { 60, 1 },
  { 60, 1 },
  { 86, 3 },
  { 88, 0 },
  { 88, 2 },
  { 88, 3 },
  { 87, 3 },
  { 89, 0 },
  { 89, 4 },
  { 89, 5 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 0: /* thrift ::= body END_OF_FILE */
#line 33 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yy_destructor(yypParser,1,&yymsp[0].minor);
}
#line 1181 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 12: /* include ::= INCLUDE STRING_VALUE */
#line 47 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  pParser->addInclude(*yymsp[0].minor.yy0);
  delete yymsp[0].minor.yy0;
  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 1190 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 13: /* cppinclude ::= CPP_INCLUDE STRING_VALUE */
#line 52 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yy_destructor(yypParser,4,&yymsp[-1].minor);
  yy_destructor(yypParser,3,&yymsp[0].minor);
}
#line 1198 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 14: /* namespace ::= NAMESPACE IDENTIFIER IDENTIFIER */
#line 55 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  pParser->addNamespace(*yymsp[-1].minor.yy0, *yymsp[0].minor.yy0);
  delete yymsp[-1].minor.yy0;
  delete yymsp[0].minor.yy0;
  yy_destructor(yypParser,5,&yymsp[-2].minor);
}
#line 1208 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 16: /* const ::= constbody LISTSEP */
      case 27: /* enumsep ::= LISTSEP */ yytestcase(yyruleno==27);
#line 62 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yy_destructor(yypParser,7,&yymsp[0].minor);
}
#line 1216 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 17: /* constbody ::= DOC_COMMENT CONST fieldtype IDENTIFIER EQ constvalue */
#line 64 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  QSharedPointer<Parser::Type> t = yymsp[-3].minor.yy85->type();
  pParser->addConst(t, *yymsp[-2].minor.yy0, QSharedPointer<Parser::ConstValue>(yymsp[0].minor.yy108), *yymsp[-5].minor.yy0);
  delete yymsp[-3].minor.yy85;
  delete yymsp[-2].minor.yy0;
  delete yymsp[-5].minor.yy0;
  yy_destructor(yypParser,9,&yymsp[-4].minor);
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1229 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 18: /* constbody ::= CONST fieldtype IDENTIFIER EQ constvalue */
#line 72 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  QSharedPointer<Parser::Type> t = yymsp[-3].minor.yy85->type();
  pParser->addConst(t, *yymsp[-2].minor.yy0, QSharedPointer<Parser::ConstValue>(yymsp[0].minor.yy108), QString());
  delete yymsp[-3].minor.yy85;
  delete yymsp[-2].minor.yy0;
  yy_destructor(yypParser,9,&yymsp[-4].minor);
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1241 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 19: /* typedef ::= DOC_COMMENT TYPEDEF definitiontype IDENTIFIER */
#line 81 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  QSharedPointer<Parser::Type> t = yymsp[-1].minor.yy142->type();
  pParser->addTypedef(*yymsp[0].minor.yy0, t, *yymsp[-3].minor.yy0);
  delete yymsp[-1].minor.yy142;
  delete yymsp[0].minor.yy0;
  delete yymsp[-3].minor.yy0;
  yy_destructor(yypParser,11,&yymsp[-2].minor);
}
#line 1253 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 20: /* typedef ::= TYPEDEF definitiontype IDENTIFIER */
#line 90 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  QSharedPointer<Parser::Type> t = yymsp[-1].minor.yy142->type();
  pParser->addTypedef(*yymsp[0].minor.yy0, t, QString());
  delete yymsp[-1].minor.yy142;
  delete yymsp[0].minor.yy0;
  yy_destructor(yypParser,11,&yymsp[-2].minor);
}
#line 1264 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 21: /* enum ::= ENUM IDENTIFIER CURLY_OPEN enumbody CURLY_CLOSE */
#line 98 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  pParser->addEnumeration(*yymsp[-3].minor.yy0, *yymsp[-1].minor.yy97, QString());
  delete yymsp[-3].minor.yy0;
  delete yymsp[-1].minor.yy97;
  yy_destructor(yypParser,12,&yymsp[-4].minor);
  yy_destructor(yypParser,13,&yymsp[-2].minor);
  yy_destructor(yypParser,14,&yymsp[0].minor);
}
#line 1276 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 22: /* enum ::= DOC_COMMENT ENUM IDENTIFIER CURLY_OPEN enumbody CURLY_CLOSE */
#line 105 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  pParser->addEnumeration(*yymsp[-3].minor.yy0, *yymsp[-1].minor.yy97, *yymsp[-5].minor.yy0);
  delete yymsp[-3].minor.yy0;
  delete yymsp[-1].minor.yy97;
  delete yymsp[-5].minor.yy0;
  yy_destructor(yypParser,12,&yymsp[-4].minor);
  yy_destructor(yypParser,13,&yymsp[-2].minor);
  yy_destructor(yypParser,14,&yymsp[0].minor);
}
#line 1289 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 23: /* enumbody ::= */
#line 115 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy97 = new QList<QPair<QString, QString>>;
}
#line 1296 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 24: /* enumbody ::= enumitem enumbody */
#line 119 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy97 = yymsp[0].minor.yy97;
  yygotominor.yy97->prepend(*yymsp[-1].minor.yy38);
  delete yymsp[-1].minor.yy38;
}
#line 1305 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 25: /* enumitem ::= enumvalue enumsep */
#line 127 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{ yygotominor.yy38 = yymsp[-1].minor.yy38;}
#line 1310 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 28: /* enumvalue ::= IDENTIFIER enuminit */
#line 134 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy38 = new QPair<QString, QString>(*yymsp[-1].minor.yy0, *yymsp[0].minor.yy19);
  delete yymsp[-1].minor.yy0;
  delete yymsp[0].minor.yy19;
}
#line 1319 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 29: /* enuminit ::= */
#line 143 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy19 = new QString;
}
#line 1326 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 30: /* enuminit ::= EQ INTEGER_VALUE */
#line 147 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy19 = yymsp[0].minor.yy0;
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1334 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 31: /* union ::= UNION IDENTIFIER CURLY_OPEN fieldlist CURLY_CLOSE */
#line 152 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  pParser->addUnion(*yymsp[-3].minor.yy0, *yymsp[-1].minor.yy123);
  delete yymsp[-3].minor.yy0;
  delete yymsp[-1].minor.yy123;
  yy_destructor(yypParser,16,&yymsp[-4].minor);
  yy_destructor(yypParser,13,&yymsp[-2].minor);
  yy_destructor(yypParser,14,&yymsp[0].minor);
}
#line 1346 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 32: /* exception ::= EXCEPTION IDENTIFIER CURLY_OPEN fieldlist CURLY_CLOSE */
#line 160 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  pParser->addException(*yymsp[-3].minor.yy0, *yymsp[-1].minor.yy123, QString());
  delete yymsp[-3].minor.yy0;
  delete yymsp[-1].minor.yy123;
  yy_destructor(yypParser,17,&yymsp[-4].minor);
  yy_destructor(yypParser,13,&yymsp[-2].minor);
  yy_destructor(yypParser,14,&yymsp[0].minor);
}
#line 1358 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 33: /* exception ::= DOC_COMMENT EXCEPTION IDENTIFIER CURLY_OPEN fieldlist CURLY_CLOSE */
#line 166 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  pParser->addException(*yymsp[-3].minor.yy0, *yymsp[-1].minor.yy123, *yymsp[-5].minor.yy0);
  delete yymsp[-3].minor.yy0;
  delete yymsp[-1].minor.yy123;
  delete yymsp[-5].minor.yy0;
  yy_destructor(yypParser,17,&yymsp[-4].minor);
  yy_destructor(yypParser,13,&yymsp[-2].minor);
  yy_destructor(yypParser,14,&yymsp[0].minor);
}
#line 1371 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 34: /* struct ::= STRUCT IDENTIFIER CURLY_OPEN fieldlist CURLY_CLOSE */
#line 175 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  pParser->addStructure(*yymsp[-3].minor.yy0, *yymsp[-1].minor.yy123, QString());
  delete yymsp[-3].minor.yy0;
  delete yymsp[-1].minor.yy123;
  yy_destructor(yypParser,18,&yymsp[-4].minor);
  yy_destructor(yypParser,13,&yymsp[-2].minor);
  yy_destructor(yypParser,14,&yymsp[0].minor);
}
#line 1383 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 35: /* struct ::= DOC_COMMENT STRUCT IDENTIFIER CURLY_OPEN fieldlist CURLY_CLOSE */
#line 181 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  pParser->addStructure(*yymsp[-3].minor.yy0, *yymsp[-1].minor.yy123, *yymsp[-5].minor.yy0);
  delete yymsp[-3].minor.yy0;
  delete yymsp[-1].minor.yy123;
  delete yymsp[-5].minor.yy0;
  yy_destructor(yypParser,18,&yymsp[-4].minor);
  yy_destructor(yypParser,13,&yymsp[-2].minor);
  yy_destructor(yypParser,14,&yymsp[0].minor);
}
#line 1396 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 36: /* fieldlist ::= */
      case 63: /* throws ::= */ yytestcase(yyruleno==63);
#line 191 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy123 = new QList<Parser::Field>;
}
#line 1404 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 37: /* fieldlist ::= fieldlist field */
#line 195 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy123 = yymsp[-1].minor.yy123;
  yygotominor.yy123->append(*yymsp[0].minor.yy109);
  delete yymsp[0].minor.yy109;
}
#line 1413 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 38: /* field ::= fieldbody */
#line 203 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy109 = yymsp[0].minor.yy109;}
#line 1418 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 39: /* field ::= fieldbody LISTSEP */
#line 204 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy109 = yymsp[-1].minor.yy109;  yy_destructor(yypParser,7,&yymsp[0].minor);
}
#line 1424 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 40: /* fieldbody ::= fieldidoption fieldreq fieldtype IDENTIFIER fieldinitializer */
#line 209 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy109 = new Parser::Field;
  yygotominor.yy109->id = yymsp[-4].minor.yy112;
  yygotominor.yy109->required = yymsp[-3].minor.yy110;
  yygotominor.yy109->type = QSharedPointer<Parser::Type>(yymsp[-2].minor.yy85->type());
  yygotominor.yy109->name = *yymsp[-1].minor.yy0;
  yygotominor.yy109->initializer = QSharedPointer<Parser::ConstValue>(yymsp[0].minor.yy108);
  delete yymsp[-1].minor.yy0;
}
#line 1437 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 41: /* fieldidoption ::= */
#line 221 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy112 = -1;
}
#line 1444 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 42: /* fieldidoption ::= fieldid */
#line 225 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy112 = yymsp[0].minor.yy112;
}
#line 1451 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 43: /* fieldinitializer ::= */
#line 232 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy108 = nullptr;
}
#line 1458 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 44: /* fieldinitializer ::= EQ constvalue */
#line 236 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy108 = yymsp[0].minor.yy108;
  yy_destructor(yypParser,10,&yymsp[-1].minor);
}
#line 1466 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 45: /* fieldid ::= INTEGER_VALUE COLON */
#line 242 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy112 = yymsp[-1].minor.yy0->toInt();
  delete yymsp[-1].minor.yy0;
  yy_destructor(yypParser,19,&yymsp[0].minor);
}
#line 1475 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 46: /* fieldreq ::= */
#line 249 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy110 = Parser::Field::RequiredFlag::Default;
}
#line 1482 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 47: /* fieldreq ::= REQUIRED */
#line 253 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy110 = Parser::Field::RequiredFlag::Required;
  yy_destructor(yypParser,20,&yymsp[0].minor);
}
#line 1490 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 48: /* fieldreq ::= OPTIONAL */
#line 257 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy110 = Parser::Field::RequiredFlag::Optional;
  yy_destructor(yypParser,21,&yymsp[0].minor);
}
#line 1498 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 49: /* service ::= SERVICE IDENTIFIER extends CURLY_OPEN functionlist CURLY_CLOSE */
#line 263 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  pParser->addService(*yymsp[-4].minor.yy0, yymsp[-3].minor.yy19 ? *yymsp[-3].minor.yy19 : QString(), *yymsp[-1].minor.yy29, QString());
  delete yymsp[-4].minor.yy0;
  delete yymsp[-3].minor.yy19;
  delete yymsp[-1].minor.yy29;
  yy_destructor(yypParser,22,&yymsp[-5].minor);
  yy_destructor(yypParser,13,&yymsp[-2].minor);
  yy_destructor(yypParser,14,&yymsp[0].minor);
}
#line 1511 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 50: /* service ::= DOC_COMMENT SERVICE IDENTIFIER extends CURLY_OPEN functionlist CURLY_CLOSE */
#line 270 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  pParser->addService(*yymsp[-4].minor.yy0, yymsp[-3].minor.yy19 ? *yymsp[-3].minor.yy19 : QString(), *yymsp[-1].minor.yy29, *yymsp[-6].minor.yy0);
  delete yymsp[-4].minor.yy0;
  delete yymsp[-3].minor.yy19;
  delete yymsp[-1].minor.yy29;
  delete yymsp[-6].minor.yy0;
  yy_destructor(yypParser,22,&yymsp[-5].minor);
  yy_destructor(yypParser,13,&yymsp[-2].minor);
  yy_destructor(yypParser,14,&yymsp[0].minor);
}
#line 1525 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 51: /* extends ::= */
#line 280 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy19 = nullptr;
}
#line 1532 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 52: /* extends ::= EXTENDS IDENTIFIER */
#line 284 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy19 = yymsp[0].minor.yy0;
  yy_destructor(yypParser,23,&yymsp[-1].minor);
}
#line 1540 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 53: /* functionlist ::= */
#line 291 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy29 = new QList<Parser::Function>;
}
#line 1547 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 54: /* functionlist ::= functionlist function */
#line 295 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy29 = yymsp[-1].minor.yy29;
  yymsp[-1].minor.yy29->append(*yymsp[0].minor.yy30);
  delete yymsp[0].minor.yy30;
}
#line 1556 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 55: /* function ::= functionbody */
#line 303 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy30 = yymsp[0].minor.yy30;}
#line 1561 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 56: /* function ::= functionbody LISTSEP */
#line 304 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy30 = yymsp[-1].minor.yy30;  yy_destructor(yypParser,7,&yymsp[0].minor);
}
#line 1567 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 57: /* functionbody ::= oneway functiontype IDENTIFIER PAREN_OPEN fieldlist PAREN_CLOSE throws */
#line 310 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy30 = new Parser::Function;
  yygotominor.yy30->isOneway = yymsp[-6].minor.yy137;
  yygotominor.yy30->type = yymsp[-5].minor.yy85->type();
  yygotominor.yy30->name = *yymsp[-4].minor.yy0;
  yygotominor.yy30->params = *yymsp[-2].minor.yy123;
  yygotominor.yy30->throws = *yymsp[0].minor.yy123;
  yygotominor.yy30->docComment = "";
  delete yymsp[-5].minor.yy85;
  delete yymsp[-4].minor.yy0;
  delete yymsp[-2].minor.yy123;
  delete yymsp[0].minor.yy123;
  yy_destructor(yypParser,24,&yymsp[-3].minor);
  yy_destructor(yypParser,25,&yymsp[-1].minor);
}
#line 1586 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 58: /* functionbody ::= DOC_COMMENT oneway functiontype IDENTIFIER PAREN_OPEN fieldlist PAREN_CLOSE throws */
#line 324 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy30 = new Parser::Function;
  yygotominor.yy30->isOneway = yymsp[-6].minor.yy137;
  yygotominor.yy30->type = yymsp[-5].minor.yy85->type();
  yygotominor.yy30->name = *yymsp[-4].minor.yy0;
  yygotominor.yy30->params = *yymsp[-2].minor.yy123;
  yygotominor.yy30->throws = *yymsp[0].minor.yy123;
  yygotominor.yy30->docComment = *yymsp[-7].minor.yy0;
  delete yymsp[-5].minor.yy85;
  delete yymsp[-4].minor.yy0;
  delete yymsp[-2].minor.yy123;
  delete yymsp[0].minor.yy123;
  delete yymsp[-7].minor.yy0;
  yy_destructor(yypParser,24,&yymsp[-3].minor);
  yy_destructor(yypParser,25,&yymsp[-1].minor);
}
#line 1606 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 59: /* oneway ::= */
#line 340 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy137 = false;}
#line 1611 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 60: /* oneway ::= ONEWAY */
#line 341 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy137 = true;  yy_destructor(yypParser,26,&yymsp[0].minor);
}
#line 1617 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 61: /* functiontype ::= fieldtype */
#line 346 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy85 = yymsp[0].minor.yy85;
}
#line 1624 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 62: /* functiontype ::= VOID */
#line 350 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy85 = new VoidType;
  yy_destructor(yypParser,27,&yymsp[0].minor);
}
#line 1632 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 64: /* throws ::= THROWS PAREN_OPEN fieldlist PAREN_CLOSE */
#line 361 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy123 = yymsp[-1].minor.yy123;
  yy_destructor(yypParser,28,&yymsp[-3].minor);
  yy_destructor(yypParser,24,&yymsp[-2].minor);
  yy_destructor(yypParser,25,&yymsp[0].minor);
}
#line 1642 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 65: /* fieldtype ::= IDENTIFIER */
#line 368 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  Identifier_Fieldtype* p = new Identifier_Fieldtype();
  p->identifier = *yymsp[0].minor.yy0;
  yygotominor.yy85 = p;
  delete yymsp[0].minor.yy0;
}
#line 1652 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 66: /* fieldtype ::= definitiontype */
#line 375 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy85 = yymsp[0].minor.yy142;
}
#line 1659 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 67: /* definitiontype ::= basetype */
#line 383 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  Basename_Definitiontype* p = new Basename_Definitiontype();
  p->basetype = *yymsp[0].minor.yy19;
  yygotominor.yy142 = p;
  delete yymsp[0].minor.yy19;
}
#line 1669 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 68: /* definitiontype ::= containertype */
#line 390 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  Containertype_Definitiontype* p = new Containertype_Definitiontype();
  p->containertype = yymsp[0].minor.yy16;
  yygotominor.yy142 = p;
}
#line 1678 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 69: /* basetype ::= BOOL */
#line 398 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy19 = new QString("bool");  yy_destructor(yypParser,29,&yymsp[0].minor);
}
#line 1684 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 70: /* basetype ::= BYTE */
#line 399 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy19 = new QString("byte");  yy_destructor(yypParser,30,&yymsp[0].minor);
}
#line 1690 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 71: /* basetype ::= I16 */
#line 400 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy19 = new QString("i16");  yy_destructor(yypParser,31,&yymsp[0].minor);
}
#line 1696 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 72: /* basetype ::= I32 */
#line 401 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy19 = new QString("i32");  yy_destructor(yypParser,32,&yymsp[0].minor);
}
#line 1702 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 73: /* basetype ::= I64 */
#line 402 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy19 = new QString("i64");  yy_destructor(yypParser,33,&yymsp[0].minor);
}
#line 1708 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 74: /* basetype ::= DOUBLE */
#line 403 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy19 = new QString("double");  yy_destructor(yypParser,34,&yymsp[0].minor);
}
#line 1714 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 75: /* basetype ::= STRING */
#line 404 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy19 = new QString("string");  yy_destructor(yypParser,35,&yymsp[0].minor);
}
#line 1720 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 76: /* basetype ::= BINARY */
#line 405 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{yygotominor.yy19 = new QString("binary");  yy_destructor(yypParser,36,&yymsp[0].minor);
}
#line 1726 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 77: /* containertype ::= maptype */
#line 410 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy16 = yymsp[0].minor.yy71;
}
#line 1733 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 78: /* containertype ::= settype */
#line 414 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy16 = yymsp[0].minor.yy149;
}
#line 1740 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 79: /* containertype ::= listtype */
#line 418 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy16 = yymsp[0].minor.yy37;
}
#line 1747 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 80: /* maptype ::= MAP LT fieldtype LISTSEP fieldtype GT */
#line 425 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy71 = new Maptype();
  yygotominor.yy71->keyType = yymsp[-3].minor.yy85->type();
  yygotominor.yy71->valueType = yymsp[-1].minor.yy85->type();
  delete yymsp[-3].minor.yy85;
  delete yymsp[-1].minor.yy85;
  yy_destructor(yypParser,37,&yymsp[-5].minor);
  yy_destructor(yypParser,38,&yymsp[-4].minor);
  yy_destructor(yypParser,7,&yymsp[-2].minor);
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1762 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 81: /* settype ::= SET LT fieldtype GT */
#line 436 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy149 = new Settype();
  yygotominor.yy149->valueType = yymsp[-1].minor.yy85->type();
  delete yymsp[-1].minor.yy85;
  yy_destructor(yypParser,40,&yymsp[-3].minor);
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1774 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 82: /* listtype ::= LIST LT fieldtype GT */
#line 445 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy37 = new Listtype();
  yygotominor.yy37->valueType = yymsp[-1].minor.yy85->type();
  delete yymsp[-1].minor.yy85;
  yy_destructor(yypParser,41,&yymsp[-3].minor);
  yy_destructor(yypParser,38,&yymsp[-2].minor);
  yy_destructor(yypParser,39,&yymsp[0].minor);
}
#line 1786 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 83: /* constvalue ::= INTEGER_VALUE */
#line 454 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  Parser::IntegerValue* p = new Parser::IntegerValue;
  p->value = *yymsp[0].minor.yy0;
  yygotominor.yy108 = p;
  delete yymsp[0].minor.yy0;
}
#line 1796 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 84: /* constvalue ::= DOUBLE_VALUE */
#line 461 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  Parser::DoubleValue* p = new Parser::DoubleValue;
  p->value = *yymsp[0].minor.yy0;
  yygotominor.yy108 = p;
  delete yymsp[0].minor.yy0;
}
#line 1806 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 85: /* constvalue ::= STRING_VALUE */
#line 468 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  Parser::StringValue* p = new Parser::StringValue;
  p->value = *yymsp[0].minor.yy0;
  yygotominor.yy108 = p;
  delete yymsp[0].minor.yy0;
}
#line 1816 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 86: /* constvalue ::= IDENTIFIER */
#line 475 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  Parser::IdentifierValue* p = new Parser::IdentifierValue;
  p->value = *yymsp[0].minor.yy0;
  yygotominor.yy108 = p;
  delete yymsp[0].minor.yy0;
}
#line 1826 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 87: /* constvalue ::= constlist */
#line 482 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  Parser::ListValue* p = new Parser::ListValue;
  p->values = *yymsp[0].minor.yy98;
  yygotominor.yy108 = p;
  delete yymsp[0].minor.yy98;
}
#line 1836 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 88: /* constvalue ::= constmap */
#line 489 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  Parser::MapValue* p = new Parser::MapValue;
  p->values = *yymsp[0].minor.yy150;
  yygotominor.yy108 = p;
  delete yymsp[0].minor.yy150;
}
#line 1846 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 89: /* constlist ::= BRACKET_OPEN constvaluelist BRACKET_CLOSE */
#line 501 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy98 = yymsp[-1].minor.yy98;
  yy_destructor(yypParser,43,&yymsp[-2].minor);
  yy_destructor(yypParser,44,&yymsp[0].minor);
}
#line 1855 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 90: /* constvaluelist ::= */
#line 505 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy98 = new QList<QSharedPointer<Parser::ConstValue>>;
}
#line 1862 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 91: /* constvaluelist ::= constvalue constvaluelist */
#line 509 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy98 = yymsp[0].minor.yy98;
  yygotominor.yy98->prepend(QSharedPointer<Parser::ConstValue>(yymsp[-1].minor.yy108));
}
#line 1870 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 92: /* constvaluelist ::= constvalue LISTSEP constvaluelist */
#line 514 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy98 = yymsp[0].minor.yy98;
  yygotominor.yy98->prepend(QSharedPointer<Parser::ConstValue>(yymsp[-2].minor.yy108));
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1879 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 93: /* constmap ::= CURLY_OPEN constmapvaluelist CURLY_CLOSE */
#line 524 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy150 = yymsp[-1].minor.yy150;
  yy_destructor(yypParser,13,&yymsp[-2].minor);
  yy_destructor(yypParser,14,&yymsp[0].minor);
}
#line 1888 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 94: /* constmapvaluelist ::= */
#line 528 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy150 = new QList<QPair<QSharedPointer<Parser::ConstValue>, QSharedPointer<Parser::ConstValue>>>;
}
#line 1895 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 95: /* constmapvaluelist ::= constvalue COLON constvalue constmapvaluelist */
#line 532 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy150 = yymsp[0].minor.yy150;
  auto p = qMakePair(QSharedPointer<Parser::ConstValue>(yymsp[-3].minor.yy108), QSharedPointer<Parser::ConstValue>(yymsp[-1].minor.yy108));
  yygotominor.yy150->prepend(p);
  yy_destructor(yypParser,19,&yymsp[-2].minor);
}
#line 1905 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      case 96: /* constmapvaluelist ::= constvalue COLON constvalue LISTSEP constmapvaluelist */
#line 538 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"
{
  yygotominor.yy150 = yymsp[0].minor.yy150;
  auto p = qMakePair(QSharedPointer<Parser::ConstValue>(yymsp[-4].minor.yy108), QSharedPointer<Parser::ConstValue>(yymsp[-2].minor.yy108));
  yygotominor.yy150->prepend(p);
  yy_destructor(yypParser,19,&yymsp[-3].minor);
  yy_destructor(yypParser,7,&yymsp[-1].minor);
}
#line 1916 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
        break;
      default:
      /* (1) body ::= */ yytestcase(yyruleno==1);
      /* (2) body ::= include body */ yytestcase(yyruleno==2);
      /* (3) body ::= cppinclude body */ yytestcase(yyruleno==3);
      /* (4) body ::= namespace body */ yytestcase(yyruleno==4);
      /* (5) body ::= const body */ yytestcase(yyruleno==5);
      /* (6) body ::= typedef body */ yytestcase(yyruleno==6);
      /* (7) body ::= enum body */ yytestcase(yyruleno==7);
      /* (8) body ::= struct body */ yytestcase(yyruleno==8);
      /* (9) body ::= union body */ yytestcase(yyruleno==9);
      /* (10) body ::= exception body */ yytestcase(yyruleno==10);
      /* (11) body ::= service body */ yytestcase(yyruleno==11);
      /* (15) const ::= constbody */ yytestcase(yyruleno==15);
      /* (26) enumsep ::= */ yytestcase(yyruleno==26);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
#line 25 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"

    pParser->setErrorFlag("Parser failure");
#line 1980 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 21 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.y"

    pParser->setErrorFlag("Syntax error");
#line 1998 "D:\\sources\\lib\\QEverCloud\\src\\ThriftParser\\thrift_lemon.cpp"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
