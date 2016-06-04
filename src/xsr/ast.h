#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <exception>
#include <cassert>

#include "xsr.h"
using namespace XSR;

struct Ast;

struct Location
{
	Location(const int line = -1, const int column = -1) :
		line(line),
		column(column)
	{}

	bool isValid() const {
		return line != -1 && column != -1;
	}

	int line;
	int column;
};

struct ParseExcept : public std::exception {
	ParseExcept(const Location& errorLoc, const char* msg) :
		errorLoc(errorLoc),
		msg(msg)
	{}

	ParseExcept(const Location& errorLoc, const std::string& msg) :
		errorLoc(errorLoc),
		msg(msg)
	{}

	const char* what() const override {
		return msg.c_str();
	}

	Location errorLoc;
	std::string msg;
};

enum Type
{
	Type_Undeduced,

	Type_BuiltInTypeBegin, // Just a marker, pointing right before 1st built in type.

	Type_void,
	Type_bool,

	Type_int,
	Type_vec2i,
	Type_vec3i,
	Type_vec4i,

	Type_float,
	Type_vec2f,
	Type_vec3f,
	Type_vec4f,

	Type_mat4f,

	Type_Texture2D,
	Type_TextureCube,

	Type_BuiltInTypeEnd, // Just a marker, pointing right after the last built in type.

	Type_UserDefined, // A user defined class.
};

// A so called trait attached to the variable.
enum VarTrait
{
	VarTrait_Regular, // Just a regual variable.
	VarTrait_VertexAttribute, // A vertex attribute.
	VarTrait_StageInVarying, // A varying variable.
	VarTrait_StageOutVarying, // A varying variable.

	// Stage specific input/output variables.
	// There may not be needed as they are similar to VarTrait_Stage*Varying
	VarTrait_StageSpecificInput,
	VarTrait_StageSpecificOutput,
};

struct TypeDesc
{
public :

	static std::string GetXShaderTypeName(const Type type);
	
public :

	TypeDesc() :
		TypeDesc(false, Type_Undeduced, 0)
	{}

	TypeDesc(const bool isConst, Type type, int arraySize = 0) : 
		m_isConst(isConst),
		m_type(type), 
		m_arraySize(arraySize)
	{}
	
	explicit TypeDesc(const bool isConst, std::string strType, int arraySize = 0);

	bool IsArray() const { return m_arraySize.size() != 0; }
	
	int GetArrayLevelsCount() const {
		return m_arraySize.size();
	}

	int GetArraySize(const int level) const {
		if(level >= m_arraySize.size()) return 0;
		return m_arraySize.at(level);
	
	}

	void SetArraySize(const int level, const int arraySize) {
		
		// In order to simplify code generation ignore calls with level < 0.
		if(level < 0){
			return;
		}

		// Modifying exiting array size or adding a new one are the only valid operations.
		// making float[4] to float[4][0][1] does not make any sense...
		if(level > m_arraySize.size()) {
			assert(false);
		}

		// Allocate enough space for the new level.
		if(m_arraySize.size() <= level) {
			m_arraySize.resize(level+1);
		}

		// If the array size is 0, that means that we should cut off that array size (all behind it).
		// If does not make sense to have  float[0][2] does it.
		// Addionally assert is if we are cutting something different form the last level.
		// [TODO] a bit more error checking ???
		if(arraySize == 0)
		{
			assert(m_arraySize.size() - 1 == level);
			m_arraySize.erase(m_arraySize.begin()+level, m_arraySize.end());
		}
		else
		{
			m_arraySize[level] = arraySize;
		}
	}

	void AddArrayLevel(const int arraySize)	{
		SetArraySize(GetArrayLevelsCount(), arraySize);
	}

	bool IsUndeduced() const {
		return m_type == Type_Undeduced;
	}

	bool IsSame(const TypeDesc& ref, const bool doConstwiseComparison) const {
		if(doConstwiseComparison)
		{
			// check if both are const.
			if(IsConst() != ref.IsConst())
			{
				return false;
			}
		}

		// Check if both types are arrays or not.
		if(GetArrayLevelsCount() != ref.GetArrayLevelsCount()){
			return false;
		}

		for(int iLevel = 0; iLevel < GetArrayLevelsCount(); ++iLevel){
			if(GetArraySize(iLevel) != ref.GetArraySize(iLevel)){
				return false;
			}
		}
		
		// Check if the data type is the same.
		if(m_type != Type_UserDefined) return m_type == ref.m_type;
		return m_strType == ref.m_strType;
	}

