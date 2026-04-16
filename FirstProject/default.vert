#version 330 core
layout (location = 0) in vec3 aPos; //pos has attribute pos 0
layout (location = 1) in vec3 aColor; //color has attribute pos 1
layout (location = 2) in vec2 aTEX; //texture has attribute pos 2
layout (location = 3) in vec3 aNormal;

out vec2 texCoord;
out vec3 normal;
out vec3 currPos;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	currPos = vec3(model * vec4(aPos,1.0f));

	gl_Position = camMatrix * vec4(currPos, 1.0);
	normal = aNormal;

	texCoord = aTEX;
}
 