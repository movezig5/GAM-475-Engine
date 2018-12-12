#include <assert.h>

#include "GraphicsObject_TextureLight.h"
#include "Model.h"
#include "Texture.h"
#include "Camera.h"
#include "CameraManager.h"
#include "ShaderObject.h"

GraphicsObject_TextureLight::GraphicsObject_TextureLight(Model *_pModel, ShaderObject *_pShaderObj, Texture::Name _name, Vect &LightColor, Vect &LightPos)
	: GraphicsObject(_pModel, _pShaderObj), textName(_name)
{
	this->pLightColor = new Vect(LightColor);
	this->pLightPos = new Vect(LightPos);
}

GraphicsObject_TextureLight::~GraphicsObject_TextureLight()
{
	delete this->pLightColor;
	delete this->pLightPos;
}

void GraphicsObject_TextureLight::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	GLuint textureID = Texture::Find(this->textName);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_TextureLight::SetDataGPU()
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

	Vect light = *this->pLightPos;
	Vect color = *this->pLightColor;
	glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float *)&light);
	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float *)&color);
}

void GraphicsObject_TextureLight::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetModel()->numTris, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_TextureLight::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}