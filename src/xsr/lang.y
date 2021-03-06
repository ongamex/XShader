%code requires {
	#include "lang.yystype.h"
}

%define api.pure full
%locations
%no-lines
%error-verbose
%parse-param {yyscan_t scanner}
%parse-param {Ast* ast}
%lex-param {yyscan_t scanner}
%lex-param { Ast* ast }

%code provides {
	#define YY_DECL \
	   int yylex(YYSTYPE* yylval_param, YYLTYPE* yylloc_param, yyscan_t yyscanner, Ast* ast)
	YY_DECL;
	
	void yyerror(YYLTYPE* loc, yyscan_t yyscanner, Ast* ast, const char* msg);
}


%{
typedef void* yyscan_t;

#include <string>
#include <cstring>
#include <math.h>
#include <map>
#include "ast.h"
#include "lang.tab.h"
#include "lang.yystype.h"


bool parseExpression(const std::string& inp);

// add a convert operator from YYLTYPE to Location
Location toLocation(const YYLTYPE& yyl) {
	Location retval;
	retval.line = yyl.first_line;
	retval.column = yyl.first_column;
	return retval;
}

%}

// Token declaration.
%token 		AND OR LE GE EQUALS NOTEQUALS
%token 		WHILE FOR IN OUT INOUT

// if, if-else expression
%token 		IF 
%nonassoc				NONASSOC_IF
%nonassoc				ELSE 
	
%token <str_val>		IDENT CODE_STRING RETURN
%token <float_val>		NUM_FLOAT
%token <int_val>		NUM_INT
%token 					ATTRIBUTE VARYING UNIFORM NATIVE_CODE

// Token precedence.

%left AND OR
%left EQUALS NOTEQUALS
%left LE '<' GE '>'
%left '+' '-'
%left '*' '/'
%left '[' ']'
%left '.'

%nonassoc NONASSOC_UNARY


// Grammar expression types (from yystype).
%type <node>		fncall_args expr_fncall fndecl_vardecl_var fndecl_vardecl
%type <node>		expr_base expr stmt expr_block 
%type <node>		expr_block_expressions
%type <node>		vardecl_var_list vardecl assign_stmt
%type <node>		stmt_list function_decl 
%type <node>		program grammar_elem grammar_list
%type <node>		shader_global_variables // These actually have no type.
%type <node>        type_node

// The root.
%start program

%%

program : grammar_list { ast->program = $1; $$ = $1; }

grammar_elem :
		function_decl 			{ $$ = $1; }
	|	shader_global_variables	{ $$ = nullptr; } // This is not a node, it just modifies the AST. 
	;

grammar_list : 

		grammar_elem  				
		{ 
			// Create a list of program elements(only functions so far).
			$$ = ast->push<ProgramElem>(toLocation(@1)); 
			
			// A program element is not necessary a node. 
			// For example vertexAttribs/varyings/uniforms they just do a add themselves
			// to a container containing all the declarations.
			if($1 != nullptr) $$->As<ProgramElem>().nodes.push_back($1); 
		}
	|	
		grammar_list grammar_elem	
		{ 
			if ($2 != nullptr) $1->As<ProgramElem>().nodes.push_back($2); 
			$$ = $1;
		}
	;
	
	//-------------------------------------------------
	// A genric type mentioning.
	//-------------------------------------------------
	type_node : 
		  IDENT						{ $$ = ast->push<TypeDeclNode>(toLocation(@1)); $$->As<TypeDeclNode>().resolvedType = TypeDesc(false, $1);}
		| type_node '[' NUM_INT ']'	{ $$ = $1; $$->As<TypeDeclNode>().resolvedType.AddArrayLevel($3); }
	
	//-------------------------------------------------
	// Global variables, uniforms, varyings, attributes
	//-------------------------------------------------
shader_global_variables : 
		// These aren't real nodes for now in order to reduce comprexity...
		ATTRIBUTE type_node IDENT ':' IDENT ';'	{ $$ = nullptr; ast->vertexAttribs.push_back(VertexAttribs((TypeDeclNode*)$2, $3, $5)); }
	|	IN        type_node IDENT ';'			{ $$ = nullptr; ast->stageInputVaryings.push_back(Varyings((TypeDeclNode*)$2, $3)); }
	|	OUT       type_node IDENT ';'			{ $$ = nullptr; ast->stageOutputVaryings.push_back(Varyings((TypeDeclNode*)$2, $3)); }
	|	UNIFORM	  type_node IDENT ';'			{ $$ = nullptr; ast->uniforms.push_back(Uniforms((TypeDeclNode*)$2, $3)); }
	;
	
	//-------------------------------------------------
	// Function Declaration.
	//-------------------------------------------------
	
	// A single variable for function declarations.
