#include <assert.h>

#include "sb7.h"
#include "TGA.h"
#include "Texture.h"
#include "TextureNode.h"

Texture::Texture()
{
	this->active = 0;
}

Texture *Texture::privGetInstance()
{
	static Texture texture;
	return &texture;
}

void Texture::Add(const char * const _assetName, const Texture::Name _name)
{
	GLuint textureID;
	GLuint *pTextureID = &textureID;

	// Get the instance to the manager
	Texture *pTexture = Texture::privGetInstance();

	// Load the texture and get the textureID
	pTexture->privLoadTexture(_assetName, pTextureID);

	// Create a TextureNode
	TextureNode *pNode = new TextureNode();

	// Initialize it
	pNode->set(_assetName, _name, textureID, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	// Add it to the manager
	pTexture->privAddToFront(pNode, pTexture->active);
}

GLuint Texture::Find(const Texture::Name _name)
{
	Texture *pTexture = Texture::privGetInstance();

	TextureNode *pNode = (TextureNode *)pTexture->active;
	while (pNode != 0)
	{
		if (pNode->name == _name)
		{
			break;
		}
		pNode = (TextureNode *)pNode->pNext;
	}

	return pNode->textureID;
}

void Texture::DeleteAllTextures()
{
	Texture *pTexture = Texture::privGetInstance();

	TextureNode *pNode = (TextureNode *)pTexture->active;
	while (pNode != 0)
	{
		glDeleteTextures(1, &pNode->textureID);

		pNode = (TextureNode *)pNode->pNext;
	}
}

void Texture::privAddToFront(TextureNodeLink *node, TextureNodeLink *&head)
{
	assert(node != 0);

	if (head == 0)
	{
		head = node;
		node->pNext = 0;
		node->pPrev = 0;
	}
	else
	{
		node->pNext = head;
		head->pPrev = node;
		head = node;
	}
}

void Texture::privLoadTexture(const char * const _assetName, GLuint *&_textureID)
{
	// Get an ID, for textures
	glGenTextures(1, _textureID);

	// Bind it
	glBindTexture(GL_TEXTURE_2D, *_textureID);

	// Load the texture
	this->privLoadTGATexture(_assetName, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

// Load a TGA as a 2D Texture. Completely initialize the state
bool Texture::privLoadTGATexture(const char *szFileName, GLint _minFilter, GLint _magFilter, GLint _horizWrapMode, GLint _vertWrapMode)
{
	GLbyte *pBits;
	int nWidth, nHeight, nComponents;
	GLenum eFormat;

	pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
	if (pBits == NULL)
		return false;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)_horizWrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)_vertWrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)_minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)_magFilter);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

	free(pBits);
	
	if (_minFilter == GL_LINEAR_MIPMAP_LINEAR ||
		_minFilter == GL_LINEAR_MIPMAP_NEAREST ||
		_minFilter == GL_NEAREST_MIPMAP_LINEAR ||
		_minFilter == GL_NEAREST_MIPMAP_NEAREST)
		glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}

// (From Ed Keenan's examples)
////////////////////////////////////////////////////////////////////
// Allocate memory and load targa bits. Returns pointer to new buffer,
// height, and width of texture, and the OpenGL format of data.
// Call free() on buffer when finished!
// This only works on pretty vanilla targas... 8, 24, or 32 bit color
// only, no palettes, no RLE encoding.
GLbyte *Texture::gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE *pFile;				// File pointer
	TGAHEADER tgaHeader;		// TGA file header
	unsigned long lImageSize;	// Size of image in bytes
	short sDepth;				// Pixel depth
	GLbyte *pBits = NULL;		// Pointer to bits

	// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_RGB;
	*iComponents = GL_RGB;

	// Attempt to open the file
	fopen_s(&pFile, szFileName, "rb");
	if (pFile == NULL)
		return NULL;

	// Read in header (binary)
	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);

	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Validity checks
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	// Calculate the size of the image buffer
	lImageSize = (unsigned int)tgaHeader.width * (unsigned int)tgaHeader.height * (unsigned int)sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte *)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error
	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}

	// Set OpenGL format expected
	switch (sDepth)
	{
	case 3:
		*eFormat = GL_BGR;
		*iComponents = GL_RGB;
		break;
	case 4:
		*eFormat = GL_BGRA;
		*iComponents = GL_RGBA;
		break;
	case 1:
		assert(false);
		break;
	default:
		break;
	}

	// Done with file
	fclose(pFile);

	// Return pointer to image data
	return pBits;
}
