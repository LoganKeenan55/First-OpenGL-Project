#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<json/json.h>
#include"Mesh.h"

using json = nlohmann::json;

class Model {
public:
	Model(const char* file);

	void Draw(Shader& shader, Camera& camera);

private:
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	std::vector<unsigned char> getData();
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);

	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);

};

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
		

	}


}	
	



#endif