fndecl_vardecl_var : 
		IDENT IDENT 				{ $$ = ast->push<FnDeclArgVarDecl>(toLocation(@1), TypeDesc(false, $1), $2, nullptr, FNAT_In   ); }
	|	IDENT IDENT '=' expr		{ $$ = ast->push<FnDeclArgVarDecl>(toLocation(@1), TypeDesc(false, $1), $2, $4     , FNAT_In   ); }
	|	IN IDENT IDENT 				{ $$ = ast->push<FnDeclArgVarDecl>(toLocation(@1), TypeDesc(false, $2), $3, nullptr, FNAT_In	); }
	|	IN IDENT IDENT '=' expr		{ $$ = ast->push<FnDeclArgVarDecl>(toLocation(@1), TypeDesc(false, $2), $3, $5     , FNAT_In	); }
	|	OUT IDENT IDENT 			{ $$ = ast->push<FnDeclArgVarDecl>(toLocation(@1), TypeDesc(false, $2), $3, nullptr, FNAT_Out  ); }
	|	OUT IDENT IDENT '=' expr	{ $$ = ast->push<FnDeclArgVarDecl>(toLocation(@1), TypeDesc(false, $2), $3, $5     , FNAT_Out  ); }
	|	INOUT IDENT IDENT 			{ $$ = ast->push<FnDeclArgVarDecl>(toLocation(@1), TypeDesc(false, $2), $3, nullptr, FNAT_InOut); }
	|	INOUT IDENT IDENT '=' expr	{ $$ = ast->push<FnDeclArgVarDecl>(toLocation(@1), TypeDesc(false, $2), $3, $5     , FNAT_InOut); }
	;
	
	// A list of variables for the function declaration.
	// This must be used only for function declaration variables.
	// Basically this create the function declaration node.
	// the node is later finished by function_decl rule.
fndecl_vardecl : 
												{ $$ = ast->push<FuncDecl>(Location()); }
	|	fndecl_vardecl_var						{ $$ = ast->push<FuncDecl>(toLocation(@1)); ((FuncDecl*)$$)->args.push_back($1); }
	|	fndecl_vardecl ',' fndecl_vardecl_var	{ $1->As<FuncDecl>().args.push_back($3); $$ = $1; }

	
	// The function delectation itself.
	// fndecl_vardecl create the function call node, 
	// we need to just add the return type name and statement.
function_decl : 
	IDENT IDENT '(' fndecl_vardecl ')' '{' stmt_list '}'	{ 
		auto& funcDecl = $4->As<FuncDecl>();
		funcDecl.retType = TypeDesc(false, $1);
		funcDecl.name = $2;
		funcDecl.stmt = $7;
		$$ = $4;
	}
	;
	
	//-------------------------------------------------
	// Variable declaration statement.
	//-------------------------------------------------
	
	// A single variable(or a variable list followed by a single variable) and the optional assigment expression
	// type var, var = expr;
vardecl_var_list : 
		IDENT 								{ $$ = ast->push<VarDecl>(toLocation(@1), $1, nullptr); }
	|	IDENT '=' expr 						{ $$ = ast->push<VarDecl>(toLocation(@1), $1, $3); }
	|	vardecl_var_list ',' IDENT 			{ 
			$1->As<VarDecl>().ident.push_back($3);
			$1->As<VarDecl>().expr.push_back(nullptr);
			$$ = $1;
		}
	|	vardecl_var_list ',' IDENT '=' expr	{ 
			$$ = $1; 
			$$->As<VarDecl>().ident.push_back($3);
			$$->As<VarDecl>().expr.push_back($5);
		}
	
	// The actual variable declaration
vardecl :
			type_node vardecl_var_list	{ $2->As<VarDecl>().typeNode = static_cast<TypeDeclNode*>($1); $$ = $2; }
	;
	
	//-------------------------------------------------
	// Statements.
	//-------------------------------------------------
	
stmt : 
		vardecl ';'									{ $1->hasSemicolon = true; ; $$ = $1; }
	|	expr ';' 									{ $1->hasSemicolon = true; $$ = $1; }
	|	assign_stmt ';' 							{ $1->hasSemicolon = true; $$ = $1; }
	|	FOR '(' vardecl ';' expr ';' expr ')' stmt	{ $$ = ast->push<StmtFor>(toLocation(@1), $3, $5, $7, $9); }
	|	WHILE '(' expr ')' stmt 					{ $$ = ast->push<StmtWhile>(toLocation(@1),$3, $5); }
	|	IF '(' expr ')' stmt %prec NONASSOC_IF		{ $$ = ast->push<StmtIf>(toLocation(@1), $3, $5, nullptr); }
	|	IF '(' expr ')' stmt ELSE stmt				{ $$ = ast->push<StmtIf>(toLocation(@1), $3, $5, $7); }
	|	'{' stmt_list '}' 							{ $2->inBlock = true; $$ = $2; }
	|	NATIVE_CODE '('  CODE_STRING  ')' ';'		{ $$ = ast->push<StmtNativeCode>(toLocation(@1), $3); }
	|	RETURN expr ';'								{ $$ = ast->push<StmtReturn>(toLocation(@1), $2); }
	|	RETURN ';'									{ $$ = ast->push<StmtReturn>(toLocation(@1)); }
	;

		//[TODO] This should become something like expr = expr at least because of array indexing.
