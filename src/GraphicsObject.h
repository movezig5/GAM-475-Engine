#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "MathEngine.h"
#include "RenderMaterial.h"

class ShaderObject;
class Model;

class GraphicsObject : private RenderMaterial
{
public:
	GraphicsObject(Model *_pModel, ShaderObject *_pShaderObj);
	GraphicsObject() = delete;
	virtual ~GraphicsObject();

	void Render();
	void SetWorld(Matrix &_world);
	void SetModel(Model *_model);
	
	Model *GetModel() const;
	ShaderObject *GetShader() const;
	Matrix &GetWorld();
protected:
	Model *pModel;
	Matrix *pWorld;
	ShaderObject *pShaderObj;
};

#endif
