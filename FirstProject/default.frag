#version 330 core
out vec4 FragColor;
in vec4 vertexColor; // input variable from vs (same name and type)
void main()
{
	FragColor = vertexColor;
}