	bool IsSame(const Type type, const bool doConstwiseComparison) const {
		XSR_ASSERT(type != Type_UserDefined); // This check does not make any sense!

		if(doConstwiseComparison)
		{
			// Assumes that the input type is const by default.
			if(IsConst() == false) return false;
		}

		return type == m_type && (IsArray() == false);
	}

	// Returns the type of amember variable.
	static TypeDesc GetMemberType(const TypeDesc& parent, const std::string& member);
	
	// Returns typename as a string in the given langage.
	std::string GetTypeAsString(const LangSettings& lang, const bool omitArraySize) const;
	
	// Returns the string that adds the array component of the type
	std::string GetArraySuffixString() const;
	
	std::string ComposeVarDecl(const LangSettings& lang, const std::string& varName) const ;
	
	Type GetBuiltInType() const { return m_type; }

	bool IsConst() const { return m_isConst; }
	void SetConst(const bool v) { m_isConst = v; }

private :

	bool m_isConst;
	Type m_type = Type_Undeduced;
	std::string m_strType;
	std::vector<int> m_arraySize;
};

// A so called line marker, that holds the data specified by "#line" directive.
// Examples:
// #line 5
// #line "my_source_file.xsr"
//
// Basically this should work just like the C++ preprocessor.
struct LineMarker
{
	LineMarker(const int sourceLine = -1, const int targetLine = -1, const char* filename = "") :
		sourceLine(sourceLine),
		targetLine(targetLine),
		filename(filename)
	{}

	// The input is the matched string directly taken from flex.
	// The string is decomposed by this function.
	LineMarker(const int sourceLine, const char* const matchedString);

	int sourceLine; // The line number where "#line" was found in the code being compiled
	int targetLine; // The line number specified in the "#line" (aka. the line number).
	std::string filename; // Optional, The filename specified by the "#line". 
};


enum ExprBinType
{ 
	EBT_Add, 
	EBT_Sub,
	EBT_Mul, 
	EBT_Div, 
	EBT_Greater, 
	EBT_GEquals, 
	EBT_Less, 
	EBT_LEquals, 
	EBT_Equals,
	EBT_NEquals,
	EBT_Or, 
	EBT_And,
};

enum FnCallArgType
{
	FNAT_In,
	FNAT_Out,
	FNAT_InOut,
};

struct VertexAttribs
{
	TypeDesc type;
	std::string varName;
	std::string semantic;
};

struct Varyings
{
	TypeDesc type;
	std::string varName;
};

struct Uniforms
{
	TypeDesc type;
	std::string varName;
};

struct Node
{
public : 

	Node() {}
	virtual ~Node() = default;

	template<typename T> T& As() { return *(T*)this; }

	std::string GenerateCode(Ast* ast) {
		
		std::string retval = Internal_GenerateCode(ast);

		if(inParens) retval = '(' + retval +')';
		if(exprSign < 0) retval = '-' + retval;
		if(hasSemicolon) retval += ";";
		if(inBlock) retval = "{" + retval + "}";

		return retval;
	}
	
	void Declare(Ast* ast);

	TypeDesc DeduceType(Ast* ast) { return Internal_DeduceType(ast); }

private :

	virtual std::string Internal_GenerateCode(Ast* ast) { XSR_ASSERT(false); return std::string(); }
	virtual void Internal_Declare(Ast* ast) { }
	virtual TypeDesc Internal_DeduceType(Ast* ast) { XSR_ASSERT(false) ;return TypeDesc(); }

public :

	int exprSign = 1; // The sign of the expression. Used for -expr for example.
	bool inParens = false; // True if the expression is surrounded with parens.
	bool inBlock = false; // True if the statement is surrounded by { }
	bool hasSemicolon = false; // True if the statement is of kind <--->; 
	Location location;
};

struct Ast
{	
	Ast() = default;

	~Ast() {
		for(auto node : nodes) delete node;
		nodes.clear();
	}

	template<typename T, typename... Args>
	T* push(const Location location, Args... args) {
		T* node = new T(args...);
		node->location = location;
		nodes.push_back(node);
		return node;
	}

	// Add a line marker used to resolve where an eventual comiling error actually is.
	// A an implementation detail, this function does a sorted insert.
	void addLineMarker(const LineMarker& marker);

	// Find the LineMaker for the given line in the source being compiled.
	const LineMarker* findLineMarker(const int sourceLine);

