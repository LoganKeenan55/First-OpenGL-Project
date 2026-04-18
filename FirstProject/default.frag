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


vec4 pointLight(){
	



	vec3 lightVector = lightPos - currPos;
	float dist = length(lightVector);
	float a = 1.0f;
	float b = 0.7f;
	float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);

	//ambient
	float ambient = .20f;

	//diffuse
	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(lightVector);

	float diffuse = max(dot(normal,lightDirection),0.0f);

	//specular
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - currPos);
	vec3 reflectionDirection = reflect(-lightDirection,normal);
	float specAmount = pow(max(dot(viewDirection,reflectionDirection),0.0f),16);
	float specular = specAmount * specularLight;
	
	return (texture(tex0, texCoord) * (diffuse * intensity + ambient) + texture(tex1, texCoord).r * specular*intensity) * lightColor;

}

vec4 directLight(vec3 direction){

	float ambient = .20f;
	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(direction);

	float diffuse = max(dot(normal,lightDirection),0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - currPos);
	vec3 reflectionDirection = reflect(-lightDirection,normal);
	float specAmount = pow(max(dot(viewDirection,reflectionDirection),0.0f),16);
	float specular = specAmount * specularLight;
	
	return (texture(tex0, texCoord) * (diffuse + ambient) + texture(tex1, texCoord).r * specular) * lightColor;

}

void main()
{
	fragColor = directLight(vec3(1.0f,1.0f,1.0f));
}
