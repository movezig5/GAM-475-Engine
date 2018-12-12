#ifndef GRAPHICS_OBJECT_WIREFRAME_H
#define GRAPHICS_OBJECT_WIREFRAME_H

#include "GraphicsObject.h"

class GraphicsObject_Wireframe : public GraphicsObject
{
public:
	GraphicsObject_Wireframe(Model *_pModel, ShaderObject *_pShaderObj);

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;
};

#endif
