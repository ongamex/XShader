#pragma once

#include <algorithm>
#include <stdarg.h>  // For va_start, etc.
#include <memory>    // For std::unique_ptr
#include <cstring>

#include "ast.h"

namespace
{
	// HLSL shader result is returned as a structure from the main function.
	// These are the names of the strctures and variables that WILL
	// be declared in the main function.
	const std::string HLSL_ShaderResultStruct = "XSR_SHADER_RESULT";
	const std::string HLSL_ShaderResultVar = "XSR_shader_result";
}

//-----------------------------------------------------------------------
//TypeDesc
//-----------------------------------------------------------------------
TypeDesc::TypeDesc(const bool isConst, std::string strType, int arraySize) :
	TypeDesc()
{
	m_isConst = isConst;
	m_strType = strType;
	SetArraySize(0, arraySize);

	if(strType == "void") m_type = Type_void;
	else if(strType == "bool") m_type = Type_bool;
	else if(strType == "int") m_type = Type_int;
	else if(strType == "float") m_type = Type_float;
	else if(strType == "vec2f") m_type = Type_vec2f;
	else if(strType == "vec3f") m_type = Type_vec3f;
	else if(strType == "vec4f") m_type = Type_vec4f;
	else if(strType == "mat4f") m_type = Type_mat4f;
	else if(strType == "Texture2D") m_type = Type_Texture2D;
	else if(strType == "TextureCube") m_type = Type_TextureCube;
	else { m_type = Type_UserDefined; }
}

std::string TypeDesc::GetXShaderTypeName(const Type type)
{
	if(type == Type_void)        return "void";
	if(type == Type_bool)        return "bool";
	if(type == Type_int)         return "int";
	if(type == Type_vec2i)       return "vec2i";
	if(type == Type_vec3i)       return "vec3i";
	if(type == Type_vec4i)       return "vec4i";
	if(type == Type_mat4f)       return "mat4f";
	if(type == Type_float)       return "float";
	if(type == Type_vec2f)       return "vec2f";
	if(type == Type_vec3f)       return "vec3f";
	if(type == Type_vec4f)       return "vec4f";
	if(type == Type_mat4f)       return "mat4f";
	if(type == Type_Texture2D)   return "Texture2D";
	if(type == Type_TextureCube) return "TextureCube";

	XSR_ASSERT(false);
	return std::string();
}

TypeDesc TypeDesc::GetMemberType(const TypeDesc& parent, const std::string& member)
{
	//[TODO] This is sooo broken....
	const bool isFloatVectorType = 
			(parent.GetBuiltInType() == Type_vec2f) 
		|| (parent.GetBuiltInType() == Type_vec3f) 
		|| (parent.GetBuiltInType() == Type_vec4f);

	const bool isIntVectorType = 
			(parent.GetBuiltInType() == Type_vec2i) 
		|| (parent.GetBuiltInType() == Type_vec3i) 
		|| (parent.GetBuiltInType() == Type_vec4i);

	if(isFloatVectorType || isIntVectorType)
	{
		// Check if this is a vector type swizzle.
		if(member.size() <= 4)
		{
			for(auto ch : member) {
				if(ch != 'x' && ch != 'y' && ch != 'z' && ch != 'w') {
					return TypeDesc(); // Unexisting member.
				}
			}

			if(isFloatVectorType)
			{
				if(member.size() == 1) return TypeDesc(parent.IsConst(), Type_float);
				if(member.size() == 2) return TypeDesc(parent.IsConst(), Type_vec2f);
				if(member.size() == 3) return TypeDesc(parent.IsConst(), Type_vec3f);
				if(member.size() == 4) return TypeDesc(parent.IsConst(), Type_vec4f);
			}
			else
			{
				if(member.size() == 1) return TypeDesc(parent.IsConst(), Type_int);
				if(member.size() == 2) return TypeDesc(parent.IsConst(), Type_vec2i);
				if(member.size() == 3) return TypeDesc(parent.IsConst(), Type_vec3i);
				if(member.size() == 4) return TypeDesc(parent.IsConst(), Type_vec4i);
			}
		}
	}

	// Unexisting member.
	return TypeDesc();
}

std::string TypeDesc::GetTypeAsString(const LangSettings& lang, const bool omitArraySize) const 
{
	XSR_ASSERT(IsUndeduced() == false);
	
	std::string retval;

	if(IsConst()) retval += "const ";

	if(GetBuiltInType() == Type_void) retval = "void";
	else if(GetBuiltInType() == Type_int) retval = "int";
	else if(GetBuiltInType() == Type_float) retval = "float";
	else if(GetBuiltInType() == Type_bool) retval = "bool";
	else if(GetBuiltInType() == Type_vec2f) { if(lang.outputLanguage == OL_HLSL) retval = "float2"; else retval = "vec2"; }
	else if(GetBuiltInType() == Type_vec3f) { if(lang.outputLanguage == OL_HLSL) retval = "float3"; else retval = "vec3"; }
	else if(GetBuiltInType() == Type_vec4f) { if(lang.outputLanguage == OL_HLSL) retval = "float4"; else retval = "vec4"; }
	else if(GetBuiltInType() == Type_mat4f) { if(lang.outputLanguage == OL_HLSL) retval = "float4x4"; else retval = "mat4"; }
	else if(GetBuiltInType() == Type_Texture2D) { if(lang.outputLanguage == OL_HLSL) retval = "Texture2D"; else retval = "sampler2D"; }
	else if(GetBuiltInType() == Type_TextureCube) { if(lang.outputLanguage == OL_HLSL) retval = "TextureCube"; else retval = "samplerCube"; } 
	else if(GetBuiltInType() == Type_UserDefined)
	{
		if(m_strType.empty()) retval = "<empty-str-type>";
		retval = m_strType;
	}

	if(omitArraySize == false) retval += GetArraySuffixString();

	return retval;
}

