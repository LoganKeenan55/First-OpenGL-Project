#version 330 core
layout (location = 0) in vec3 aPos; //pos has attribute pos 0
layout (location = 1) in vec3 aColor; //color has attribute pos 1
layout (location = 2) in vec2 aTEX; //texture has attribute pos 2


out vec3 ourColor;
out vec2 texCoord;

uniform float offset;

void main()
{
	gl_Position = vec4(aPos, 1.0)+vec4(offset,0,0,0); 
	ourColor = aColor; //set ourColor to color from the vertex data
	texCoord = aTEX;
}
 