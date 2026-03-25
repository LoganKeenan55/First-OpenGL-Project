#version 330 core
out vec4 fragColor;
in vec3 ourColor; // input variable from vs (same name and type)
in vec2 texCoord;

uniform sampler2D tex0;
uniform float time;

uniform float offset;  
void main()
{
	fragColor =  texture(tex0, texCoord);

}