std::string TypeDesc::GetArraySuffixString() const
{
	std::string retval;

	for(int iLevel = 0; iLevel < GetArrayLevelsCount(); ++iLevel)
	{
		char temp[32] = {0};
		sprintf(temp, "[%d]", GetArraySize(iLevel));
		retval += temp;
	}

	return retval;
}

std::string TypeDesc::ComposeVarDecl(const LangSettings& lang, const std::string& varName) const
{
	if(IsArray())
	{
		// In both HLSL and GLSL array are defined like this:
		// type varname[sz0][sz1]..;
		const std::string arraySuffix = GetArraySuffixString();
		return GetTypeAsString(lang, true) + " " + varName + arraySuffix;
	}

	return GetTypeAsString(lang, true) + " " + varName;
}

//-----------------------------------------------------------------------
// LineMarker
//-----------------------------------------------------------------------
LineMarker::LineMarker(const int sourceLine, const char* const matchedString) :
	sourceLine(sourceLine)
{
	const size_t ln = strlen(matchedString);

	if(ln < 5)
	{
		throw ParseExcept(Location(), "Invalid #line command.");
	}

	if(memcmp("#line", matchedString, 5)!=0)
	{
		ParseExcept(Location(), "Unknown preprocessor directive!");
	}

	size_t idx = 5;
	targetLine = 0;

	bool lineRead = false;
	bool openQuoteFound = false;
	bool closeQuoteFound = false;

	for(;idx<=ln; idx++)
	{
		const char ch = matchedString[idx];

		if(isspace(ch) || ch == '\0')
		{
			if(targetLine!=0) lineRead = true;
			continue;
		}

		if(lineRead==false) {
			if(isdigit(ch)) targetLine = targetLine * 10 + (ch - '0');
			else throw ParseExcept(Location(), "Invalid #line macro, invalid line number.");
		}

		// The line has been read, this must be the filename.
		if(lineRead==true)
		{
			if(ch == '\"')
			{
				if(openQuoteFound==false)
				{
					openQuoteFound = true;
				}
				else
				{
					closeQuoteFound = true;
					break;
				}
			}
			else if(openQuoteFound)
			{
				filename.push_back(ch);
			}
		}
	}

	if(!lineRead || (openQuoteFound && !openQuoteFound))
	{
		throw ParseExcept(Location(), "Invalid #line command.");
	}
}


//-----------------------------------------------------------------------
// Ast
//-----------------------------------------------------------------------
void Ast::addLineMarker(const LineMarker& marker)
{
	std::vector<LineMarker>::iterator itr = lineMarkers.begin();

	// Find the 1st element with bigger sourceLine, 
	// so all line markers are kept in order.
	for(size_t t = 0; t < lineMarkers.size(); ++t)
	{
		if(lineMarkers[t].sourceLine > itr->sourceLine)
		{
			itr = lineMarkers.begin() + t;
		}
	}

	lineMarkers.insert(itr, marker);
}

const LineMarker* Ast::findLineMarker(const int sourceLine)
{
	for(const LineMarker& lineMarker : lineMarkers)
	{
		if(sourceLine > lineMarker.sourceLine) return &lineMarker;
	}

	return nullptr;
}

const Ast::FullVariableDesc* Ast::declareVariable(const TypeDesc& td, const std::string& name, VarTrait trait)
{
	XSR_ASSERT(td.IsUndeduced() == false);

	FullVariableDesc fvd;

	for(auto s : scope) fvd.fullName += s + "::";

	fvd.fullName += name;
	fvd.type = td;
	fvd.trait = trait;

	// Proove that there isn't a variable with the same name already defined.
	std::find_if(begin(declaredVariables), end(declaredVariables), [&fvd, &name](FullVariableDesc v)
	{
		const bool equal = fvd.fullName == v.fullName;
		if(equal) throw ParseExcept(Location(), "Variable with name '" + name + "' is already defined!");
		return equal;
	});

	declaredVariables.push_back(fvd);

	return &declaredVariables.back();
}

const Ast::FullVariableDesc* Ast::findVarInCurrentScope(const std::string& name, const Location& location)
{
	// Search through all declared variables.
	int depth = scope.size();
	std::string fullName;

	while(depth >= 0)
	{
		fullName.clear();
		for(int t = 0; t < depth; ++t) fullName+= scope[t] + "::";
		fullName += name;

		for(Ast::FullVariableDesc& fvd : declaredVariables)
		{
			if(fvd.fullName == fullName) {

				// Check if this is a "keyword variable".
				// Mark the variable as "mentioned", meaning that this variable needs a special declaration in the output code(usually(maybe only) stage specific variables).
				const bool isKeywordVar = fvd.trait == VarTrait_StageSpecificInput || fvd.trait == VarTrait_StageSpecificOutput;
			
				if(isKeywordVar) {
					const bool varFound = 
						end(keywordVariablesMentioned) == std::find(begin(keywordVariablesMentioned), end(keywordVariablesMentioned), &fvd);
					
					if(varFound)
					{
						keywordVariablesMentioned.push_back(&fvd);
					}
				}

				return &fvd;
			}
		}

		depth--;
	}

	throw ParseExcept(location, "Referenced an undefined variable: " + name);
}

const Ast::FullFuncionDesc& Ast::findFuncDecl(const std::string& name)
{
	for(auto& f : declaredFunctions)
	{
		if(f.fullName == name) return f;
	}

	throw ParseExcept(Location(), "Referenced an undefined funcion: " + name);
}

void Ast::declareFunction(const TypeDesc& returnType, const std::string& name)
{
	declaredFunctions.push_back({name, returnType});
}

