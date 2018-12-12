#include <assert.h>

#include "NullModel.h"
#include "GraphicsObject_Null.h"
#include "GameObjectManager.h"
#include "PCSTreeForwardIterator.h"
#include "PCSTreeReverseIterator.h"

void GameObjectManager::Add(GameObject *pObj)
{
	assert(pObj != 0);

	GameObjectManager *pGOM = GameObjectManager::privGetInstance();
	
	PCSNode *pRootNode = pGOM->pRootTree->GetRoot();

	pGOM->pRootTree->Insert(pObj, pRootNode);
}

void GameObjectManager::Remove(GameObject *pObj)
{
	assert(pObj != 0);

	privGetInstance()->pRootTree->Remove(pObj);
}

void GameObjectManager::RemoveAll()
{
	GameObjectManager *pGOM = GameObjectManager::privGetInstance();
	PCSNode *pRootNode = pGOM->pRootTree->GetRoot();
	PCSTreeForwardIterator itr(pRootNode);
	PCSNode *current;
	while (!itr.IsDone())
	{
		current = itr.CurrentItem();
		itr.Next();
		delete current;
	}
}

void GameObjectManager::Update(float currentTime)
{
	GameObjectManager *pGOM = GameObjectManager::privGetInstance();
	assert(pGOM);

	PCSNode *pRootNode = pGOM->pRootTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardItr(pRootNode);
	PCSNode *pNode = pForwardItr.First();

	GameObject *pGameObj = 0;

	while (!pForwardItr.IsDone())
	{
		assert(pNode);
		pGameObj = (GameObject *)pNode;
		pGameObj->Update(currentTime);
		pNode = pForwardItr.Next();
	}
}

void GameObjectManager::Draw()
{
	GameObjectManager *pGOM = GameObjectManager::privGetInstance();
	assert(pGOM);

	PCSNode *pRootNode = pGOM->pRootTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardItr(pRootNode);
	PCSNode *pNode = pForwardItr.First();

	GameObject *pGameObj = 0;

	while (!pForwardItr.IsDone())
	{
		assert(pNode);
		pGameObj = (GameObject *)pNode;
		pGameObj->Draw();
		pNode = pForwardItr.Next();
	}
}

GameObject *GameObjectManager::getFirst()
{
	GameObjectManager *pGOM = privGetInstance();
	if(pGOM->pRootTree->GetRoot()->GetChild() != 0)
		return (GameObject *)pGOM->pRootTree->GetRoot()->GetChild();
	else return 0;
}

GameObject *GameObjectManager::getLast()
{
	GameObjectManager *pGOM = privGetInstance();
	GameObject *root = (GameObject *)pGOM->pRootTree->GetRoot();
	PCSTreeReverseIterator itr(root);
	if (itr.First() != root)
		return (GameObject *)itr.First();
	else
		return 0;
}

GameObjectManager::GameObjectManager()
{
	NullModel *pModel = new NullModel(0);
	ShaderObject *pShader = new ShaderObject(ShaderObject::Name::NULL_SHADER, "nullRender");
	GraphicsObject_Null *pGraphicsObject = new GraphicsObject_Null(pModel, pShader);
	GameObject *pGameRoot = new GameObject(pGraphicsObject);
	pGameRoot->SetName("GameObject_Root");

	this->pRootTree = new PCSTree();
	assert(this->pRootTree);

	this->pRootTree->Insert(pGameRoot, this->pRootTree->GetRoot());
}

GameObjectManager *GameObjectManager::privGetInstance(void)
{
	static GameObjectManager gom;
	return &gom;
}
