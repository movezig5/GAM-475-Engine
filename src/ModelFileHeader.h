#ifndef MODEL_FILE_HEADER_H
#define MODEL_FILE_HEADER_H

#include <string.h>

#define OBJECT_NAME_SIZE	32
#define TEXTURE_NAME_SIZE	32

struct ModelFileHeader
{
	// Object name
	char objName[OBJECT_NAME_SIZE];

	// Vertex buffer
	int numVerts;
	DWORD vertBufferOffset;

	// Trilist index
	int numTriList;
	DWORD triListBufferOffset;

	// Texture info
	//char textName[TEXTURE_NAME_SIZE];
	//unsigned int minFilter;
	//unsigned int magFilter;
	//unsigned int horizWrapMode;
	//unsigned int vertWrapMode;

	ModelFileHeader()
	{
		memset(this, 0x0, sizeof(ModelFileHeader));
	}
};

#endif
