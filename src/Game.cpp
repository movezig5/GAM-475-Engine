#include "Framework.h"
#include "MathEngine.h"
#include "Game.h"
#include "GameObject.h"
#include "ShaderObject.h"
#include "CubeModel.h"
#include "PlaneModel.h"
#include "PyramidModel.h"
#include "TriPyramidModel.h"
#include "GraphicsObject.h"
#include "GraphicsObject_ColorByPosition.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_ConstColor.h"
#include "Texture.h"
#include "InputManager.h"
#include "InputTest.h"
#include "Camera.h"
#include "CameraManager.h"
#include "GameObjectManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"

Game::Game(const char * const pWindowName, const int width, const int height)
	: Engine(pWindowName, width, height)
{
	assert(pWindowName);
	this->buttonHeld = 0;
	this->buttonHeld2 = 0;
	this->buttonHeld3 = 0;
	this->buttonHeld4 = 0;
	this->buttonHeld5 = 0;
	this->pObj = 0;
	this->pTexObj = 0;
}

void Game::Initialize()
{
	InputManager::Create();
}

void Game::LoadContent()
{
	// Camera setup
	
	Camera *pCam = new Camera();
	pCam->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
	pCam->setPerspective(50.0f, float(pCam->getScreenWidth()) / float(pCam->getScreenHeight()), 0.10f, 1000.0f);
	pCam->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 1.0f, 4.5f));
	CameraManager::Add(pCam);
	CameraManager::setActiveCam(pCam);

	pCam = new Camera();
	pCam->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
	pCam->setPerspective(50.0f, float(pCam->getScreenWidth()) / float(pCam->getScreenHeight()), 0.10f, 1000.0f);
	pCam->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(-10.0f, 0.0f, 0.0f), Vect(-20.0f, 1.0f, 4.5f));
	CameraManager::Add(pCam);

	pCam = new Camera();
	pCam->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
	pCam->setPerspective(50.0f, float(pCam->getScreenWidth()) / float(pCam->getScreenHeight()), 0.10f, 1000.0f);
	pCam->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(10.0f, 0.0f, 0.0f), Vect(20.0f, 1.0f, 4.5f));
	CameraManager::Add(pCam);

	pCam = CameraManager::getActiveCam();
	pCam->updateCamera();

	// Load the model
	CubeModel *pCubeModel = new CubeModel("cubeModel.azul");
	assert(pCubeModel);
	ModelManager::Add(pCubeModel);
	PlaneModel *pPlaneModel = new PlaneModel("planeModel.azul");
	assert(pPlaneModel);
	ModelManager::Add(pPlaneModel);
	PyramidModel *pPyramidModel = new PyramidModel("pyramidModel.azul");
	assert(pPyramidModel);
	ModelManager::Add(pPyramidModel);
	TriPyramidModel *pTriPyramidModel = new TriPyramidModel("triPyramidModel.azul");
	assert(pTriPyramidModel);
	ModelManager::Add(pTriPyramidModel);

	// Create/Load shader
	ShaderObject *pShaderObject_color = new ShaderObject(ShaderObject::Name::COLOR_LIGHT, "colorRender");
	assert(pShaderObject_color);
	ShaderManager::Add(pShaderObject_color);
	ShaderObject *pShaderObject_texture = new ShaderObject(ShaderObject::Name::TEXTURE_SIMPLE, "textureRender");
	assert(pShaderObject_texture);
	ShaderManager::Add(pShaderObject_texture);
	ShaderObject *pShaderObject_textureLight = new ShaderObject(ShaderObject::Name::TEXTURE_POINT_LIGHT, "texturePointLightDiff");
	assert(pShaderObject_textureLight);
	ShaderManager::Add(pShaderObject_textureLight);
	ShaderObject *pShaderObject_constColor = new ShaderObject(ShaderObject::Name::CONST_COLOR, "constcolorRender");
	assert(pShaderObject_constColor);
	ShaderManager::Add(pShaderObject_constColor);

	// Textures
	Texture::Add("Rocks.tga", Texture::Name::ROCKS);
	Texture::Add("Stone.tga", Texture::Name::STONES);
	Texture::Add("RedBrick.tga", Texture::Name::RED_BRICK);
	Texture::Add("Duckweed.tga", Texture::Name::DUCKWEED);

	// GraphicsObjects
	//GraphicsObject_ColorByPosition *pGraphics_ColorByPosition;
	GraphicsObject_Wireframe *pGraphics_Wireframe;
	GraphicsObject_FlatTexture *pGraphics_FlatTexture;
	GraphicsObject_TextureLight *pGraphics_TextureLight;
	GraphicsObject_ConstColor *pGraphics_ConstColor;

	// GameObjects
	Vect color(1.50f, 1.50f, 1.50f, 1.0f);
	Vect pos(1, 10, 1);

	// Textured objects
	GameObject *pGameObj;
	pGraphics_TextureLight = new GraphicsObject_TextureLight(pPlaneModel, pShaderObject_textureLight, Texture::Name::DUCKWEED, color, pos);
	pGameObj = new GameObject(pGraphics_TextureLight);
	pGameObj->SetPos(Vect(0.0f, -0.25f, 0.0f));
	GameObjectManager::Add(pGameObj);
	
	pGraphics_TextureLight = new GraphicsObject_TextureLight(pCubeModel, pShaderObject_textureLight, Texture::Name::STONES, color, pos);
	this->pTexObj = new GameObject(pGraphics_TextureLight);
	this->pTexObj->SetPos(Vect(0.0f, 0.0f, 0.0f));
	this->pTexObj->SetRot(Vect(0.0f, 1.0f, 0.0f), MATH_PI4);
	this->pTexObj->SetDeltaRot(0.02f);
	GameObjectManager::Add(this->pTexObj);

	pGraphics_TextureLight = new GraphicsObject_TextureLight(pPyramidModel, pShaderObject_textureLight, Texture::Name::RED_BRICK, color, pos);
	pGameObj = new GameObject(pGraphics_TextureLight);
	pGameObj->SetPos(Vect(-1.0f, 0.0f, -1.0f));
	pGameObj->SetRot(Vect(0.0f, 1.0f, 0.0f), MATH_PI4);
	GameObjectManager::Add(pGameObj);

	pGraphics_TextureLight = new GraphicsObject_TextureLight(pTriPyramidModel, pShaderObject_textureLight, Texture::Name::ROCKS, color, pos);
	pGameObj = new GameObject(pGraphics_TextureLight);
	pGameObj->SetPos(Vect(1.0f, 0.0f, -1.0f));
	GameObjectManager::Add(pGameObj);

	// Constant color objects
	Vect base(0.0f, 1.0f, 0.0f, 1.0f);
	pos = Vect(5.0f, 5.0f, 5.0f);
	pGraphics_ConstColor = new GraphicsObject_ConstColor(pPlaneModel, pShaderObject_constColor, base, color, pos);
	pGameObj = new GameObject(pGraphics_ConstColor);
	pGameObj->SetPos(Vect(-20.0f, -0.25f, 0.0f));
	GameObjectManager::Add(pGameObj);

	base[x] = 1.0f;
	base[y] = 0.0f;
	pGraphics_ConstColor = new GraphicsObject_ConstColor(pCubeModel, pShaderObject_constColor, base, color, pos);
	pGameObj = new GameObject(pGraphics_ConstColor);
	pGameObj->SetPos(Vect(-25.0f, 0.0f, 5.0f));
	pGameObj->SetRot(Vect(1.0f, 1.0f, 1.0f), 0.0f);
	pGameObj->SetDeltaRot(0.05f);
	GameObjectManager::Add(pGameObj);

	base[y] = 0.0f;
	base[z] = 1.0f;
	pGraphics_ConstColor = new GraphicsObject_ConstColor(pPyramidModel, pShaderObject_constColor, base, color, pos);
	pGameObj = new GameObject(pGraphics_ConstColor);
	pGameObj->SetPos(Vect(-15.0f, 0.0f, 5.0f));
	GameObjectManager::Add(pGameObj);

	base[x] = 1.0f;
	pGraphics_ConstColor = new GraphicsObject_ConstColor(pTriPyramidModel, pShaderObject_constColor, base, color, pos);
	pGameObj = new GameObject(pGraphics_ConstColor);
	pGameObj->SetPos(Vect(-20.0f, 0.0f, 0.0f));
	pGameObj->SetScale(Vect(2.0f, 2.0f, 2.0f));
	GameObjectManager::Add(pGameObj);

	// Flat textured objects
	pGraphics_FlatTexture = new GraphicsObject_FlatTexture(pPlaneModel, pShaderObject_texture, Texture::Name::DUCKWEED);
	pGameObj = new GameObject(pGraphics_FlatTexture);
	pGameObj->SetPos(Vect(20.0f, -0.25f, 0.0f));
	GameObjectManager::Add(pGameObj);

	pGraphics_FlatTexture = new GraphicsObject_FlatTexture(pCubeModel, pShaderObject_texture, Texture::Name::STONES);
	pGameObj = new GameObject(pGraphics_FlatTexture);
	pGameObj->SetPos(Vect(20.0f, 0.0f, 0.0f));
	pGameObj->SetRot(Vect(0.0f, 1.0f, 0.0f), MATH_PI4);
	pGameObj->SetDeltaRot(0.02f);
	GameObjectManager::Add(pGameObj);

	pGraphics_FlatTexture = new GraphicsObject_FlatTexture(pPyramidModel, pShaderObject_texture, Texture::Name::RED_BRICK);
	pGameObj = new GameObject(pGraphics_FlatTexture);
	pGameObj->SetPos(Vect(19.0f, 0.0f, -1.0f));
	GameObjectManager::Add(pGameObj);

	pGraphics_FlatTexture = new GraphicsObject_FlatTexture(pTriPyramidModel, pShaderObject_texture, Texture::Name::ROCKS);
	pGameObj = new GameObject(pGraphics_FlatTexture);
	pGameObj->SetPos(Vect(21.0f, 0.0f, -1.0f));
	GameObjectManager::Add(pGameObj);

	// Wireframe objects
	pGraphics_Wireframe = new GraphicsObject_Wireframe(pPlaneModel, pShaderObject_color);
	pGameObj = new GameObject(pGraphics_Wireframe);
	pGameObj->SetPos(Vect(0.0f, -0.25f, -20.0f));
	GameObjectManager::Add(pGameObj);

	pGraphics_Wireframe = new GraphicsObject_Wireframe(pCubeModel, pShaderObject_color);
	pGameObj = new GameObject(pGraphics_Wireframe);
	pGameObj->SetPos(Vect(0.0f, 0.0f, -20.0f));
	GameObjectManager::Add(pGameObj);

	pGraphics_Wireframe = new GraphicsObject_Wireframe(pPyramidModel, pShaderObject_color);
	pGameObj = new GameObject(pGraphics_Wireframe);
	pGameObj->SetPos(Vect(-5.0f, 0.0f, -20.0f));
	pGameObj->SetRot(Vect(1.0f, 0.0f, 0.0f), MATH_PI);
	pGameObj->SetDeltaRot(0.04f);
	GameObjectManager::Add(pGameObj);

	pGraphics_Wireframe = new GraphicsObject_Wireframe(pTriPyramidModel, pShaderObject_color);
	pGameObj = new GameObject(pGraphics_Wireframe);
	pGameObj->SetPos(Vect(5.0f, 0.0f, -20.0f));
	GameObjectManager::Add(pGameObj);
}

