#include "MathEngine.h"
#include "GameObject.h"
#include "Game.h"

extern Game *pGame;

GameObject::GameObject(GraphicsObject *_pGraphicsObj)
	: pGraphicsObj(_pGraphicsObj)
{
	this->pWorld = new Matrix(Matrix::SpecialType::Identity);
	this->pTrans = new Vect(0.0f, 0.0f, 0.0f);
	this->pScale = new Vect(1.0f, 1.0f, 1.0f);
	this->pAxis = new Vect(0.0f, 0.0f, 0.0f);
	this->angle = 0.0f;
	this->deltaRot = 0.0f;
	assert(pWorld);
	assert(pTrans);
	assert(pScale);
	assert(_pGraphicsObj != 0);
}

GameObject::~GameObject()
{
	delete this->pWorld;
}

Matrix *GameObject::GetWorld()
{
	return this->pWorld;
}

GraphicsObject *GameObject::GetGraphicsObject()
{
	return this->pGraphicsObj;
}

void GameObject::SetWorld(Matrix *_pWorld)
{
	assert(_pWorld);
	*this->pWorld = *_pWorld;
}

void GameObject::SetPos(const Vect &pos)
{
	*this->pTrans = pos;
}

void GameObject::SetScale(const Vect &inScale)
{
	*this->pScale = inScale;
}

void GameObject::SetRot(const Vect &axis, float _angle)
{
	*this->pAxis = axis;
	this->angle = _angle;
}

void GameObject::SetDeltaRot(float dRot)
{
	this->deltaRot = dRot;
}

void GameObject::privUpdate(float currentTime)
{
	UNUSED_VAR(currentTime);
	
	Matrix Scale(Matrix::Scale, *this->pScale);
	Matrix TransA(Matrix::Trans, *this->pTrans);
	Matrix Rot(Matrix::Identity);
	this->angle += this->deltaRot;
	Rot.set(*this->pAxis, this->angle);
	*this->pWorld = Scale * Rot * TransA;
}

void GameObject::Update(float currentTime)
{
	// Update the world matrix
	this->privUpdate(currentTime);

	// Push to graphics object
	this->pGraphicsObj->SetWorld(*this->pWorld);
}

void GameObject::Draw()
{
	GraphicsObject *_pGraphicsObj = this->GetGraphicsObject();
	assert(_pGraphicsObj);

	_pGraphicsObj->Render();
}