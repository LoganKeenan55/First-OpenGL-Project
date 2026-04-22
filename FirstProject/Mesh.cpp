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

void Mesh::Draw(Shader& shader, Camera& camera) {
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
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


}