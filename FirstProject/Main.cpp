#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"camera.h"
#include"Texture.h"

int gScreenWidth = 1920;
int gScreenHeight = 1080;


// Vertices coordinates
GLfloat vertices[] =
{  //   COORDINATES        /        COLORS           /   TexCoord   /     NORMALS      //
-1.0f, 0.0f,  1.0f,			 0.0f, 0.0f, 0.0f,			0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
-1.0f, 0.0f, -1.0f,			 0.0f, 0.0f, 0.0f,			0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
 1.0f, 0.0f, -1.0f,			 0.0f, 0.0f, 0.0f,			1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
 1.0f, 0.0f,  1.0f,			 0.0f, 0.0f, 0.0f,			1.0f, 0.0f,   0.0f, 1.0f, 0.0f
};

GLuint indicies[] = {
	0,1,2,
	0,2,3
};


GLfloat lightVertices[] = {
	-0.1f,-0.1f,0.1f,
	-0.1f,-0.1f,-0.1f,
	0.1f,-0.1f,-0.1f,
	0.1f,-0.1f,0.1f,
	-0.1f,0.1f,0.1f,
	-0.1f,0.1f,-0.1f,
	0.1f,0.1f,-0.1f,
	0.1f,0.1f,0.1f
};

GLuint lightIndices[] = {
	0,3,2,
	2,1,0,
	0,4,7,
	0,7,3,
	3,7,6,
	3,6,2,
	2,6,5,
	2,5,1,
	1,5,4,
	1,4,0,
	4,5,6,
	4,6,7

};

int main() {

	Camera camera(gScreenWidth, gScreenHeight, glm::vec3(0.0f, 0.0f, 2.0f));

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLFWwindow* window = glfwCreateWindow(gScreenWidth, gScreenHeight, "Hello, World!", NULL, NULL);

	if (!window) {
		std::cout << "Failed to create a window" << std::endl;
		glfwTerminate();
		return 0;
	}

	//introduce window to current context
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, gScreenWidth, gScreenHeight);

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
	VAO1.LinkVBO(VBO1, 0,3,11*sizeof(float),(void*)0);
	VAO1.LinkVBO(VBO1, 1,3,11*sizeof(float),(void*)(3*sizeof(float)));
	VAO1.LinkVBO(VBO1, 2,2,11*sizeof(float),(void*)(6*sizeof(float)));
	VAO1.LinkVBO(VBO1, 3,3,11*sizeof(float),(void*)(8*sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f,1.0f);


	//light square
	Shader lightShader("light.vert", "light.frag");
	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkVBO(lightVBO, 0, 3, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	lightShader.setMat4("model", lightModel);
	lightShader.setVec4("lightColor", lightColor);

	shaderProgram.Activate();
	shaderProgram.setMat4("model", pyramidModel);
	shaderProgram.setVec4("lightColor", lightColor);
	shaderProgram.setVec3("lightPos", lightPos);


	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	Texture brick("planks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brick.texUnit(shaderProgram, "tex0", 0);

	while (!glfwWindowShouldClose(window)) {

		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.handleInput(window,deltaTime);
		camera.updateMatrix(60.0f, 0.1f, 100.0f);

		//Pyramid
		glm::mat4 pyramidModel = glm::mat4(1.0f);

		//pyramidModel = glm::rotate(pyramidModel, (float)glfwGetTime() * glm::radians(50.0f),
			//glm::vec3(0.0f, 1.0f, 0.0f));

		shaderProgram.Activate();
		shaderProgram.setMat4("model", pyramidModel);
		VAO1.Bind();
		brick.Bind();

		camera.Matrix(shaderProgram, "camMatrix");
		glDrawElements(GL_TRIANGLES, sizeof(indicies)/sizeof(int), GL_UNSIGNED_INT, 0);
		shaderProgram.setVec3("camPos", camera.Position);

		
		//light
		lightShader.Activate();
		lightShader.setMat4("model", lightModel);
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices)/sizeof(int), GL_UNSIGNED_INT, 0);




		VAO1.Bind();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	brick.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
