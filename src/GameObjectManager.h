#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "GameObject.h"
#include "PCSTree.h"

// Singleton
class GameObjectManager
{
public:
	static void Add(GameObject *pObj);
	static void Remove(GameObject *pObj);
	static void RemoveAll();
	static void Draw(void);
	static void Update(float currentTime);
	static GameObject *getFirst();
	static GameObject *getLast();

private:
	GameObjectManager();
	static GameObjectManager *privGetInstance();

	PCSTree *pRootTree;
};

#endif
