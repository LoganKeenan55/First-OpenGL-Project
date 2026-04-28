#include"Mesh.h"
#include <cstddef>

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures) {
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	VAO.Bind();

	//generates vertex buffer object
	//holds vertices
	VBO VBO(vertices);

	//generates element buffer object
	//holds indices
	EBO EBO(indices);

	//links VBO to VAO
	VAO.LinkVBO(VBO, 0, 3, sizeof(Vertex), (void*)offsetof(Vertex, position));
	VAO.LinkVBO(VBO, 1, 3, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	VAO.LinkVBO(VBO, 2, 3, sizeof(Vertex), (void*)offsetof(Vertex, color));
	VAO.LinkVBO(VBO, 3, 2, sizeof(Vertex), (void*)offsetof(Vertex, textUV));

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();


}

void Mesh::Draw(
	Shader& shader,
	Camera& camera,
	glm::mat4 matrix,
	glm::vec3 translation,
	glm::quat rotation,
	glm::vec3 scale
) {
	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular= 0;

	for (int i = 0; i < textures.size();i++) {
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse") {
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular") {
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	camera.Matrix(shader, "camMatrix");
	shader.setVec3("camPos", camera.Position);

	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	rot = glm::rotate(rot, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	sca = glm::scale(sca, scale);


	shader.setMat4("translation", trans);
	shader.setMat4("rotation", rot);
	shader.setMat4("scale", sca);
	shader.setMat4("model", matrix);


	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


}