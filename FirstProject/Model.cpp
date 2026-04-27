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