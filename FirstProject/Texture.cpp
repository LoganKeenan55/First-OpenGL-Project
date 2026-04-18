#include"Texture.h"

Texture::Texture(const char* image, GLenum textType, GLuint slot, GLenum format, GLenum pixelType) {

	type = textType;
	int imgWidth, imgHeight, numColorChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &imgWidth, &imgHeight, &numColorChannels, 0);

	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(textType, ID);

	glTexParameteri(textType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(textType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(textType, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(textType, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


	if (numColorChannels == 4)
		format = GL_RGBA;
	else if (numColorChannels == 3)
		format = GL_RGB;
	else if (numColorChannels == 1)
		format = GL_RED;

	glTexImage2D(textType, 0, format, imgWidth, imgHeight, 0, format, pixelType, bytes);
	glGenerateMipmap(textType);
	

	stbi_image_free(bytes);
	glBindTexture(textType, 0);

	glEnable(GL_DEPTH_TEST);




}

void Texture::texUnit(Shader shader, const char* uniform, GLuint unit) {

	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, ID);

}

void Texture::Unbind() {
	glBindTexture(type, 0);

}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}