	// During declaration pass, these are used in order to 
	// set change the current scope for defining and searching for variables.
	void declPushScope() {
		static int scopeIndex;
		char srtScope[32];
		sprintf(srtScope, "@scp_%d", scopeIndex);
		scopeIndex++;

		declPushScope(srtScope);
	}

	void declPushScope(const std::string& scopeName) {
		scope.push_back(scopeName);
	}

	void declPopScope() {
		scope.pop_back();
	}

	// Adds a node. to the deduction queue.
	// This is in order to traverse only the nodes that need type deduction.
	void addDeduct(Node* expr) {
		deductionQueue.push_back(expr);
	}

	// A fully defined variable description.
	struct FullVariableDesc {

		FullVariableDesc() = default;
		FullVariableDesc(
			std::string fullName,
			TypeDesc type,
			VarTrait trait,
			const char* hlslSemantic = nullptr,
			const char* glslVarName = nullptr)
		:
			fullName(fullName), type(type), trait(trait), hlslSemantic(hlslSemantic), glslVarName(glslVarName)
		{}

		std::string fullName;
		TypeDesc type;
		VarTrait trait;

		// Used for stage specific variables.
		const char* hlslSemantic = nullptr;
		const char* glslVarName = nullptr;
	};

	struct FullFuncionDesc {
		std::string fullName;
		TypeDesc retType;
	};

	std::string bisonParseError;
	Location bisonParseErrorLocation;

	// Declares a variable at the current scope
	const FullVariableDesc* declareVariable(const TypeDesc& td, const std::string& name,  VarTrait trait = VarTrait_Regular);
	void declareFunction(const TypeDesc& returnType, const std::string& name);
	
	// Thorws ParseExcept if missing. 
	const FullVariableDesc* findVarInCurrentScope(const std::string& name, const Location& location);
	const FullFuncionDesc& findFuncDecl(const std::string& name);

	// A list of line markers, marking where the code below it was originally.
	// [CAUTION] This structure must be sorted by sourceLine!!!
	std::vector<LineMarker> lineMarkers;

	Node* program = nullptr; // The root node.
	std::vector<Node*> nodes;

	std::vector<VertexAttribs> vertexAttribs; // Vertex shader vertex attributes.
	std::vector<Varyings> stageInputVaryings; // aka. input varyings
	std::vector<Varyings> stageOutputVaryings; // aka. output varyings
	std::vector<Uniforms> uniforms;

	std::vector<std::string> scope; // A elper stack variables used to stack the scope ducing declaration pass.
	std::list<FullVariableDesc> declaredVariables; // yep a list, becase we need the pointers to be solid.
	std::vector<FullFuncionDesc> declaredFunctions;

	std::vector<Node*> deductionQueue;

	// A list of reserved variable that where mentioned in the program.
	// These vaules are basically replicas to gl_*(gl_Position for instance)
	// or something with SV_* semantic.
	std::vector<const Ast::FullVariableDesc*> keywordVariablesMentioned;

	// Cached output language settings.
	LangSettings lang;
	bool OutLangIs(OutputLanguage ol) const { return lang.outputLanguage == ol; }
};

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
struct TypeDeclNode : public Node
{
	TypeDeclNode() = default;
	TypeDesc Internal_DeduceType(Ast* ast) override {
		XSR_ASSERT(resolvedType.IsUndeduced()==false);
		return resolvedType;
	}

	TypeDesc resolvedType;
};

//-------------------------------------------------------------------------
// Expressions.
//-------------------------------------------------------------------------
struct Ident : public Node
{
	Ident() = default;
	Ident(const std::string& identifier) :
		identifier(identifier)
	{}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;
	TypeDesc Internal_DeduceType(Ast* ast) override;

	std::string identifier;
	const Ast::FullVariableDesc* resolvedFvd = nullptr;
};

struct ExprMemberAccess : public Node
{
	ExprMemberAccess() = default;
	ExprMemberAccess(Node* expr, const std::string& member) :
		expr(expr), member(member)
	{}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;
	TypeDesc Internal_DeduceType(Ast* ast) override;

	Node* expr;
	std::string member;

	TypeDesc resolvedType; 
};

// Binary expression of kind: a ? b
struct ExprBin : public Node
{
	ExprBin() = default;
	ExprBin(ExprBinType type, Node* left, Node* right) :
		type(type), left(left), right(right)
	{}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;
	TypeDesc Internal_DeduceType(Ast* ast) override;

