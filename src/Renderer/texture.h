#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <string>

namespace Renderer {

typedef unsigned int uint;
class Texture
{
	typedef unsigned int texture;
private:
	uint m_id;
	texture m_texture;


public:
	Texture(const std::string& texturePath, uint m_id = 0);
	~Texture();

	void use();
};

}

#endif
