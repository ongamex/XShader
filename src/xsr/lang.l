%option reentrant 
%option bison-bridge 
%option bison-locations
%option yylineno
%option never-interactive
%option noyywrap
%option nounistd

%{
#include <stdio.h>
#include <string>
#include "ast.h"
#include "lang.tab.h"
#include "lang.yystype.h"

// [TODO] Ivestigate when ECHO is called and eventuall add a proper fix.
// I've added this because in some caes flex will call fwrite and some other stange function
// causing casing a crash in non console application.
#define ECHO do {} while(false)

#define YY_USER_ACTION yylloc->first_line = yylloc->last_line = yylineno;

%}

%%


"//".*[\n]												;
"#line"[ ]+[1-9][0-9]*(.*)?								{ ast->addLineMarker(LineMarker(yylineno, yytext)); }
"for"													return FOR;
"if"													return IF;
"else"													return ELSE;
"while"													return WHILE;
"in"													return IN;
"out"													return OUT;
"inout"													return INOUT;
"attribute"												return ATTRIBUTE;
"uniform"												return UNIFORM;
"native_code"											return NATIVE_CODE;
"return"												return RETURN;
[A-Za-z_][A-Za-z_0-9]* 									{ yylval->str_val = std::string(yytext); return IDENT; }
[0-9]*"."[0-9]+([eE][0-9][0-9]*)?f?						{ yylval->float_val = atof(yytext); return NUM_FLOAT; }
[0-9][0-9]*												{ yylval->int_val = atoi(yytext); return NUM_INT; }
"&&"													return AND;
"||"													return OR;
"<="													return LE;
">="													return GE;
"=="													return EQUALS;
"!="													return NOTEQUALS;
[-()<>=+*/;{},.:\[\]] 									return *yytext;
%%

	//The function that knows how to parse the language.
namespace XSR {
	bool XSParseExpression(const char* code, Ast* ast)
	{
		yyscan_t myscanner;
		yylex_init(&myscanner);
		struct yyguts_t * yyg = (struct yyguts_t*)myscanner;
		
		yy_delete_buffer(YY_CURRENT_BUFFER,myscanner);
		
		/*Copy string into new buffer and Switch buffers*/
		yy_scan_string(code, myscanner);
		
		// [HACK] Those are not properly initialized for non file parsers
		// and becuase of that we get garbage in yyerror...
		yylineno = 1;
        yycolumn = 0;
		
		bool nasi = yyparse(myscanner, ast);
		yylex_destroy(myscanner);
		return nasi;
	}
}