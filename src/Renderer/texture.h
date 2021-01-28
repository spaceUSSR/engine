#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <string>

namespace Renderer {

class Texture
{
	typedef unsigned int texture;
	typedef texture TexNum;
private:
	texture m_texture;


public:
	Texture(const std::string& texturePath);
	~Texture();

	void use(TexNum texNum);
};

}

#endif
