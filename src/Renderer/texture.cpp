#include "texture.h"
#include <stb_image.h>
#include <glad/glad.h>

namespace Renderer {

Texture::Texture(const std::string &texturePath)
{
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	int height;
	int widht;
	int chanel;

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLubyte* textureData = stbi_load(texturePath.c_str(), &widht, &height, &chanel, 0);
	if(textureData)
	{
		GLint format = (chanel == 4)? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, widht, height, 0, format, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(textureData);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::use(Texture::TexNum texNum)
{
	glActiveTexture(texNum);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

};
