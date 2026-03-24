#version 330 core
layout (location = 0) in vec3 aPos; //pos has attribute pos 0
layout (location = 1) in vec3 aColor; //color has attribute pos 1
layout (location = 2) in vec2 aTEX; //texture has attribute pos 2


out vec2 texCoord;

uniform mat4 transform;
uniform float time;

void main()
{
	
	gl_Position = transform * vec4(aPos, 1.0);
	

	texCoord = aTEX;
}
 