#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <exception>

#include "xsr.h"
using namespace XSR;

struct Ast;
struct Node;
struct TypeNode;

struct ParseExcept : public std::exception {
	ParseExcept(const char* msg) :
		std::exception(msg)
	{}

	ParseExcept(const std::string& msg) :
		std::exception(msg.c_str())
	{}
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

	static std::string GetLangTypeName(const Type type);
	
public :

	TypeDesc(Type type = Type_Undeduced, int arraySize = 0) : m_type(type), m_arraySize(arraySize) {}
	explicit TypeDesc(std::string strType, int arraySize = 0);

	bool IsArray() const { return m_arraySize > 0; }
	int GetArraySize() const { return m_arraySize; }
	void SetArraySize(int arraySize) { m_arraySize = arraySize; }

	bool operator==(const Type type) const { return type == m_type && (m_arraySize == 0); }
	bool operator!=(const Type type) const { return type != m_type && (m_arraySize == 0); }

	bool operator==(const TypeDesc& other) const {

		// Check if both types are arrays or not.
		const bool areSameArraywise = !!(GetArraySize()) ^ !!(other.GetArraySize());
		if(areSameArraywise) return false;

		// Check if the data type is the same.
		if(m_type != Type_UserDefined) return m_type == other.m_type;
		return m_strType == other.m_strType;
	}
	bool operator!=(const TypeDesc& other) const { return !(*this == other); }
	static TypeDesc GetMemberType(const TypeDesc& parent, const std::string& member);
	std::string GetTypeAsString(const LangSettings& lang,  bool omitArraySize) const;
	std::string ComposeVarDecl(const LangSettings& lang, const std::string& varName) const ;
	
	Type GetBuiltInType() const { return m_type; }
private : 

	Type m_type = Type_Undeduced;
	std::string m_strType;
	int m_arraySize = 0; // 0 means that this is not an array.
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
	VertexAttribs(TypeNode* const typeNode = nullptr, const std::string& varName = std::string(), const std::string& semantic = std::string()) :
		typeNode(typeNode),
		varName(varName),
		semantic(semantic)
	{}

	TypeNode* typeNode = nullptr;
	std::string varName;
	std::string semantic;
};

struct Varyings
{
	Varyings(TypeNode* const typeNode = nullptr, const std::string& varName = std::string()) : 
		typeNode(typeNode),
		varName(varName)
	{}

	TypeNode* typeNode = nullptr;
	std::string varName;
};

struct Uniforms
{
	Uniforms(TypeNode* const typeNode = nullptr, const std::string& varName = std::string()) :
		typeNode(typeNode),
		varName(varName)
	{}

	TypeNode* typeNode = nullptr;
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

	virtual std::string Internal_GenerateCode(Ast* ast) { return std::string(); }
	virtual void Internal_Declare(Ast* ast) { }
	virtual TypeDesc Internal_DeduceType(Ast* ast) { return TypeDesc(); }

public :

	int exprSign = 1; // The sign of the expression. Used for -expr for example.
	bool inParens = false; // True if the expression is surrounded with parens.
	bool inBlock = false; // True if the statement is surrounded by { }
	bool hasSemicolon = false; // True if the statement is of kind <--->; 
};

struct Ast
{	
	Ast() = default;

	~Ast() {
		for(auto node : nodes) delete node;
		nodes.clear();
	}

	template<typename T, typename... Args>
	T* push(Args... args) {
		T* node = new T(args...);
		nodes.push_back(node);
		return node;
	}

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

	// Declares a variable at the current scope
	const FullVariableDesc* declareVariable(const TypeDesc& td, const std::string& name,  VarTrait trait = VarTrait_Regular);
	void declareFunction(const TypeDesc& returnType, const std::string& name);
	
	// Thorws ParseExcept if missing. 
	const FullVariableDesc* findVarInCurrentScope(const std::string& name);
	const FullFuncionDesc& findFuncDecl(const std::string& name);

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

struct TypeNode : public Node
{
	TypeDesc GenerateTypeDesc() const;

	std::vector<int> arraySizes; // The array sizes. If none, the variable is not an array.
	std::vector<std::string> identifiers; // A list of all identifiers that participate in the type decl example is: "in const int"
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
	ExprLiteral(float f) : type("float"), float_val(f) {}
	ExprLiteral(int i) : type("int"), int_val(i) {}

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

	VarDecl(TypeNode* typeNode, std::string firstIdent, Node* firstExpr) :
		typeNode(typeNode)
	{
		ident.push_back(firstIdent);
		expr.push_back(firstExpr);
	}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	TypeNode* typeNode;
	std::vector<std::string> ident;
	std::vector<Node*> expr;
};

//---------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------

struct FnDeclArgVarDecl : public Node
{
	FnDeclArgVarDecl() = default;

	FnDeclArgVarDecl(TypeNode* typeNode, const std::string& ident, Node* const expr, FnCallArgType argType) :
		typeNode(typeNode), ident(ident), expr(expr), argType(argType)
	{}

	std::string Internal_GenerateCode(Ast* ast) override;
	void Internal_Declare(Ast* ast) override;

	TypeNode* typeNode;
	std::string ident; // The name of the variable.
	Node* expr;
	FnCallArgType argType; //in/out/inout.

};

struct FuncDecl : public Node
{
	std::vector<Node*> args;
	TypeNode* retType;
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