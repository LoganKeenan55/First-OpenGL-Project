#version 330 core
out vec4 FragColor;
in vec4 vertexColor; // input variable from vs (same name and type)

//global
uniform vec4 ourColor;

void main()
{
	FragColor = ourColor;
}
