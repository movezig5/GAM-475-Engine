#ifndef GRAPHICS_OBJECT_CONST_COLOR_H
#define GRAPHICS_OBJECT_CONST_COLOR_H

#include "GraphicsObject.h"

class GraphicsObject_ConstColor : public GraphicsObject
{
public:
	GraphicsObject_ConstColor(Model *_pModel, ShaderObject *_pShaderObj, Vect &BaseColor, Vect &LightColor, Vect &LightPos);

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	Vect *pBaseColor;
	Vect *pLightColor;
	Vect *pLightPos;
};

#endif
