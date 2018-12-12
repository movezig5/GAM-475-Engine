#ifndef GAME_H
#define GAME_H

#include <sb7.h>
#include "Engine.h"

class GameObject;

class Game : public Engine
{
public:
	Game(const char * const pWindowName, const int width, const int height);
	virtual void Initialize() override;
	virtual void LoadContent() override;
	virtual void Update(float currentTime) override;
	virtual void Draw() override;
	virtual void UnloadContent() override;
	virtual void ClearBufferFunc() override;

	int buttonHeld;
	int buttonHeld2;
	int buttonHeld3;
	int buttonHeld4;
	int buttonHeld5;
	GameObject *pObj;
	GameObject *pTexObj;
};

#endif