void Game::Update(float currentTime)
{
	Camera *pCam = CameraManager::getActiveCam();
	// Handle keyboard inputs
	Keyboard *pKey = InputManager::GetKeyboard();

	// Move forward
	if (pKey->GetKeyState(Keyboard::KEY_W))
	{

		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		pos = pos + 0.1f * forwardNorm;
		tar = tar + 0.1f * forwardNorm;
		up = pos + upNorm;

		pCam->setHelper(up, tar, pos);
	}

	// Move backward
	if (pKey->GetKeyState(Keyboard::KEY_S))
	{

		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		pos = pos - 0.1f * forwardNorm;
		tar = tar - 0.1f * forwardNorm;
		up = pos + upNorm;

		pCam->setHelper(up, tar, pos);
	}

	// Turn left
	if (pKey->GetKeyState(Keyboard::KEY_A))
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		tar = tar - 0.1f * rightNorm;

		pCam->setHelper(up, tar, pos);
	}

	// Turn right
	if (pKey->GetKeyState(Keyboard::KEY_D))
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);
		
		tar = tar + 0.1f * rightNorm;

		pCam->setHelper(up, tar, pos);
	}

	// Move up
	if (pKey->GetKeyState(Keyboard::KEY_SPACE))
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		pos = pos + 0.1f * upNorm;
		tar = tar + 0.1f * upNorm;
		up = pos + upNorm;
		
		pCam->setHelper(up, tar, pos);
	}

	// Move down
	if (pKey->GetKeyState(Keyboard::KEY_C))
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		pos = pos - 0.1f * upNorm;
		tar = tar - 0.1f * upNorm;
		up = pos + upNorm;

		pCam->setHelper(up, tar, pos);
	}

	// Look down (inverted controls)
	if(pKey->GetKeyState(Keyboard::KEY_ARROW_UP))
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		Matrix Trans(Matrix::Trans, tar);
		Matrix NegTrans(Matrix::Trans, -tar);
		Matrix Rot;
		Rot.set(rightNorm, 0.05f);
		Matrix M = NegTrans * Rot * Trans;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->setHelper(up, tar, pos);
	}

	// Look up (inverted controls)
	if (pKey->GetKeyState(Keyboard::KEY_ARROW_DOWN))
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		Matrix Trans(Matrix::Trans, tar);
		Matrix NegTrans(Matrix::Trans, -tar);
		Matrix Rot;
		Rot.set(rightNorm, -0.05f);
		Matrix M = NegTrans * Rot * Trans;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->setHelper(up, tar, pos);
	}

	// "Strafe" left
	if (pKey->GetKeyState(Keyboard::KEY_ARROW_LEFT))
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		pos = pos - 0.1f * rightNorm;
		tar = tar - 0.1f * rightNorm;
		up = pos + upNorm;

		pCam->setHelper(up, tar, pos);
	}

	// "Strafe" right
	if (pKey->GetKeyState(Keyboard::KEY_ARROW_RIGHT))
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		pos = pos + 0.1f * rightNorm;
		tar = tar + 0.1f * rightNorm;
		up = pos + upNorm;

		pCam->setHelper(up, tar, pos);
	}

	// Switch cameras - ']' goes to the next camera, '[' goes to the previous one
	bool lBracket = pKey->GetKeyState(Keyboard::KEY_LEFT_BRACKET);
	bool rBracket = pKey->GetKeyState(Keyboard::KEY_RIGHT_BRACKET);
	if (lBracket || rBracket)
	{
		if (!buttonHeld)
		{
			if (lBracket)
			{
				CameraManager::next();
				pCam = CameraManager::getActiveCam();
				buttonHeld = 1;
			}
			if (rBracket)
			{
				CameraManager::prev();
				pCam = CameraManager::getActiveCam();
				buttonHeld = 1;
			}
		}
	}
	else
	{
		buttonHeld = 0;
	}

	// Reset camera
	if (pKey->GetKeyState(Keyboard::KEY_R))
	{
		pCam = CameraManager::getFirst();
		pCam->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
		pCam->setPerspective(50.0f, float(pCam->getScreenWidth()) / float(pCam->getScreenHeight()), 0.10f, 1000.0f);
		pCam->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 1.0f, 4.5f));
		CameraManager::setActiveCam(pCam);
	}

	// Remove and store a game object
	if (pKey->GetKeyState(Keyboard::KEY_MINUS))
	{
		if (!buttonHeld2 && this->pObj == 0)
		{
			this->pObj = GameObjectManager::getLast();
			GameObjectManager::Remove(pObj);
			buttonHeld2 = 1;
		}
	}
	else
	{
		this->buttonHeld2 = 0;
	}

	// Add stored game object back into the game
	//   Objects are removed from the end of the list and added to the front.
	//   This is inefficient, but it means a different object is removed every time.
	if (pKey->GetKeyState(Keyboard::KEY_EQUAL))
	{
		if (this->pObj != 0)
		{
			GameObjectManager::Add(this->pObj);
			this->pObj = 0;
		}
	}

	// Delete the stored game object.
	if (pKey->GetKeyState(Keyboard::KEY_DELETE) && this->pObj != 0)
	{
		delete this->pObj;
		if (this->pTexObj == this->pObj) // Hack, but needed to prevent crashing
			this->pTexObj = 0;
		this->pObj = 0;
	}

	// Remove the current camera
	if (pKey->GetKeyState(Keyboard::KEY_N))
	{
		if (buttonHeld3 == 0)
		{
			Camera *temp = CameraManager::getActiveCam();
			CameraManager::next();
			pCam = CameraManager::getActiveCam();
			if (pCam != temp)
			{
				CameraManager::Remove(temp);
				delete temp;
			}
		}
		buttonHeld3 = 1;
	}
	else
	{
		buttonHeld3 = 0;
	}

	// Add a new camera
	if (pKey->GetKeyState(Keyboard::KEY_M))
	{
		if (buttonHeld4 == 0)
		{
			Camera *pCamera = new Camera();
			pCam = pCamera;
			pCam->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
			pCam->setPerspective(50.0f, float(pCam->getScreenWidth()) / float(pCam->getScreenHeight()), 0.10f, 1000.0f);
			pCam->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 1.0f, 4.5f));
			CameraManager::Add(pCam);
			CameraManager::setActiveCam(pCam);
		}
		buttonHeld4 = 1;
	}
	else
	{
		buttonHeld4 = 0;
	}

	// Add a new orthographic camera
	if (pKey->GetKeyState(Keyboard::KEY_COMMA))
	{
		if (buttonHeld5 == 0)
		{
			Camera *pCamera = new Camera(Camera::ORTHOGRAPHIC);
			pCam = pCamera;
			pCam->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
			pCam->setPerspective(4.0f, float(pCam->getScreenWidth()) / float(pCam->getScreenHeight()), 0.10f, 1000.0f);
			pCam->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 1.0f, 4.5f));
			CameraManager::Add(pCam);
			CameraManager::setActiveCam(pCam);
		}
		buttonHeld5 = 1;
	}
	else
	{
		buttonHeld5 = 0;
	}

	// Change the texture on the first game object
	if (pKey->GetKeyState(Keyboard::KEY_1))
	{
		if (this->pTexObj != 0)
		{
			GraphicsObject_TextureLight * pGO = (GraphicsObject_TextureLight *)this->pTexObj->GetGraphicsObject();
			pGO->textName = Texture::Name::DUCKWEED;
		}
	}
	if (pKey->GetKeyState(Keyboard::KEY_2))
	{
		if (this->pTexObj != 0)
		{
			GraphicsObject_TextureLight * pGO = (GraphicsObject_TextureLight *)this->pTexObj->GetGraphicsObject();
			pGO->textName = Texture::Name::RED_BRICK;
		}
	}
	if (pKey->GetKeyState(Keyboard::KEY_3))
	{
		if (this->pTexObj != 0)
		{
			GraphicsObject_TextureLight * pGO = (GraphicsObject_TextureLight *)this->pTexObj->GetGraphicsObject();
			pGO->textName = Texture::Name::ROCKS;
		}
	}
	if (pKey->GetKeyState(Keyboard::KEY_4))
	{
		if (this->pTexObj != 0)
		{
			GraphicsObject_TextureLight * pGO = (GraphicsObject_TextureLight *)this->pTexObj->GetGraphicsObject();
			pGO->textName = Texture::Name::STONES;
		}
	}

	// Update camera
	pCam->updateCamera();

	// Update game objects
	GameObjectManager::Update(currentTime);
};

void Game::Draw()
{
	GameObjectManager::Draw();
}

void Game::UnloadContent() {
	if (this->pObj != 0)
		delete this->pObj;
	GameObjectManager::RemoveAll();
	ShaderManager::DeleteAll();
	ModelManager::DeleteAll();
	CameraManager::RemoveAll();
}

void Game::ClearBufferFunc()
{
	const GLfloat grey[] = {0.0f, 0.8f, 1.0f, 1.0f };
	const GLfloat one = 1.0f;

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glClearBufferfv(GL_COLOR, 0, grey);
	glClearBufferfv(GL_DEPTH, 0, &one);
}