//-----------------------------------------------------------------------
// Node
//-----------------------------------------------------------------------
void Node::Declare(Ast* ast)
{
	if(inBlock) ast->declPushScope();
	Internal_Declare(ast);
	if(inBlock) ast->declPopScope();
}

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
std::string Ident::Internal_GenerateCode(Ast* ast)
{
	// Check if this is a keyword variable.
	if(ast->OutLangIs(OL_HLSL))
	{
		// Stage specifics outputs and varyings
		if(resolvedFvd->trait == VarTrait_StageOutVarying || resolvedFvd->trait == VarTrait_StageSpecificOutput)
		{
			return HLSL_ShaderResultVar + "." + identifier;
		}

		if(resolvedFvd->trait == VarTrait_StageSpecificInput)
		{
			return identifier;
		}
	}

	if(ast->OutLangIs(OL_GLSL))
	{
		//
		if(resolvedFvd->trait == VarTrait_StageSpecificOutput || resolvedFvd->trait == VarTrait_StageSpecificInput)
		{
			return resolvedFvd->glslVarName;
		}

		// Output varyings.
		if(resolvedFvd->trait == VarTrait_StageOutVarying)
		{
			return identifier;
		}

		// Vertex attributes.... For GLSL use the semantic name instead of the actual variable name.
		if(resolvedFvd->trait == VarTrait_VertexAttribute)
		{
			for(const auto& attr : ast->vertexAttribs) {
				if(attr.varName == identifier) return attr.semantic;
			}

			throw ParseExcept(location, "Attribute '" + identifier + "\' not found!");
		}
	}

	// Just a regular variable or something that exactly matches the name of the identifier.
	return identifier;
	
}

void Ident::Internal_Declare(Ast* ast)
{
	// [TODO] This is just a mistake...
	// Deduce the type during the declaration. This is esier becase we already know the current scope.
	// The correct solution would be to cache the current scope and deduce the type into the "type deduction" pass.
	resolvedFvd = ast->findVarInCurrentScope(identifier, location);
}

TypeDesc Ident::Internal_DeduceType(Ast* ast)
{
	// [NOTE] Currently resolved in "Declaration" step, this is a mistake and must get fixed.
	return resolvedFvd->type;
}

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
std::string ExprMemberAccess::Internal_GenerateCode(Ast* ast)
{
	return expr->GenerateCode(ast) + "." + member;
}

void ExprMemberAccess::Internal_Declare(Ast* ast)
{
	expr->Declare(ast);
}

TypeDesc ExprMemberAccess::Internal_DeduceType(Ast* ast)
{
	if(resolvedType.IsUndeduced()){
		resolvedType = TypeDesc::GetMemberType(expr->DeduceType(ast), member);

		if(resolvedType.IsUndeduced()){
			throw ParseExcept(location, "Unknown member access: " + member);
		}
	}

	return resolvedType;
}

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
std::string ExprBin::Internal_GenerateCode(Ast* ast)
{
	switch(type) {
		case EBT_Add : return left->GenerateCode(ast) + (" + ") + right->GenerateCode(ast);
		case EBT_Sub : return left->GenerateCode(ast) + (" - ") + right->GenerateCode(ast);
		case EBT_Mul :
		{
			// In HLSL matrix multiplication is a bit odd. mathematical multiplication with matrices is
			// done with mul(m,?) while component-wise matrix multiplication is done with *.
			const Type lt = left->DeduceType(ast).GetBuiltInType();
			const Type rt = right->DeduceType(ast).GetBuiltInType();

			const bool hasMatrix = (lt == Type_mat4f  || rt == Type_mat4f);
			const bool hasScalar = (lt == Type_float  || rt == Type_float) || (lt == Type_int  || rt == Type_int);

			const bool isAtLeastOneAscalar = 
				left->DeduceType(ast).GetBuiltInType() == Type_float 
				|| right->DeduceType(ast).GetBuiltInType() == Type_float;

			if(ast->lang.outputLanguage == OL_HLSL && hasMatrix && !hasScalar)
			{
				return "mul(" + left->GenerateCode(ast) + "," + right->GenerateCode(ast) + ")";
			}
			else 
			{
				return left->GenerateCode(ast) + (" * ") + right->GenerateCode(ast);
			}
		}
		case EBT_Div :      return left->GenerateCode(ast) + (" / ") + right->GenerateCode(ast);
		case EBT_Greater :  return left->GenerateCode(ast) + (" > ") + right->GenerateCode(ast);
		case EBT_GEquals :  return left->GenerateCode(ast) + (" >= ") + right->GenerateCode(ast);
		case EBT_Less :     return left->GenerateCode(ast) + (" < ") + right->GenerateCode(ast);
		case EBT_LEquals :  return left->GenerateCode(ast) + (" <= ") + right->GenerateCode(ast);
		case EBT_Equals :   return left->GenerateCode(ast) + (" == ") + right->GenerateCode(ast);
		case EBT_NEquals :  return left->GenerateCode(ast) + (" != ") + right->GenerateCode(ast);
		case EBT_Or :       return left->GenerateCode(ast) + (" || ") + right->GenerateCode(ast);
		case EBT_And :      return left->GenerateCode(ast) + (" && ") + right->GenerateCode(ast);
	}

	throw ParseExcept(location, "Unknown bynary opt!");
}

void ExprBin::Internal_Declare(Ast* ast)
{
	left->Declare(ast);
	right->Declare(ast);
}