	ExprBinType type;
	Node* left;
	Node* right;

	TypeDesc resolvedType;
};

struct ExprIndexing : public Node
{
	ExprIndexing() = default;
	ExprIndexing(Node* expr, Node* idxExpr) : 
		expr(expr), idxExpr(idxExpr)
	{}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;
	TypeDesc Internal_DeduceType(Ast* ast) override;

	Node* expr; // what we are indexing
	Node* idxExpr; // the index itself

	TypeDesc resolvedType;
};

struct FuncCall : public Node
{
	std::string fnName;
	std::vector<Node*> args;

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;
	TypeDesc Internal_DeduceType(Ast* ast) override;

	TypeDesc resolvedType;
};

// Literal value
struct ExprLiteral : public Node
{
	union
	{
		int int_val;
		float float_val;
	};

	ExprLiteral() : type() {}
	ExprLiteral(float f) : type(true, Type_float), float_val(f) {}
	ExprLiteral(int i) : type(true, Type_int), int_val(i) {}

	std::string Internal_GenerateCode(Ast* ast) override;
	TypeDesc Internal_DeduceType(Ast* ast) override;

	TypeDesc type;
};

// Expression block. Example { expr, expr ... }
struct ExprBlock : public Node
{
	std::vector<Node*> exprs; // the list of expression.

	TypeDesc Internal_DeduceType(Ast* ast) override;
	std::string Internal_GenerateCode(Ast* ast) override;

	TypeDesc resolvedType;
};


//---------------------------------------------------------------------------------
// Statements
//---------------------------------------------------------------------------------
struct Assign : public Node
{
	Assign(Node* lval, Node* expr) :
		lval(lval), expr(expr)
	{}

	Node* lval;
	Node* expr;

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;
};

struct StmtNativeCode : public Node
{
	StmtNativeCode() = default;
	StmtNativeCode(const std::string& code) : code(code) {}

	std::string Internal_GenerateCode(Ast* ast) override;

	std::string code;
};

struct StmtIf : public Node
{
	StmtIf() = default;
	StmtIf(Node* expr, Node* trueStmt, Node* falseStmt) : expr(expr), trueStmt(trueStmt), falseStmt(falseStmt) {}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	Node* expr = nullptr;
	Node* trueStmt = nullptr;
	Node* falseStmt = nullptr; // optional
};

struct StmtWhile : public Node
{
	StmtWhile() = default;
	StmtWhile(Node* expr, Node* bodyStmt) : expr(expr), bodyStmt(bodyStmt) {}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	Node* expr = nullptr;
	Node* bodyStmt = nullptr;
};

struct StmtFor : public Node
{
	StmtFor(Node* vardecl, Node* boolExpr, Node* postExpr, Node* stmt) :
		vardecl(vardecl), boolExpr(boolExpr), postExpr(postExpr), stmt(stmt)
	{}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	Node* vardecl = nullptr;
	Node* boolExpr = nullptr;
	Node* postExpr = nullptr;
	Node* stmt = nullptr;
};

struct StmtReturn : public Node
{
	StmtReturn() = default;
	StmtReturn(Node* expr) : expr(expr) {}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	Node* expr = nullptr;
};

struct StmtList : public Node
{
	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	std::vector<Node*> nodes;
};

struct VarDecl : public Node
{
	VarDecl() = default;

	VarDecl(std::string firstIdent, Node* firstExpr) : 
		typeNode(nullptr)
	{
		ident.push_back(firstIdent);
		expr.push_back(firstExpr);
	}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	TypeDeclNode* typeNode;
	std::vector<std::string> ident;
	std::vector<Node*> expr;
};

//---------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------

struct FnDeclArgVarDecl : public Node
{
	FnDeclArgVarDecl() = default;

	FnDeclArgVarDecl(TypeDesc type, const std::string& ident, Node* const expr, FnCallArgType argType) :
		type(type), ident(ident), expr(expr), argType(argType)
	{}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	TypeDesc type;//std::string type;
	std::string ident; // The name of the variable.
	Node* expr;
	FnCallArgType argType; //in/out/inout.

};

struct FuncDecl : public Node
{
	std::vector<Node*> args;
	TypeDesc retType;//std::string retType;
	std::string name;

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	Node* stmt; // the body of the function.

private :

	std::string GenerateMainFuncHLSL(Ast* ast);
};

struct ProgramElem : public Node
{
	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	std::vector<Node*> nodes;
};