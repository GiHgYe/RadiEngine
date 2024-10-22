#version 330 core

#define PI 3.1415926535897932384626433832795
#define PI_2 6.283185307
#define INV_PI 0.31830988618
#define INV_2PI 0.15915494309

uniform sampler2D u_diffuseMap0;
//uniform sampler2D specularMap0;
//uniform float metallic;
//uniform float roughness;
//uniform float ao;

//uniform vec3 u_cameraPos;
//uniform vec3 u_lightPos;
//uniform vec3 u_lightDir;
//uniform vec3 u_lightIntensity;

in vec2 uv;


out vec4 fragColor;

void main()
{
	vec3 color = texture(u_diffuseMap0, uv).rgb;
    fragColor = vec4(color, 1.0);
}