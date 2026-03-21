#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

int gScreenWidth = 800;
int gScreenHeight = 800;


float vertices[] = {
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f // top left
};

GLuint indicies[] = {
	0,1,3,
	1,2,3

};

int main() {
	 
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLFWwindow* window = glfwCreateWindow(gScreenHeight, gScreenHeight, "Hello, World!", NULL, NULL);

	if (!window) {
		std::cout << "Failed to create a window" << std::endl;
		glfwTerminate();
		return 0;
	}

	//introduce window to current context
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, gScreenHeight, gScreenHeight);

	//creates a shader object
	Shader shaderProgram("default.vert", "default.frag");

	//generates vertex array object
	//holds how to interpret data in VBO
	VAO VAO1;
	VAO1.Bind();

	//generates vertex buffer object
	//holds vertices
	VBO VBO1(vertices, sizeof(vertices));

	//generates element buffer object
	//holds indices
	EBO EBO1(indicies, sizeof(indicies));
	
	//links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	while (!glfwWindowShouldClose(window)) {
		
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + .5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");
		glUseProgram(shaderProgram.ID);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}