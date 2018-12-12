#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Keyboard.h"
#include "Mouse.h"

class InputManager
{
public:
	InputManager(const InputManager &) = delete;
	InputManager &operator=(const InputManager &) = delete;
	~InputManager();

	static void Create();
	static Keyboard *GetKeyboard();
	static Mouse *GetMouse();
private:
	InputManager();

	static InputManager *privInstance();
	static void privCreate();

	static InputManager *pInputMan;
	Keyboard *pKeyboard;
	Mouse *pMouse;
};

#endif