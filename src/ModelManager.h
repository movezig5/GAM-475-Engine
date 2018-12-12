#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "DLinkList.h"
#include "Model.h"

// Singleton
class ModelManager
{
public:
	static void Add(Model *mObj);
	static void Remove(Model *mObj);
	static Model *GetHead();
	static void DeleteAll();
private:
	ModelManager();
	static ModelManager *privGetInstance();

	DLinkList modelList;
};

#endif
