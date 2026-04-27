#include "model.h"

Model::Model(const char* file) {
	std::string text = get_file_contents(file);
	JSON = json::parse(text);

	Model::file = file;
	data = getData();
}

std::vector<unsigned char> Model::getData() {
	std::string bytesText;
	std::string uri = JSON["buffers"][0]["uri"];

	std::string fileStr = std::string(file);
	
	//build correct path file = "assets/models/cube.gltf"
	std::string fileDirectory = fileStr.substr(0, fileStr.find_last_not_of('/') + 1);

	//read the file and turn it into bytes
	bytesText = get_file_contents((fileDirectory + uri).c_str());
	std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
	
	return data;
}
std::vector<float> Model::getFloats(json accessor) {
	std::vector<float> floatVec;

	unsigned int buffViewInd = accessor.value("bufferView", 1);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	std::string type = accessor["type"];

	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	unsigned int numPerVert;
	if (type == "SCALAR") numPerVert = 1;
	else if (type == "VEC2") numPerVert = 2;
	else if (type == "VEC3") numPerVert = 3;
	else if (type == "VEC4") numPerVert = 4;
	else throw std::invalid_argument("Type is invalid");

	unsigned int beginningOfData = byteOffset + accByteOffset;
	unsigned int lengthOfData = count * 4 * numPerVert;
	for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData;i) {
		unsigned char bytes[] = { data[i++],data[i++],data[i++],data[i++] };
		float value;
		std::memcpy(&value, bytes, sizeof(float));
		floatVec.push_back(value);


	}
	return floatVec;

}

std::vector<GLuint> Model::getIndices(json accessor) {
	std::vector<GLuint> indices;

	unsigned int buffViewInd = accessor.value("bufferView", 0);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	unsigned int componentType = accessor["componentType"];

	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	unsigned int beginningOfData = byteOffset + accByteOffset;
	//unsigned int
	if (componentType == 5125) {

		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4;i) {
			unsigned char bytes[] = { data[i++],data[i++],data[i++],data[i++] };
			unsigned int  value;
			std::memcpy(&value, bytes, sizeof(unsigned int));
			indices.push_back((GLuint)value);

		}

	}
	//unsigned short
	else if (componentType == 5123) {

		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4;i) {
			unsigned char bytes[] = { data[i++],data[i++],data[i++],data[i++] };
			unsigned short  value;
			std::memcpy(&value, bytes, sizeof(unsigned short));
			indices.push_back((GLuint)value);

		}

	}
	//short
	else if (componentType == 5122) {

		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4;i) {
			unsigned char bytes[] = { data[i++],data[i++],data[i++],data[i++] };
			short value;
			std::memcpy(&value, bytes, sizeof(short));
			indices.push_back((GLuint)value);

		}

	}

	return indices;
}

std::vector<glm::vec2> Model::groupFloatsVec2(std::vector<float> floatVec) {
	std::vector<glm::vec2> vectors;
	for (int i = 0; i < floatVec.size();i) {
		vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
	}
	return vectors;

}

std::vector<glm::vec3> Model::groupFloatsVec3(std::vector<float> floatVec) {
	std::vector<glm::vec3> vectors;
	for (int i = 0; i < floatVec.size();i) {
		vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;

}

std::vector<glm::vec4> Model::groupFloatsVec4(std::vector<float> floatVec) {
	std::vector<glm::vec4> vectors;
	for (int i = 0; i < floatVec.size();i) {
		vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;

}

std::vector<Vertex> assembleVertices(
	std::vector<glm::vec3> positions,
	std::vector<glm::vec3> normals,
	std::vector<glm::vec2> texUvs
){
	std::vector<Vertex> vertices;
	for (int i = 0; i < positions.size(); i++) {
		vertices.push_back(
			Vertex{
				positions[i],
				normals[i],
				glm::vec3(1.0f,1.0f,1.0f),
				texUvs[i]
			}
		);

	}

}