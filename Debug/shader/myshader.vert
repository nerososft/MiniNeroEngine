#version 130

in vec3 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;


out vec3 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

//uniform mat4 P;

void main(){

 //gl_Position.xy = (P*vec4(vertexPosition,0.0f,1.0f)).xy;

 gl_Position.xyz =vertexPosition;

  gl_Position.w = 1.0;
  
  fragmentPosition = vertexPosition;
  fragmentColor = vertexColor;
  fragmentUV = vec2(vertexUV.x,1-vertexUV.y);
}