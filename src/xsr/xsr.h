// DO NOT POLLUTE this file with ANY SGE_DEFINITIONS
#pragma once

#include <string>

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
		OutputLanguage outputLanguage;
		ShaderType shaderType;
	};

	bool XSCompileCode(
		const char* const pCode, 
		const LangSettings langSettings,
		std::string& result,
		std::string& compilationErrors);
}
