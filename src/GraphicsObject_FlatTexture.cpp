#include <assert.h>

#include "GraphicsObject_FlatTexture.h"
#include "ShaderObject.h"
#include "Texture.h"
#include "Model.h"

#include "Camera.h"
#include "CameraManager.h"

GraphicsObject_FlatTexture::GraphicsObject_FlatTexture(Model *_pModel, ShaderObject *_pShaderObj, Texture::Name _name)
	: GraphicsObject(_pModel, _pShaderObj), textName(_name)
{
	assert(pModel);
	assert(pShaderObj);
	assert(pWorld);
}

void GraphicsObject_FlatTexture::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	GLuint textureID = Texture::Find(this->textName);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_FlatTexture::SetDataGPU()
{
	this->pShaderObj->SetActive();

	glBindVertexArray(this->GetModel()->vao);

	Camera *pCam = CameraManager::getActiveCam();
	Matrix world = this->GetWorld();
	Matrix view = pCam->getViewMatrix();
	Matrix proj = pCam->getProjMatrix();
	
	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);
}

void GraphicsObject_FlatTexture::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_FlatTexture::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}
