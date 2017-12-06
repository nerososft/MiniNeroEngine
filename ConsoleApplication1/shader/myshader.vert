#version 130

in vec3 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;
in vec3 vertexNormal;


out vec3 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;
out vec3 fragmentNormal;

uniform mat4 P;

void main(){

  gl_Position.xyz = (P*vec4(vertexPosition,1.0f)).xyz;

  gl_Position.w = 1.0;
  
  fragmentPosition = vertexPosition;
  fragmentColor = vertexColor;
  fragmentUV = vec2(vertexUV.x,1-vertexUV.y);
  fragmentNormal = vertexNormal;
}