#include <assert.h>
#include "CameraManager.h"

void CameraManager::Add(Camera *pCam)
{
	assert(pCam);
	CameraManager *pCM = privGetInstance();
	if (pCM->pHead == 0)
	{
		pCM->pTail = pCam;
	}
	pCam->setNext(pCM->pHead);
	if (pCam->getNext() != 0)
		pCam->getNext()->setPrev(pCam);
	pCM->pHead = pCam;
}

void CameraManager::Remove(Camera *pCam)
{
	assert(pCam);
	CameraManager *pCM = privGetInstance();
	Camera *pCurrent = pCM->pHead;
	while (pCurrent->getNext() != 0 && pCurrent != pCam)
	{
		pCurrent = pCurrent->getNext();
	}
	if (pCurrent == pCam)
	{
		if (pCurrent->getNext() != 0)
			pCurrent->getNext()->setPrev(pCurrent->getPrev());
		else
			pCM->pTail = pCurrent->getPrev();

		if (pCurrent->getPrev() != 0)
			pCurrent->getPrev()->setNext(pCurrent->getNext());
		else
			pCM->pHead = pCurrent->getNext();

		pCurrent->setNext(0);
		pCurrent->setPrev(0);
	}
}

void CameraManager::RemoveAll()
{
	Camera *current = privGetInstance()->pHead;
	if (current != 0)
	{
		while (current->getNext() != 0)
		{
			current = current->getNext();
			delete current->getPrev();
		}
		delete current;
	}
}

void CameraManager::next()
{
	CameraManager *pCM = privGetInstance();
	Camera *active = pCM->pActiveCam;
	if (active != 0)
	{
		if (active->getNext() != 0)
			pCM->pActiveCam = active->getNext();
		else
			pCM->pActiveCam = pCM->pHead;
	}
}

void CameraManager::prev()
{
	CameraManager *pCM = privGetInstance();
	Camera *active = pCM->pActiveCam;
	if (active != 0)
	{
		if (active->getPrev() != 0)
			pCM->pActiveCam = active->getPrev();
		else
			pCM->pActiveCam = pCM->pTail;
	}
}

void CameraManager::Update()
{
	CameraManager *pCM = privGetInstance();
	Camera *pCurrent = pCM->pHead;
	if (pCurrent != 0)
	{
		while (pCurrent->getNext() != 0)
		{
			pCurrent->updateCamera();
			pCurrent = pCurrent->getNext();
		}
	}
}

Camera *CameraManager::getActiveCam()
{
	return privGetInstance()->pActiveCam;
}

Camera *CameraManager::getFirst()
{
	return privGetInstance()->pHead;
}

void CameraManager::setActiveCam(Camera *pCam)
{
	assert(pCam);
	privGetInstance()->pActiveCam = pCam;
}

CameraManager::CameraManager()
{
	this->pHead = 0;
	this->pActiveCam = 0;
}

CameraManager *CameraManager::privGetInstance(void)
{
	static CameraManager cm;
	return &cm;
}