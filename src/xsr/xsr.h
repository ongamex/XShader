// DO NOT POLLUTE this file with ANY SGE_DEFINITIONS
#pragma once

#include <string>

#if defined(_DEBUG) && !defined(NDEBUG)
	#ifdef WIN32
		#define XSR_ASSERT(expr) do { if(expr==false) __debugbreak(); } while(false);
	#else
		#define XSR_ASSERT(expr) do { } while(false);
	#endif
#else
	#define XSR_ASSERT(expr) do { } while(false);
#endif

namespace XSR
{
	enum OutputLanguage
	{
		OL_HLSL,
		OL_GLSL
	};

	enum ShaderType
	{
		ST_Vertex,
		ST_Pixel,
	};

	struct LangSettings
	{
		LangSettings(){}
		LangSettings(const OutputLanguage outputLanguage, const ShaderType shaderType) :
			outputLanguage(outputLanguage),
			shaderType(shaderType)
		{}

		OutputLanguage outputLanguage;
		ShaderType shaderType;
	};

	bool XSCompileCode(
		const char* const pCode, 
		const LangSettings& langSettings,
		std::string& result,
		std::string& compilationErrors);
}
