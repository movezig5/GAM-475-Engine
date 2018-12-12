#include "ModelManager.h"

void ModelManager::Add(Model *mObj)
{
	privGetInstance()->modelList.Add(mObj);
}

void ModelManager::Remove(Model *mObj)
{
	privGetInstance()->modelList.Remove(mObj);
}

Model * ModelManager::GetHead()
{
	return (Model *)privGetInstance()->modelList.GetHead();
}

void ModelManager::DeleteAll()
{
	privGetInstance()->modelList.DeleteAll();
}

ModelManager::ModelManager()
{
	this->modelList = DLinkList();
}

ModelManager *ModelManager::privGetInstance()
{
	static ModelManager mm;
	return &mm;
}
