#ifndef TEXTURE_H
#define TEXTURE_H

#include "sb7.h"

#include "TextureNodeLink.h"

class Texture
{
public:
	static const unsigned int ASSET_NAME_SIZE = 64;

	enum class Name
	{
		STONES,
		RED_BRICK,
		DUCKWEED,
		ROCKS,
		NOT_INITIALIZED
	};

	Texture(const Texture &) = delete;
	Texture &operator=(const Texture &) = delete;
	~Texture() = default;

	static void Add(const char * const _assetName, const Texture::Name _name);
	static void DeleteAllTextures();
	static GLuint Find(const Texture::Name _name);

private:
	Texture();
	static Texture *privGetInstance();

	// Private helper methods
	void privLoadTexture(const char * const _assetName, GLuint *&textureID);
	bool privLoadTGATexture(const char *szFileName, GLint _minFilter, GLint _magFilter, GLint _horizWrapMode, GLint _vertWrapMode);
	void privAddToFront(TextureNodeLink *node, TextureNodeLink *&head);
	GLbyte *gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

	TextureNodeLink *active;
};

#endif
