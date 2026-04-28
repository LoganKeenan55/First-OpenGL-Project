#include"Texture.h"

Texture::Texture(const char* image, const char* texType, GLuint slot) {

	type = texType;
	int imgWidth, imgHeight, numColorChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &imgWidth, &imgHeight, &numColorChannels, 0);

	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


	if (numColorChannels == 4)
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			imgWidth,
			imgHeight,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bytes

		);
	else if (numColorChannels == 3)
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			imgWidth,
			imgHeight,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			bytes

		);
	else if (numColorChannels == 1)
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			imgWidth,
			imgHeight,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			bytes

		);
	else {
		throw std::invalid_argument("not valid texture");
	}
	

	glGenerateMipmap(GL_TEXTURE_2D);
	

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_DEPTH_TEST);




}

void Texture::texUnit(Shader shader, const char* uniform, GLuint unit) {

	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);

}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}