assign_stmt : 
		expr '=' expr				{ $$ = ast->push<Assign>(toLocation(@1), $1, $3); }
	;
	
	// A list of statements.
stmt_list : 
		stmt 				{ $$ = ast->push<StmtList>(toLocation(@1)); $$->As<StmtList>().nodes.push_back($1); }
	|	stmt_list stmt 		{ 
			$$ = $1;
			$1->As<StmtList>().nodes.push_back( {$2} );
		}
	;
	
	//-------------------------------------------------
	// Expressions (like +-*/ function calls, literals ect.).
	//-------------------------------------------------

expr : expr_base { $$ = $1; ast->addDeduct($1); }
expr_base :
		'(' expr_base ')'			    	{ $2->inParens = true; $$ = $2; }
	|	expr_base '[' expr_base ']'			{ $$ = ast->push<ExprIndexing>(toLocation(@1), $1, $3); } // shift-reduce don't know why...
	|	expr_base '.' IDENT					{ $$ = ast->push<ExprMemberAccess>(toLocation(@1), $1, $3); }
	|	IDENT					        	{ $$ = ast->push<Ident>(toLocation(@1), $1); }
	|	expr_base OR expr_base			    { $$ = ast->push<ExprBin>(toLocation(@1), EBT_Or, $1, $3); }
	|	expr_base AND expr_base			    { $$ = ast->push<ExprBin>(toLocation(@1), EBT_And, $1, $3); }
	|	expr_base NOTEQUALS expr_base		{ $$ = ast->push<ExprBin>(toLocation(@1), EBT_NEquals, $1, $3); }
	|	expr_base EQUALS expr_base			{ $$ = ast->push<ExprBin>(toLocation(@1), EBT_Equals, $1, $3); }
	|	expr_base LE expr_base				{ $$ = ast->push<ExprBin>(toLocation(@1), EBT_LEquals, $1, $3); }
	|	expr_base '<' expr_base				{ $$ = ast->push<ExprBin>(toLocation(@1), EBT_Less, $1, $3); }
	|	expr_base GE expr_base				{ $$ = ast->push<ExprBin>(toLocation(@1), EBT_GEquals, $1, $3); }
	|	expr_base '>' expr_base				{ $$ = ast->push<ExprBin>(toLocation(@1), EBT_Greater, $1, $3); }
	|	expr_base '+' expr_base				{ $$ = ast->push<ExprBin>(toLocation(@1), EBT_Add, $1, $3); } 
	|	expr_base '-' expr_base				{ $$ = ast->push<ExprBin>(toLocation(@1), EBT_Sub, $1, $3); } 	
	|	expr_base '*' expr_base				{ $$ = ast->push<ExprBin>(toLocation(@1), EBT_Mul, $1, $3); } 
	|	expr_base '/' expr_base				{ $$ = ast->push<ExprBin>(toLocation(@1), EBT_Div, $1, $3); }
	|	NUM_FLOAT					        { $$ = ast->push<ExprLiteral>(toLocation(@1), $1); }
	|	NUM_INT						        { $$ = ast->push<ExprLiteral>(toLocation(@1), $1); }
	|	expr_fncall					        { $$ = $1; }
	|	expr_block							{ $$ = $1; }
	|	'-' expr_base %prec NONASSOC_UNARY	{ $2->exprSign *= -1; $$ = $2; }
	|	'+' expr_base %prec NONASSOC_UNARY	{ $$ = $2; }
	;

	// Expression block. Something like "{expr, expr ...}" example array initialization.
expr_block_expressions : 
		expr_base				{ $$ = ast->push<ExprBlock>(toLocation(@1)); $$->As<ExprBlock>().exprs.push_back($1); }
	|	expr_block_expressions ',' expr_base	{ $1->As<ExprBlock>().exprs.push_back($3); $$ = $1; } 
	;
	
expr_block :  
			'{' expr_block_expressions '}'	{ ast->addDeduct($2); $$ = $2; } 
	;

	// Function arguments as a list.
fncall_args :
			{ $$ = ast->push<FuncCall>(Location()); }
	| 	expr_base { 
					Node* fnCall = ast->push<FuncCall>(toLocation(@1));
					fnCall->As<FuncCall>().args.push_back($1); 
					$$ = fnCall;
				  }
		
	|	fncall_args ',' expr_base 	{ $1->As<FuncCall>().args.push_back($3); $$ = $1; }
	
	// The function call expression itself.
expr_fncall :
		IDENT '(' fncall_args ')'	{ 
			$3->As<FuncCall>().fnName = $1;
			$$ = $3; 
		}
	;
	//--------------------------------------------
	//
	//--------------------------------------------

%%

void yyerror(struct YYLTYPE* yyErrorLoc ,void* s,struct Ast* ast,char const* msg){
	ast->bisonParseError = msg;
	ast->bisonParseErrorLocation = toLocation(*yyErrorLoc);
}
