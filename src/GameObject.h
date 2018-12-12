#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "ShaderObject.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "PCSNode.h"

class GameObject : public PCSNode
{
public:
	GameObject(GraphicsObject *_pGraphicsObj);
	
	GameObject() = delete;
	GameObject(const GameObject &) = delete;
	GameObject &operator=(const GameObject &) = delete;
	virtual ~GameObject();

	void Update(float currentTime);
	void Draw();
	GraphicsObject *GetGraphicsObject();

	Matrix *GetWorld();
	void SetWorld(Matrix *_pWorld);
	void SetPos(const Vect &pos);
	void SetScale(const Vect &scale);
	void SetRot(const Vect &axis, float _angle);
	void SetDeltaRot(float dRot);

protected:
	Matrix *pWorld;
	Vect *pTrans;
private:
	void privUpdate(float currentTime);
	GraphicsObject *pGraphicsObj;
	Vect *pScale;
	Vect *pAxis;
	float angle;
	float deltaRot;
};

#endif