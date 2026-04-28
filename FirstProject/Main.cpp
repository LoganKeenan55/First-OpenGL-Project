#include"model.h"

int gScreenWidth = 1920;
int gScreenHeight = 1080;



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
	Model model("models/bunny/scene.gltf");

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, gScreenWidth, gScreenHeight);


	//creates a shader object
	Shader shaderProgram("default.vert", "default.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(-1.0f, 1.0f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);


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

		camera.handleInput(window,deltaTime);
		camera.updateMatrix(60.0f, 0.1f, 100.0f);

		model.Draw(shaderProgram, camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
