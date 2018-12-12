#include <assert.h>
#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject_ColorByPosition.h"
#include "ShaderObject.h"
#include "CameraManager.h"

#include "Camera.h"

GraphicsObject_ColorByPosition::GraphicsObject_ColorByPosition(Model *_pModel, ShaderObject *_pShaderObj)
	: GraphicsObject(_pModel, _pShaderObj)
{
	assert(pModel);
	assert(pShaderObj);
	assert(pWorld);
}

void GraphicsObject_ColorByPosition::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_ColorByPosition::SetDataGPU()
{
	// Set the VAO
	glBindVertexArray(this->GetModel()->vao);

	// Use this shader
	Camera *pCam = CameraManager::getActiveCam();
	this->pShaderObj->SetActive();
	Matrix world = this->GetWorld();
	Matrix view = pCam->getViewMatrix();
	Matrix proj = pCam->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);
}

void GraphicsObject_ColorByPosition::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_ColorByPosition::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}
