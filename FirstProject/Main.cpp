#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

int gScreenWidth = 800;
int gScreenHeight = 800;


float vertices[] = {
		//pos				 //colors			//texture coords
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f, //bottom left
		0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,	1.0f, 0.0f,  //bottem right
		-0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  //upper left
		0.5f, 0.5f, 0.0f,    1.0f, 1.0f, 1.0f,	1.0f, 1.0f  //upper right
};

GLuint indicies[] = {
	0,1,2,
	1,3,2
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
	VAO1.LinkVBO(VBO1, 0,3,8*sizeof(float),(void*)0);
	VAO1.LinkVBO(VBO1, 1,3,8*sizeof(float),(void*)(3*sizeof(float)));
	VAO1.LinkVBO(VBO1, 2,2,8*sizeof(float),(void*)(6*sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//texture
	int imgWidth, imgHeight, numColorChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("birb.png", &imgWidth, &imgHeight, &numColorChannels, 0);

	GLuint texture;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	GLenum format;
	if (numColorChannels == 4)
		format = GL_RGBA;
	else if (numColorChannels == 3)
		format = GL_RGB;
	else if (numColorChannels == 1)
		format = GL_RED;

	glTexImage2D(GL_TEXTURE_2D, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	
	
	shaderProgram.setInt("text0", 0);

	while (!glfwWindowShouldClose(window)) {


		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		float timeValue = glfwGetTime();
		shaderProgram.setFloat("time", timeValue);


		
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glDeleteTextures(1, &texture);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}