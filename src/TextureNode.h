#ifndef TEXTURE_NODE_H
#define TEXTURE_NODE_H

#include "Texture.h"
#include "TextureNodeLink.h"

class TextureNode : public TextureNodeLink
{
public:
	TextureNode();
	void set(
		const char * const _assetName,
		Texture::Name _name,
		GLuint _textureID,
		GLenum _minFilter,
		GLenum _magFilter,
		GLenum _horizWrapMode,
		GLenum _vertWrapMode);

	Texture::Name name;
	GLuint textureID;
	GLenum minFilter;
	GLenum magFilter;
	GLenum horizWrapMode;
	GLenum vertWrapMode;
private:
	char assetName[Texture::ASSET_NAME_SIZE];

};

#endif
