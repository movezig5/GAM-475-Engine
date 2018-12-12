#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "ShaderObject.h"
#include "DLinkList.h"

class ShaderManager
{
public:
	static void Add(ShaderObject *sObj);
	static void Remove(ShaderObject *sObj);
	static ShaderObject *GetHead();
	static void DeleteAll();
private:
	ShaderManager();
	static ShaderManager *privGetInstance();

	DLinkList shaderList;
};

#endif
