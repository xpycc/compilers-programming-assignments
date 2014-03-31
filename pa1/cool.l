/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */

int nested;
char inv_str[100];

%}

%x COMMENTS STRINGS STRERR

/*
 * Define names for regular expressions here.
 */

A				[aA]
B				[bB]
C				[cC]
D				[dD]
E				[eE]
F				[fF]
G				[gG]
H				[hH]
I				[iI]
J				[jJ]
K				[kK]
L				[lL]
M				[mM]
N				[nN]
O				[oO]
P				[pP]
Q				[qQ]
R				[rR]
S				[sS]
T				[tT]
U				[uU]
V				[vV]
W				[wW]
X				[xX]
Y				[yY]
Z				[zZ]

DARROW			=>
INT_CONST		[0-9]+
BOOL_CONST		t[rR][uU][eE]|f[aA][lL][sS][eE]
TYPEID			[A-Z][a-zA-Z0-9_]*
OBJECTID		[a-z][a-zA-Z0-9_]*
ASSIGN 			<-
LE 				<=

SINGLE_OP		"."|"@"|"~"|"*"|"/"|"+"|"-"|"<"|"="|":"|"("|")"|"{"|"}"|","|";"
WHITESPACE		\f|\r|\t|\v|" "

NEW_LINE		\n
LINE_COMMENT	"--".*

%%

{LINE_COMMENT}	/* discard */
{NEW_LINE}		{ curr_lineno++; }

 /*
  *  Nested comments
  */
"(*"			{ nested++; BEGIN(COMMENTS); }
"*)"			{
				yylval.error_msg = "Unmatched *)";
				return ERROR;
				}
<COMMENTS>"(*"	{ nested++; }
<COMMENTS>"*)"	{ if (--nested == 0) BEGIN(INITIAL); }
<COMMENTS>. 	/* discard */
<COMMENTS>\n	{ curr_lineno++; }
<COMMENTS><<EOF>> {
				yylval.error_msg = "EOF in comment";
				BEGIN(INITIAL);
				return ERROR;
				}

 /*
  *  The multiple-character operators.
  */
{DARROW}		{ return DARROW; }
{LE}			{ return LE; }
{ASSIGN}		{ return ASSIGN; }
{SINGLE_OP}		{ return yytext[0]; }

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */

{C}{L}{A}{S}{S}				{ return CLASS; }
{E}{L}{S}{E}				{ return ELSE; }
{F}{I}						{ return FI; }
{I}{F}						{ return IF; }
{I}{N}						{ return IN; }
{I}{N}{H}{E}{R}{I}{T}{S}	{ return INHERITS; }
{L}{E}{T}					{ return LET; }
{L}{O}{O}{P}				{ return LOOP; }
{P}{O}{O}{L}				{ return POOL; }
{T}{H}{E}{N}				{ return THEN; }
{W}{H}{I}{L}{E}				{ return WHILE; }
{C}{A}{S}{E}				{ return CASE; }
{E}{S}{A}{C}				{ return ESAC; }
{O}{F}						{ return OF; }
{N}{E}{W}					{ return NEW; }
{I}{S}{V}{O}{I}{D}			{ return ISVOID; }
{N}{O}{T}					{ return NOT; }

 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */
{INT_CONST}		{
				yylval.symbol = inttable.add_string(yytext);
				return INT_CONST;
				}
{BOOL_CONST}	{
				yylval.boolean = yytext[0] == 't';
				return BOOL_CONST;
				}
\"				{ BEGIN(STRINGS); string_buf_ptr = string_buf; }
<STRINGS>\"		{
				BEGIN(INITIAL);
				yylval.symbol = stringtable.add_string(string_buf,
						string_buf_ptr - string_buf);
				return STR_CONST;
				}
<STRINGS>\0		|
<STRINGS>\\\0	{
				BEGIN(STRERR);
				yylval.error_msg = "String contains null character";
				return ERROR;
				}
<STRINGS>.		{
				if (string_buf_ptr == string_buf + MAX_STR_CONST - 1) {
					BEGIN(STRERR);
					yylval.error_msg = "String constant too long";
					return ERROR;
				}
				*string_buf_ptr++ = yytext[0];
				}
<STRINGS>\\\n	{
				++curr_lineno;
				if (string_buf_ptr == string_buf + MAX_STR_CONST - 1) {
					BEGIN(STRERR);
					yylval.error_msg = "String constant too long";
					return ERROR;
				}
				*string_buf_ptr++ = '\n';
				}
<STRINGS>\\.	{
				if (string_buf_ptr == string_buf + MAX_STR_CONST - 1) {
					BEGIN(STRERR);
					yylval.error_msg = "String constant too long";
					return ERROR;
				}
				switch (yytext[1]) {
					case 'b': *string_buf_ptr++ = '\b'; break;
					case 't': *string_buf_ptr++ = '\t'; break;
					case 'n': *string_buf_ptr++ = '\n'; break;
					case 'f': *string_buf_ptr++ = '\f'; break;
					default : *string_buf_ptr++ = yytext[1]; break;
				}
				}
<STRINGS>\n 	{
				yylval.error_msg = "Unterminated string constant";
				BEGIN(INITIAL);
				++curr_lineno;
				return ERROR;
				}
<STRINGS><<EOF>> {
				yylval.error_msg = "Unterminated string constant";
				BEGIN(INITIAL);
				return ERROR;
				}
<STRERR>\n		{ BEGIN(INITIAL); ++curr_lineno; }
<STRERR>\"		{ BEGIN(INITIAL); }
<STRERR>\\\n	{ ++curr_lineno; }
<STRERR>.		/* discard */

{TYPEID}		{
				yylval.symbol = idtable.add_string(yytext);
				return TYPEID;
				}
{OBJECTID}		{
				yylval.symbol = idtable.add_string(yytext);
				return OBJECTID;
				}

 /*
  * Make up other things here.
  */

{WHITESPACE}	/* discard */
.				{
				strcpy(inv_str, yytext);
				yylval.error_msg = inv_str;
				return ERROR;
				}
<<EOF>>			{ yyterminate(); }

%%
