#include <assert.h>

#include "Model.h"
#include "GraphicsObject_Wireframe.h"
#include "ShaderObject.h"

#include "Camera.h"
#include "CameraManager.h"

GraphicsObject_Wireframe::GraphicsObject_Wireframe(Model *_pModel, ShaderObject *_pShaderObj)
	: GraphicsObject(_pModel, _pShaderObj)
{
	assert(pModel);
	assert(pShaderObj);
	assert(pWorld);
}

void GraphicsObject_Wireframe::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_Wireframe::SetDataGPU()
{
	// Use this shader
	this->pShaderObj->SetActive();

	// Set the VAO
	glBindVertexArray(this->GetModel()->vao);

	// Set state
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

	Camera *pCam = CameraManager::getActiveCam();
	Matrix world = this->GetWorld();
	Matrix view = pCam->getViewMatrix();
	Matrix proj = pCam->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);
}

void GraphicsObject_Wireframe::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_Wireframe::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
