#include <assert.h>
#include "MathEngine.h"
#include "Model.h"
#include "GraphicsObject_ConstColor.h"
#include "Camera.h"
#include "CameraManager.h"
#include "ShaderObject.h"

GraphicsObject_ConstColor::GraphicsObject_ConstColor(Model *_pModel, ShaderObject *_pShaderObj, Vect &BaseColor, Vect &LightColor, Vect &LightPos)
	: GraphicsObject(_pModel, _pShaderObj)
{
	this->pBaseColor = new Vect(BaseColor);
	this->pLightColor = new Vect(LightColor);
	this->pLightPos = new Vect(LightPos);
}

void GraphicsObject_ConstColor::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_ConstColor::SetDataGPU()
{
	glBindVertexArray(this->GetModel()->vao);

	this->pShaderObj->SetActive();

	Camera *pCam = CameraManager::getActiveCam();
	Matrix world = this->GetWorld();
	Matrix view = pCam->getViewMatrix();
	Matrix proj = pCam->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);

	Vect base = *this->pBaseColor;
	Vect light = *this->pLightPos;
	Vect color = *this->pLightColor;
	glUniform4fv(this->pShaderObj->GetLocation("vBaseColor"), 1, (float *)&base);
	glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float *)&light);
	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float *)&color);
}

void GraphicsObject_ConstColor::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_ConstColor::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}
