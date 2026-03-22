#version 330 core
out vec4 FragColor;
in vec3 ourColor; // input variable from vs (same name and type)
in vec2 texCoord;

uniform sampler2D tex0;

uniform float offset;  
void main()
{
	FragColor = texture(tex0,texCoord);
}
