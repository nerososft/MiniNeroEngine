#version 130
in vec3 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;
in vec3 fragmentNormal;

out vec4 color;

uniform sampler2D mySampler;

void main(){

vec4 textureColor = texture(mySampler,fragmentUV);
color = textureColor * fragmentColor;
}