TypeDesc ExprBin::Internal_DeduceType(Ast* ast)
{
	// Check if the type has been already resolved
	if(resolvedType.IsUndeduced()==false) {
		return resolvedType;
	}

	// Resolve the arguments type.
	const auto lt = left->DeduceType(ast);
	const auto rt = right->DeduceType(ast);

	// [CAUTION]
	if(lt.IsArray() || rt.IsArray()){
		throw ParseExcept(location, "Binary operations between arrays do not exist.");
	}

	// Just a helper function...
	auto isPairOf = [lt, rt](Type a, Type b) {
	return (lt.GetBuiltInType() == a && rt.GetBuiltInType() == b) ||
			(lt.GetBuiltInType() == b && rt.GetBuiltInType() == a);
	};

	// Deduce the type.
	switch(type)
	{
		case EBT_Add : 
		case EBT_Sub :
		{
			if(lt.IsSame(rt, false) == false){
				const std::string leftType = TypeDesc::GetXShaderTypeName(lt.GetBuiltInType());
				const std::string rightType = TypeDesc::GetXShaderTypeName(rt.GetBuiltInType());
				throw ParseExcept(location,"operator+/- called with mixed types: "+leftType+" and "+rightType+".");
			}

			resolvedType = lt;
			break;
		}

		case EBT_Mul : 
		{
			if(lt.IsSame(rt, false))                  resolvedType = lt;
			else if(isPairOf(Type_int, Type_float))   resolvedType = TypeDesc(true, Type_float);
			else if(isPairOf(Type_float, Type_vec2f)) resolvedType = TypeDesc(true, Type_vec2f);
			else if(isPairOf(Type_float, Type_vec3f)) resolvedType = TypeDesc(true, Type_vec3f);
			else if(isPairOf(Type_float, Type_vec4f)) resolvedType = TypeDesc(true, Type_vec4f);
			else if(isPairOf(Type_mat4f, Type_vec4f)) resolvedType = TypeDesc(true, Type_vec4f);
			else if(isPairOf(Type_mat4f, Type_float)) resolvedType = TypeDesc(true, Type_mat4f);
			else if(isPairOf(Type_mat4f, Type_mat4f)) resolvedType = TypeDesc(true, Type_mat4f);
			else if(isPairOf(Type_mat4f, Type_int))   resolvedType = TypeDesc(true, Type_mat4f);
			
			// The type should be deduced by now, if not this is an error.
			if(resolvedType.IsUndeduced()){
				const std::string leftType = TypeDesc::GetXShaderTypeName(lt.GetBuiltInType());
				const std::string rightType = TypeDesc::GetXShaderTypeName(rt.GetBuiltInType());
				throw ParseExcept(location, "operator* called with incompatible types: "+leftType+" and "+rightType+".");
			}
			break;
		}
		
		case EBT_Div :
		{
			if(isPairOf(Type_float, Type_float)) resolvedType = TypeDesc(true, Type_float);
			else if(isPairOf(Type_int, Type_int)) resolvedType = TypeDesc(true, Type_int);

			// The type should be deduced by now, if not this is an error.
			if(resolvedType.IsUndeduced()){
				const std::string leftType = TypeDesc::GetXShaderTypeName(lt.GetBuiltInType());
				const std::string rightType = TypeDesc::GetXShaderTypeName(rt.GetBuiltInType());

				throw ParseExcept(location, "operator/ called with incompatible types: "+leftType+" and "+rightType+".");
			}
			break;
		}
		
		// Logical operators. Just ignore the arg types and return a boolean.
		case EBT_Greater :
		case EBT_GEquals : 
		case EBT_Less :
		case EBT_LEquals :
		case EBT_Equals :
		case EBT_NEquals :
		case EBT_Or :
		case EBT_And :
		{
			resolvedType = TypeDesc(true, Type_bool);
			break;
		}
		default :
			throw ParseExcept(location, "Unknown binary expression.");
	}

	if(resolvedType.IsUndeduced())
	{
		throw ParseExcept(location, "Failed to deduce the binary experssion type.");
	}

	return resolvedType;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string ExprIndexing::Internal_GenerateCode(Ast* ast)
{
	return expr->GenerateCode(ast) + '[' + idxExpr->GenerateCode(ast) + ']';
}
void ExprIndexing::Internal_Declare(Ast* ast)
{
	expr->Declare(ast);
	idxExpr->Declare(ast);
}

TypeDesc ExprIndexing::Internal_DeduceType(Ast* ast)
{
	if(resolvedType.IsUndeduced()==false) {
		return resolvedType;
	}

	TypeDesc exprType = expr->DeduceType(ast);
	if(exprType.IsArray() == false) {
		// [TODO] Write the actual type name.
		throw ParseExcept(location, "operator[] is not defined for non array types.");
	}

	// Shrink the type array levels by one.
	resolvedType = exprType;
	resolvedType.SetArraySize(resolvedType.GetArrayLevelsCount()-1, 0);

	return resolvedType;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string FuncCall::Internal_GenerateCode(Ast* ast)
{
	// First check if this is a special function (determined by the name of the function). 
	// If so do the special logic.
	if(fnName == "takeSample")
	{
		if(args.size() != 2)
		{
			throw ParseExcept(location, "Invalid call to takeSample(<TextureType>, <samplingArgs>).");
		}

		// Get the given argument types and find out what call actually we have.
		const TypeDesc textureType = args[0]->DeduceType(ast);
		const TypeDesc samplingCoordType = args[1]->DeduceType(ast);

		if(textureType.IsSame(Type_Texture2D, false) && samplingCoordType.IsSame(Type_vec2f, false)==false) {
			throw ParseExcept(location, "Invalid call to takeSample(Texture2D texture, vec2f samplingUV).");
		}

		if(textureType.IsSame(Type_TextureCube, false) && samplingCoordType.IsSame(Type_vec3f, false)==false) {
			throw ParseExcept(location, "Invalid call to takeSample(TextureCube texture, vec3f samplingNormal).");
		}

		const std::string textureCode = args[0]->GenerateCode(ast);
		const std::string samplingPtCode = args[1]->GenerateCode(ast);

		// Texture sampling.
		if(ast->OutLangIs(OL_HLSL))
		{
			// [TODO][HARDCODED] the sampler name is generated by diractly appending _sgeSS which is wrong.
			return textureCode + ".Sample(" + textureCode + "_sgeSS," + samplingPtCode + ")";
		}
		else if(ast->OutLangIs(OL_GLSL))
		{
			if(textureType.IsSame(Type_Texture2D, false)) return "texture2D(" + textureCode + "," + samplingPtCode + ")";
			else if(textureType.IsSame(Type_TextureCube, false)) return "textureCube(" + textureCode + "," + samplingPtCode + ")";
			else
			{
				// [TODO] write the actual typename.
				throw ParseExcept(location, "takeSample is not implemented for this type.");
			}
		}
		else
		{
			// Should never happen.
			XSR_ASSERT(false);
			throw ParseExcept(location, "Invalid code path in FuncCall::Internal_GenerateCode.");
		}
	}
	
	else if(fnName == "discard") 
	{
		// Discarded as a function call.
		return "discard;";
	}
	else 
	{
		// Regular functions.
		std::string callFnName; // Stores the actual function name that will be called.

		// Check if this is a type constructor (vec3f(...) vec4f(...) ect...)
		for(int t = Type_BuiltInTypeBegin + 1; t < Type_BuiltInTypeEnd; ++t)
		{
			const std::string typeName = TypeDesc::GetXShaderTypeName((Type)t);

			if(typeName.empty()){
				throw ParseExcept(location, "A unnamed type found!");
			}
		
			if(fnName == typeName) 
			{
				TypeDesc type(false, (Type)t);
				//Assert(type.GetArraySize() == 0); //[TODO] Arrays if possible.
				callFnName = type.GetTypeAsString(ast->lang, true);
				break;
			}
		}

		// Both HLSL and GLSL lerp/mix functions are supported.
		if(ast->OutLangIs(OL_HLSL) && fnName == "mix") callFnName = "lerp";
		if(ast->OutLangIs(OL_GLSL) && fnName == "lerp") callFnName = "mix";
	
		// If this is just a regular function call.
		if(callFnName.empty()) {
			callFnName = fnName;
		}

		std::string retval = callFnName + '(';
	
		for(int t = 0; t < args.size(); ++t) {
			retval += args[t]->GenerateCode(ast);
			if(t < args.size() - 1) retval += ",";
		}

		retval += ')';
	
		return retval;
	}
}

void FuncCall::Internal_Declare(Ast* ast)
{
	for(auto& arg : args) arg->Declare(ast);
}

TypeDesc FuncCall::Internal_DeduceType(Ast* ast)
{
	if(resolvedType.IsUndeduced()==false){
		return resolvedType;
	}

	// [HARDCODED]
	// Function calls type deduction has special behavior for some specific functions that is hardcoded here.
	// The right thing to do is to support multiple function declaration(based on the argument types),
	// but currently these functions are the only real cases(or at least known to me).
	// linear interpolation support both hlsl "lerp" and glsl "mix".
	if(fnName == "lerp" || fnName == "mix" || fnName == "clamp" || fnName == "smoothstep")
	{
		if(args.size() != 3)
		{
			throw ParseExcept(location, "Invalid call to "+fnName+"(T a, T b, float t)");
		}

		// Check if the reference types are the same.
		if(args[0]->DeduceType(ast).IsSame(args[1]->DeduceType(ast), false)==false)
		{
			throw ParseExcept(location, "Invalid call to "+fnName+"(T a, T b, float t)");
		}

		// Check if the interpolation coefficient is a float.
		if(args[2]->DeduceType(ast).IsSame(Type_float, false)==false)
		{
			throw ParseExcept(location, fnName+" interpolation coefficient isn't a float!"); // the interpolation coeff must be a float.
		}

		resolvedType = args[1]->DeduceType(ast);
	}

	if(fnName == "dot")
	{
		if(args.size() != 2){
			throw ParseExcept(location, "Invalid call to dot(vec*, vec*).");
		}

		const TypeDesc& td0 = args[0]->DeduceType(ast);
		const TypeDesc& td1 = args[1]->DeduceType(ast);

		if(td0.IsSame(td1, false) == false)
		{
			throw ParseExcept(location, "dot(vec*, vec*) called with mixed argument types."); 
		}

		if(td0.IsSame(Type_vec2f, false) || td0.IsSame(Type_vec3f, false) || td0.IsSame(Type_vec4f, false))
		{
			resolvedType = TypeDesc(true, Type_float);
		}
		else
		{
			throw ParseExcept(location, "dot(vec*, vec*) with non floating point vector type. [TODO] Fix this!");
		}
	}

	if(fnName == "cross")
	{
		const TypeDesc& td0 = args[0]->DeduceType(ast);
		const TypeDesc& td1 = args[1]->DeduceType(ast);

		// Check if both types are vec3f.
		if(td0.IsSame(Type_vec3f,false) && td1.IsSame(Type_vec3f,false))
		{
			throw ParseExcept(location, "Invalid call to cross(vec3f a, vec3f b)");
		}

		resolvedType = TypeDesc(true, Type_vec3f);
	}

	if(fnName == "normalize")
	{
		if(args.size() != 1) throw ParseExcept(location, "normalize must be called with exactly one argument.");

		const TypeDesc& td = args[0]->DeduceType(ast);
		if(td.IsSame(Type_vec2f, false) || td.IsSame(Type_vec3f, false) || td.IsSame(Type_vec4f, false))
		{
			resolvedType = td;
		}
		else
		{
			throw ParseExcept(location, "Invalid call to normalize(vec*f)");
		}
	}

	if(fnName == "transpose")
	{
		if(args.size() != 1) {
			throw ParseExcept(location, "transpose must be called with exactly one argument.");
		}

		resolvedType = args[0]->DeduceType(ast);
	}

	// Check if this is a type constructor.
	if(resolvedType.IsUndeduced())
	{
		for(int t = Type_BuiltInTypeBegin + 1; t < Type_BuiltInTypeEnd; ++t)
		{
			const std::string typeName = TypeDesc::GetXShaderTypeName((Type)t);
		
			if(typeName.empty()){
					throw ParseExcept(location, "A unnamed type found!");
				}

			if(fnName == typeName) 
			{
				resolvedType = TypeDesc(true, (Type)t);
				break;
			}
		}
	}

	// Just a regualr function call.
	if(resolvedType.IsUndeduced())
	{	
		resolvedType = ast->findFuncDecl(fnName).retType;
	}

	return resolvedType;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string ExprLiteral::Internal_GenerateCode(Ast* ast)
{
	char buff[64] = {0};
	if(type.GetBuiltInType() == Type_float)
	{
		sprintf(buff, "%f", float_val);

		// Kill the trailing zeroes.
		for(int t = strlen(buff);t > 1; --t){
			if(buff[t] == '0' && buff[t-1] == '0') {
				buff[t] = '\0';
			}
			if(buff[t] == '.') break;
		}

		return buff;
	}
	else if(type.GetBuiltInType() == Type_int)
	{
		sprintf(buff, "%d", int_val);

		return buff;
	}

	throw ParseExcept(location, "Unknown literal type.");
}

TypeDesc ExprLiteral::Internal_DeduceType(Ast* ast) 
{
	return type;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TypeDesc ExprBlock::Internal_DeduceType(Ast* ast)
{
	if(resolvedType.IsUndeduced())
	{
		if(exprs.size() == 0) {
			throw ParseExcept(location, "Invalid ExprBlock. No expressions are specified");
		}

		// All types should match, otherwise this block is invalid.
		resolvedType = exprs[0]->DeduceType(ast);
		for(int t = 1; t < exprs.size(); ++t)
		{
			if(resolvedType.IsSame(exprs[t]->DeduceType(ast), false))
			{
				throw ParseExcept(location, "Mixed types in ExprBlock");
			}
		}

		resolvedType.SetArraySize(resolvedType.GetArrayLevelsCount(), exprs.size());
	}

	return resolvedType;
}

std::string ExprBlock::Internal_GenerateCode(Ast* ast)
{
	if(ast->OutLangIs(OL_HLSL))
	{
		std::string retval = "{";

		for(int t = 0; t < exprs.size(); ++t)
		{
			retval += exprs[t]->GenerateCode(ast);
			retval += ',';
		}

		// Replace the last comma with }.
		retval.back() = '}';

		return retval;
	}
	else if(ast->OutLangIs(OL_GLSL))
	{
		std::string retval = resolvedType.GetTypeAsString(ast->lang, false);
		retval += "(";

		for(int t = 0; t < exprs.size(); ++t)
		{
			retval += exprs[t]->GenerateCode(ast);
			retval += ',';
		}

		// Replace the last comma with ).
		retval.back() = ')';

		return retval;
	}
	else
	{
		throw ParseExcept(location, "Unknown output language!");
	}

	return "{not-implemented}";
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string Assign::Internal_GenerateCode(Ast* ast)
{
	return lval->GenerateCode(ast) + " = " + expr->GenerateCode(ast);
}

void Assign::Internal_Declare(Ast* ast)
{
	lval->Declare(ast);
	expr->Declare(ast);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string StmtNativeCode::Internal_GenerateCode(Ast* ast)
{
	return code;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string StmtIf::Internal_GenerateCode(Ast* ast)
{
	std::string retval = "if(" + expr->GenerateCode(ast) + ")";
	if(trueStmt) retval += trueStmt->GenerateCode(ast); else retval += ';';
	if(falseStmt) retval += "else " + falseStmt->GenerateCode(ast);
	return retval;
}

void StmtIf::Internal_Declare(Ast* ast)
{
	expr->Declare(ast);

	if(trueStmt)
	{
		ast->declPushScope();
		trueStmt->Declare(ast);
		ast->declPopScope();
	}

	if(falseStmt)
	{
		ast->declPushScope();
		falseStmt->Declare(ast);
		ast->declPopScope();
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string StmtWhile::Internal_GenerateCode(Ast* ast)
{
	std::string retval = "while(" + expr->GenerateCode(ast) + ")";
	if(bodyStmt) retval += bodyStmt->GenerateCode(ast); 
	else retval += ';';
	return retval;
}

void StmtWhile::Internal_Declare(Ast* ast)
{
	if(expr) expr->Declare(ast);

	if(bodyStmt)
	{
		ast->declPushScope();
		bodyStmt->Declare(ast);
		ast->declPopScope();
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string StmtFor::Internal_GenerateCode(Ast* ast)
{
	std::string retval = "for(";
	if(vardecl) retval +=  vardecl->GenerateCode(ast); retval += ';';
	if(boolExpr) retval += boolExpr->GenerateCode(ast); retval += ';';
	if(postExpr) retval += postExpr->GenerateCode(ast); 
	retval += ')';
	retval += stmt->GenerateCode(ast);

	return retval;
}

void StmtFor::Internal_Declare(Ast* ast)
{
	if(vardecl)
	{
		ast->declPushScope();
		vardecl->Declare(ast);
		ast->declPopScope();
	}

	if(boolExpr) boolExpr->Declare(ast);

	if(stmt) 
	{
		ast->declPushScope();
		stmt->Declare(ast);
		ast->declPopScope();
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string StmtReturn::Internal_GenerateCode(Ast* ast)
{
	if(expr != nullptr)
	{
		return std::string("return ") + expr->GenerateCode(ast) + ";";
	}

	return "return;";
}

void StmtReturn::Internal_Declare(Ast* ast)
{
	if(expr) expr->Declare(ast);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string StmtList::Internal_GenerateCode(Ast* ast)
{
	std::string retval;
	for(auto& node : nodes) retval += node->GenerateCode(ast);
	return retval;
}

void StmtList::Internal_Declare(Ast* ast)
{
	for(auto& node : nodes) {
		node->Declare(ast);
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string VarDecl::Internal_GenerateCode(Ast* ast)
{
	std::string retval;

	const TypeDesc type = typeNode->resolvedType;

	if(type.IsArray() == false)
	{
		// Non-Arrays
		retval += type.GetTypeAsString(ast->lang, true) + " ";

		for(int t = 0; t < ident.size(); ++t)
		{
			retval += ident[t];
			if(expr[t]) retval += "=" + expr[t]->GenerateCode(ast);
			if(t < ident.size() - 1) retval += ',';
		}
	}
	else
	{
		// Arrays
		std::string arraySizesString;
		for(int iLevel = 0; iLevel < type.GetArrayLevelsCount(); ++iLevel) {
			char temp[32] = { 0 };
				sprintf(temp, "[%d]", type.GetArraySize(iLevel) );
				arraySizesString += temp;
		}

		const std::string typeAsString = type.GetTypeAsString(ast->lang, true) + " ";

		for(int t = 0; t < ident.size(); ++t)
		{
			retval += typeAsString + ident[t] + arraySizesString;
			if(expr[t]) retval += "=" + expr[t]->GenerateCode(ast);
			if(t < ident.size() - 1) retval += ';';
		}
	}

	return retval;
}

void VarDecl::Internal_Declare(Ast* ast)
{
	const TypeDesc type = typeNode->DeduceType(ast);

	for(int t = 0; t < ident.size(); ++t)
	{
		ast->declareVariable(type, ident[t]);
		if(expr[t]) expr[t]->Declare(ast);
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string FnDeclArgVarDecl::Internal_GenerateCode(Ast* ast)
{
	std::string retval;
	if(argType == FNAT_InOut) retval += "inout ";
	if(argType == FNAT_Out) retval += "out ";

	retval += type.GetTypeAsString(ast->lang, true) + " " + ident;
	if(expr) retval += "=" + expr->GenerateCode(ast);
	return retval;
}

void FnDeclArgVarDecl::Internal_Declare(Ast* ast)
{
	ast->declareVariable(type, ident);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string FuncDecl::Internal_GenerateCode(Ast* ast)
{
	std::string retval;

	// Check if this is a special function, that needs special attention.
	// For GLSL the main function is just a regular function.
	if(ast->OutLangIs(OL_HLSL) && name == "main")
	{
		retval += GenerateMainFuncHLSL(ast);
	}
	else
	{
		// Just a regular function.
		retval = retType.GetTypeAsString(ast->lang, true) + " " + name + "(";

		for(int t = 0; t < args.size(); ++t) {
			retval += args[t]->GenerateCode(ast);
			if(t < args.size() - 1) retval += ',';
		}

		retval += "){" + stmt->GenerateCode(ast) + "}";
	}

	return retval;
}

std::string FuncDecl::GenerateMainFuncHLSL(Ast* ast)
{
	std::string retval;

	// 1st output the definition of the result strcture for the main function. 
	// Usually this is just output varyings + stage specific output.
	{
		retval += "struct " + HLSL_ShaderResultStruct + " {";

		// The user specified output varyings.
		for(const auto& var : ast->stageOutputVaryings) {
			retval += var.type.GetTypeAsString(ast->lang, true) + " " + var.varName + " : " + var.varName + ";";
		}

		// Stage specific output with SV_*.
		for(const auto& var : ast->keywordVariablesMentioned) {
			if(var->trait == VarTrait_StageSpecificOutput)
			{
				retval += var->type.GetTypeAsString(ast->lang, true) + " " + var->fullName + " : " + var->hlslSemantic + ";";
			}
		}

		retval += "};";
	}

	//The function arguments, usually vertex attributes or input varyings.
	{
		retval += HLSL_ShaderResultStruct + " main(";

		// Vertex attributes input.
		for(auto& attrib : ast->vertexAttribs) {
			retval += attrib.type.ComposeVarDecl(ast->lang, attrib.varName) + " : " + attrib.semantic + ",";
		}

		// Varyings input.
		for(auto& var : ast->stageInputVaryings) {
			retval += var.type.ComposeVarDecl(ast->lang, var.varName) + " : " + var.varName + ",";
		}

		// Stage specific input with SV_*.
		for(const auto& var : ast->keywordVariablesMentioned) {
			if (var->trait == VarTrait_StageSpecificInput) {
				retval += var->type.ComposeVarDecl(ast->lang, var->fullName) + " : " + var->hlslSemantic + ",";
			}
		}

		// Pop the last comma.
		if(retval.back() == ',') retval.pop_back(); 

		retval += ")";
	}

	// Fianlly generate the function body itself.
	// Also add at the begining and and at the ending 
	// the shader program result(varyings, vertex, fargment data ect.)
	{
		retval += '{';
		retval += HLSL_ShaderResultStruct + " " + HLSL_ShaderResultVar + ";";
		retval += stmt->GenerateCode(ast);
		retval += "return " + HLSL_ShaderResultVar + ";";
		retval += '}';
	}

	return retval;
}


void FuncDecl::Internal_Declare(Ast* ast)
{
	ast->declPushScope(name);

	ast->declareFunction(retType, name);

	// Declare the local variables
	for(auto& var : args) var->Declare(ast);
	stmt->Declare(ast);

	ast->declPopScope();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string ProgramElem::Internal_GenerateCode(Ast* ast)
{
	std::string retval;

	for(const auto& node : nodes) {
		retval += node->GenerateCode(ast);
	}

	return retval;
}

void ProgramElem::Internal_Declare(Ast* ast)
{
	for(auto& node : nodes) {
		node->Declare(ast);
	}
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
namespace XSR
{
	// Declared in lang.y
	bool XSParseExpression(const char* code, Ast* ast);

	bool XSCompileCode(
		const char* const pCode, 
		const LangSettings& langSettings,
		std::string& result,
		std::string& compilationErrors)
	{
		Ast ast;

		try 
		{
			ast.lang = langSettings;

			// [CAUTION] For some reason FLEX doens't like '\r' symbol (maybe there are others as well...)
			// It crashes randomly somewhere in isatty...
			std::string processedCode = pCode;
			//std::replace(processedCode.begin(), processedCode.end(), '\r', ' ');

			XSParseExpression(processedCode.c_str(), &ast); // Build the AST tree.

			if(!ast.program) {
				throw ParseExcept(ast.bisonParseErrorLocation, ast.bisonParseError.empty() ? "Failed while compiling program!" : ast.bisonParseError);
			}

			// Declare the predefined functions for the language.
			// JUST A REMINDIER: 
			// DOUBLE CHECK THE ORDER OF THE ARGUMENTS OF THE NATIVE FUNCTIONS.
			{
				// [TODO] find a way to implement lerp.clamp ect. they depend on the input type.
				//// Declare lerp.
				//// Keep in mind that we are defining the functions below with float return type. But actually they heve a spec for almost every type.
				//// For now we are safe becase we only care if the expression type is a matrix or not.
				//ast.declareFunction(Type_float, "lerp"); // Lerp is called mix in GLSL. This case is handled in FuncCall.
				//ast.declareFunction(Type_float, "clamp");

				// For hlsl trigonometric functions have vector type specializations, but for now lets pretend
				// that there isn't.
				ast.declareFunction(TypeDesc(true, Type_float), "sin");
				ast.declareFunction(TypeDesc(true, Type_float), "cos");
				ast.declareFunction(TypeDesc(true, Type_float), "tan");
				ast.declareFunction(TypeDesc(true, Type_float), "tan2");

				ast.declareFunction(TypeDesc(true, Type_float), "asin");
				ast.declareFunction(TypeDesc(true, Type_float), "acos");
				ast.declareFunction(TypeDesc(true, Type_float), "atan");

				ast.declareFunction(TypeDesc(true, Type_float), "sincos");

				ast.declareFunction(TypeDesc(true, Type_float), "sqrt");
				ast.declareFunction(TypeDesc(true, Type_float), "rsqrt");

				// Texture sampling
				ast.declareFunction(TypeDesc(true, Type_vec4f), "takeSample");

				// Pixel shader discard statement. We define it as a function.
				ast.declareFunction(TypeDesc(true, Type_void), "discard");
			}

			// Declare the vertex attributes, io varyings, and uniforms.
			{
				// Declare all the keyword variables...
				// The languages uses the glsl-style of returning/obtaining stage specific variables.
				// These variables are always implicitly defined(some of them are defined only if used).
				// There is a "mentioned" list stored in the AST that holds a list of mentioned variables in the user's code.
				{
					// Vertex shader outputs
					ast.declaredVariables.push_back(Ast::FullVariableDesc("xsr_VertexOut", TypeDesc(false, Type_vec4f), VarTrait_StageSpecificOutput, "SV_Position", "gl_Position"));
					ast.declaredVariables.push_back(Ast::FullVariableDesc("xsr_VertexID", TypeDesc(false, Type_int), VarTrait_StageSpecificInput, "SV_VertexID", "gl_VertexID"));

					// Pixel shader output
					ast.declaredVariables.push_back(Ast::FullVariableDesc("xsr_PixelOut", TypeDesc(false, Type_vec4f), VarTrait_StageSpecificOutput, "SV_Target", "gl_FragColor" ));
					ast.declaredVariables.push_back(Ast::FullVariableDesc("xsr_PixelNDC", TypeDesc(false, Type_vec4f), VarTrait_StageSpecificInput, "SV_Position", "gl_FragCoord" ));
				};

				// Vertex Attributes.
				// [TODO] Concider to declare these values as locals in main.
				for(const auto& var : ast.vertexAttribs) {
					ast.declareVariable(var.type, var.varName, VarTrait_VertexAttribute);
				}

				// Input varyings. 
				// [TODO] Concider to declare these values as locals in main.
				for(const auto& var : ast.stageInputVaryings)
				{
					ast.declareVariable(var.type, var.varName, VarTrait_StageInVarying);
				}

				// Output varyings.
				// [TODO] Concider to declare these values as locals in main.
				for(const auto& var : ast.stageOutputVaryings)
				{
					ast.declareVariable(var.type, var.varName, VarTrait_StageOutVarying);
				}

				// Declare the global unifroms.
				for(const auto& unif : ast.uniforms)
				{
					ast.declareVariable(unif.type, unif.varName);
				}
			}

			// Declare everything else.
			ast.program->Declare(&ast);

			// Deduce a type for every expression that was matched by bison.
			for(auto n : ast.deductionQueue) {
				n->DeduceType(&ast);
			}

			// CODE GENERATION....

			// GENERATE the declaration code for the attrib varyings for GLSL.
			if(ast.OutLangIs(OL_GLSL))
			{
				// GLSL vertex attributes input and output varyings...

				// Keep in mind that in GLSL there are no sematics. So for vertex attributes
				// we are going to output the semantic rater than the variable name.
				for(const auto& var : ast.vertexAttribs) {
					result += "attribute " + var.type.ComposeVarDecl(ast.lang, var.semantic) + ";";
				}

				for(const auto& var : ast.stageInputVaryings) {
					// [TODO] for older versions of GLSL this should be "vaying" instead of "in".
					result += "in " + var.type.ComposeVarDecl(ast.lang, var.varName) + ";";
				}

				for(const auto& var : ast.stageOutputVaryings) {
					// [TODO] for older versions of GLSL this should be "vaying" instead of out
					result += "out " + var.type.ComposeVarDecl(ast.lang, var.varName) + ";";
				}
			}

			// GENERATE the declaration code for uniforms for both GLSL and HLSL.
			for(const auto& unif : ast.uniforms)
			{
				result += "uniform " + unif.type.ComposeVarDecl(ast.lang, unif.varName) + ";";

				// Textures in HLSL need a sampler. Define 1 sampler for every texture.
				if(ast.lang.outputLanguage == OL_HLSL) {
					//[TODO] Arrays...
					if(unif.type.GetBuiltInType() == Type_Texture2D ||
						 unif.type.GetBuiltInType() == Type_TextureCube) {
						result += "uniform sampler " + unif.varName  + "_sgeSS;";
					}
				}
			}

			// Finally genrate the code form the AST three.
			result += ast.program->GenerateCode(&ast);
			return true;
		}
		catch(const ParseExcept& e) {

			const LineMarker* const errorLocation = ast.findLineMarker(e.errorLoc.line);

			const int errorLine = (errorLocation != nullptr) 
				? errorLocation->targetLine + e.errorLoc.line - errorLocation->sourceLine
				: e.errorLoc.line;

			const char* const errorFile = (errorLocation != nullptr)
				? errorLocation->filename.c_str()
				: ""; // [TODO] Add a default filename.

			if(errorLine >= 0)
			{
				char errorString[1024] = {0};
				sprintf(errorString, "\n%s(%d): error: %s", errorFile, errorLine, e.what());
				compilationErrors += errorString;
			}
			else
			{
				compilationErrors += std::string("\n%s(??): error: %s") + e.what();
			}
			return false;
		}

		return false;
	}

} 