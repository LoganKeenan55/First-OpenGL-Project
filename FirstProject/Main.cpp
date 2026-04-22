#include"Mesh.h"

int gScreenWidth = 1920;
int gScreenHeight = 1080;


// Vertices coordinates
Vertex vertices[] =
{
	Vertex{glm::vec3(-2.0f, 0.0f,  2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-2.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 2.0f)},
	Vertex{glm::vec3(2.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(2.0f, 2.0f)},
	Vertex{glm::vec3(2.0f, 0.0f,  2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(2.0f, 0.0f)}
};

GLuint indices[] = {
	0,1,2,
	0,2,3
};


Vertex lightVertices[] = {
	Vertex{glm::vec3(-0.1f,-0.1f,0.1f)},
	Vertex{glm::vec3(-0.1f,-0.1f,-0.1f)},
	Vertex{glm::vec3(0.1f,-0.1f,-0.1f)},
	Vertex{glm::vec3(0.1f,-0.1f,0.1f)},
	Vertex{glm::vec3(-0.1f,0.1f,0.1f)},
	Vertex{glm::vec3(-0.1f,0.1f,-0.1f)},
	Vertex{glm::vec3(0.1f,0.1f,-0.1f)},
	Vertex{glm::vec3(0.1f,0.1f,0.1f)}
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
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, gScreenWidth, gScreenHeight);


	Texture textures[]{
		Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};


	//creates a shader object
	Shader shaderProgram("default.vert", "default.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh floor(verts, ind, tex);


	//light square
	Shader lightShader("light.vert", "light.frag");
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh light(lightVerts, lightInd, tex);



	glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 0.5f);
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



	while (!glfwWindowShouldClose(window)) {

		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.handleInput(window,deltaTime);
		camera.updateMatrix(60.0f, 0.1f, 100.0f);

		floor.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();
	lightShader.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
