#ifndef GRAPHICS_OBJECT_TEXTURE_LIGHT_H
#define GRAPHICS_OBJECT_TEXTURE_LIGHT_H

#include "GraphicsObject.h"
#include "Texture.h"
#include "MathEngine.h"

class GraphicsObject_TextureLight : public GraphicsObject
{
public:
	GraphicsObject_TextureLight(Model *_pModel, ShaderObject *_pShaderObj, Texture::Name _name, Vect &LightColor, Vect &LightPos);
	GraphicsObject_TextureLight() = delete;
	GraphicsObject_TextureLight & operator = (const GraphicsObject_TextureLight &) = delete;
	~GraphicsObject_TextureLight();

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	Texture::Name textName;
	Vect *pLightColor;
	Vect *pLightPos;
};

#endif
