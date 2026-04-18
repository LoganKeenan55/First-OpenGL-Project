#version 330 core
out vec4 fragColor;
in vec3 ourColor; // input variable from vs (same name and type)
in vec2 texCoord;

in vec3 normal;
in vec3 currPos;


uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float time;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;


uniform float offset;  
void main()
{

	float ambient = .15f;
	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(lightPos - currPos);

	float diffuse = max(dot(normal,lightDirection),0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - currPos);
	vec3 reflectionDirection = reflect(-lightDirection,normal);
	float specAmount = pow(max(dot(viewDirection,reflectionDirection),0.0f),16);
	float specular = specAmount * specularLight;
	
	fragColor =  texture(tex0, texCoord) * lightColor * (diffuse+ambient) +texture(tex1, texCoord).r * specular;

}
