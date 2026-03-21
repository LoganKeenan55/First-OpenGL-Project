#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int gScreenWidth = 800;
int gScreenHeight = 800;



int main() {
	 
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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



	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	//clear back buffer and specify new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	//swap back buffer with front buffer
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);


	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}