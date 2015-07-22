# XShader(XSR)
#[CAUTION] : This is a "pre-beta" project that is still in development.

XShader is (going to be) custom language designed to be compiled to HLSL, GLSL(and eventually other shading languages).

The language parser is implemented using FLEX/BISON.

The main goal(that isn't reached yet) of the project is to provide something that is reasonably modifiable by other 
programmers rather than a compleate solution to the problem (although I'm thinking of trying).

Example minamal vertex shader: 

[XSR]
```C++
attribute vec3f a_pos : a_position;

uniform mat4f projView;
uniform mat4f world;

void main() {
	vec4f worldPos = world * vec4f(a_pos, 1.0);
	xsr_VertexOut = projView * worldPos;
}
```

Looks in:

[HLSL]
```C++
uniform float4x4 projView;
uniform float4x4 world;
struct XSR_SHADER_RESULT  {
  float4 xsr_VertexOut : SV_Position;

}
;
XSR_SHADER_RESULT main(float3 a_pos : a_position) {
  XSR_SHADER_RESULT XSR_shader_result;
  float4 worldPos=mul(world, float4(a_pos, 1.0));
  XSR_shader_result.xsr_VertexOut = mul(projView, worldPos);
  return XSR_shader_result;

}
```

[GLSL]
```C++
attribute vec3 a_position;
uniform mat4 projView;
uniform mat4 world;
void main() {
  vec4 worldPos=world * vec4(a_position, 1.0);
  gl_Position = projView * worldPos;
}
```

