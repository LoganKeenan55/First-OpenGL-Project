#include"model.h"

int gScreenWidth = 1920;
int gScreenHeight = 1080;


// floor vertices
Vertex vertices[] =
{
	//position, normal, color, textUV
	Vertex{glm::vec3(-2.0f, 0.0f,  2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-2.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 4.0f)},
	Vertex{glm::vec3(2.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(4.0f, 4.0f)},
	Vertex{glm::vec3(2.0f, 0.0f,  2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(4.0f, 0.0f)}
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};


int main() {

	Camera camera(gScreenWidth, gScreenHeight, glm::vec3(0.0f, 0.5f, 3.0f));

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

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, gScreenWidth, gScreenHeight);


	//bunny model
	Model model("models/bunny/scene.gltf");


	//textures for the ground
	Texture textures[]
	{
		Texture("planks.png", "diffuse", 0),
		Texture("planksSpec.png", "specular", 1)
	};


	//main shader
	Shader shaderProgram("default.vert", "default.frag");


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);


	//floor mesh
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh floor(verts, ind, tex);


	//model matrices
	glm::mat4 floorModel = glm::mat4(1.0f);

	glm::mat4 bunnyModel = glm::mat4(1.0f);
	bunnyModel = glm::translate(bunnyModel, glm::vec3(0.0f, 0.0f, 0.0f));


	//set main shader uniforms
	shaderProgram.Activate();
	shaderProgram.setVec4("lightColor", lightColor);
	shaderProgram.setVec3("lightPos", lightPos);


	float deltaTime = 0.0f;
	float lastFrame = 0.0f;


	while (!glfwWindowShouldClose(window)) {

		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.handleInput(window, deltaTime);
		camera.updateMatrix(60.0f, 0.1f, 100.0f);


		//draw floor
		shaderProgram.Activate();
		shaderProgram.setMat4("model", floorModel);
		shaderProgram.setVec4("lightColor", lightColor);
		shaderProgram.setVec3("lightPos", lightPos);
		floor.Draw(shaderProgram, camera);


		//draw bunny
		shaderProgram.Activate();
		shaderProgram.setMat4("model", bunnyModel);
		shaderProgram.setVec4("lightColor", lightColor);
		shaderProgram.setVec3("lightPos", lightPos);
		model.Draw(shaderProgram, camera);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}