#ifndef TEXTURE_NODE_LINK_H
#define TEXTURE_NODE_LINK_H

class TextureNodeLink
{
public:
	TextureNodeLink()
	{
		this->pNext = 0;
		this->pPrev = 0;
	}

	TextureNodeLink *pNext;
	TextureNodeLink *pPrev;
};

#endif
