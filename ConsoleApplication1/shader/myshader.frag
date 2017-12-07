#version 130
in vec3 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;
in vec3 fragmentNormal;

out vec4 color;

uniform sampler2D mySampler;
uniform float time;

struct Light
{
    vec3 position;
    vec3 diffuseColor;
    vec3 attenuation;
};

vec3 CalculateContribution(const in Light light, const in vec3
position)
{
    float distance = distance(position, light.position);
    float attenuation = 1.0 / (light.attenuation[0] + light.attenuation[1] * distance + light.attenuation[2] * distance * distance);

    return light.diffuseColor * light.attenuation;
}

void main(){
    vec3 myPosition = vec3(0.0, 0.0, 0.0);
    Light light1 = Light(vec3(10.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0) ,vec3(1.0, 2.0, 3.0));
    Light light2 = Light(vec3(0.0, 10.0, 0.0), vec3(1.0, 0.0, 0.0) ,vec3(1.0, 2.0, 3.0));
    Light light3 = Light(vec3(0.0, 0.0, 10.0), vec3(1.0, 0.0, 0.0) ,vec3(1.0, 2.0, 3.0));
    // Calculate light1
    vec3 finalColor = CalculateContribution(light1, myPosition);
    // Calculate light2
    finalColor += CalculateContribution(light2, myPosition);
    // Calculate light3
    finalColor += CalculateContribution(light3, myPosition);

    vec4 textureColor = texture(mySampler,fragmentUV);
    color = textureColor * fragmentColor *  vec4(fragmentColor.r*(cos(fragmentPosition.x*4.0+time)+1.0)*0.5,
					fragmentColor.g*(cos(fragmentPosition.y*8.0+time)+1.0)*0.5,
			fragmentColor.b*(cos(fragmentPosition.x*16.0+time)+1.0)*0.5,
								fragmentColor.a);
}