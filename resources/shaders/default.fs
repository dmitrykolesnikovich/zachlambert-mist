#version 330 core
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

out vec3 color;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
};

uniform Material material;

uniform mat4 MV;
uniform vec3 LightPosition_worldspace;

uniform float LightPower;
uniform vec3 LightColor;

void main(){
    vec3 MaterialDiffuseColor = texture(material.diffuse, UV).rgb;
    vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;
    vec3 MaterialSpecularColor = texture(material.specular, UV).rgb;

    float distance = length(LightPosition_worldspace - Position_worldspace);

    vec3 n = normalize(Normal_cameraspace);
    vec3 ld = normalize(LightDirection_cameraspace);
    float dot_n_ld = dot(n,ld);
    float cosTheta = clamp(dot_n_ld, 0, 1);

    vec3 E = normalize(EyeDirection_cameraspace);
    vec3 R = reflect(-ld, n);
    // Only provide specular light if cosTheta > 0
    float cosAlpha = clamp(dot(E,R),0,1) * step(0, dot_n_ld);

    color = MaterialAmbientColor +
            MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
            MaterialSpecularColor * LightPower * pow(cosAlpha,5) / (distance*distance);
}
