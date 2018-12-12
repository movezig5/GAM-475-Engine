#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "Camera.h"

// Singleton
class CameraManager
{
public:
	static void Add(Camera *pCam);
	static void Remove(Camera *pCam);
	static void RemoveAll();
	static void Update();
	static Camera *getActiveCam();
	static Camera *getFirst();
	static void setActiveCam(Camera *pCam);
	static void next();
	static void prev();

private:
	CameraManager();
	static CameraManager *privGetInstance();

	Camera *pHead;
	Camera *pTail;
	Camera *pActiveCam;
};

#endif
