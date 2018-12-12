#include "ShaderManager.h"

void ShaderManager::Add(ShaderObject *sObj)
{
	privGetInstance()->shaderList.Add(sObj);
}

void ShaderManager::Remove(ShaderObject *sObj)
{
	privGetInstance()->shaderList.Remove(sObj);
}

ShaderObject *ShaderManager::GetHead()
{
	return (ShaderObject *)privGetInstance()->shaderList.GetHead();
}

void ShaderManager::DeleteAll()
{
	privGetInstance()->shaderList.DeleteAll();
}

ShaderManager::ShaderManager()
{
	this->shaderList = DLinkList();
}

ShaderManager *ShaderManager::privGetInstance()
{
	static ShaderManager sm;
	return &sm;
}
