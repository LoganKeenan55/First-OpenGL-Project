#version 330 core
out vec4 FragColor;
in vec3 ourColor; // input variable from vs (same name and type)

uniform float offset;  
void main()
{
	FragColor = vec4(ourColor,1.0)+offset;
}
