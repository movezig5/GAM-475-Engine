#include <assert.h>
#include <math.h>

#include "sb7.h"
#include "Camera.h"

Camera::Camera() {
	this->cameraType = Camera::Type::PERSPECTIVE;
	this->pNext = 0;
	this->pPrev = 0;
}

Camera::Camera(Camera::Type type)
{
	this->cameraType = type;
	this->pNext = 0;
	this->pPrev = 0;
}

Camera::~Camera() {}

void Camera::getHelper(Vect &up, Vect &tar, Vect &pos, Vect &upNorm, Vect &forwardNorm, Vect &pRightNorm)
{
	getPos(pos);
	getTarget(tar);
	getUp(upNorm);
	up = pos + upNorm;
	forwardNorm = tar - pos;
	forwardNorm.norm();

	getRight(pRightNorm);
}

void Camera::setHelper(Vect &up, Vect &tar, Vect &pos)
{
	Vect upVect = up - pos;
	setOrientAndPosition(upVect, tar, pos);
}

void Camera::setPerspective(const float Fovy, const float Aspect, const float NearDist, const float FarDist)
{
	this->aspectRatio = Aspect;
	this->fovy = Fovy;
	this->nearDist = NearDist;
	this->farDist = FarDist;
}

int Camera::getScreenWidth() const
{
	return this->viewport_width;
}

int Camera::getScreenHeight() const
{
	return this->viewport_height;
}

void Camera::setViewport(const int inX, const int inY, const int width, const int height)
{
	this->viewport_x = inX;
	this->viewport_y = inY;
	this->viewport_width = width;
	this->viewport_height = height;

	this->privSetViewState();
}

void Camera::privSetViewState(void)
{
	glViewport(this->viewport_x, this->viewport_y, this->viewport_width, this->viewport_height);
}

void Camera::privCalcPlaneHeightWidth(void)
{
	this->near_height = 2.0f * tanf((this->fovy * MATH_PI / 180.0f) * .5f) * this->nearDist;
	this->near_width = this->near_height * this->aspectRatio;
	this->far_height = 2.0f * tanf((this->fovy * MATH_PI / 180.0f) * .5f) * this->farDist;
	this->far_width = this->far_height * this->aspectRatio;
}

void Camera::privCalcPlaneHeightWidthOrtho(void)
{
	this->near_height = fovy;
	this->near_width = this->near_height * this->aspectRatio;
	this->far_height = this->near_height;
	this->far_width = this->near_width;
}

void Camera::setOrientAndPosition(const Vect &inUp, const Vect &inTarget, const Vect &inPos)
{
	this->vTarget = inTarget;
	
	this->vDir = inPos - inTarget;
	this->vDir.norm();

	this->vRight = inUp.cross(this->vDir);
	this->vRight.norm();

	this->vUp = this->vDir.cross(this->vRight);
	this->vUp.norm();

	this->vPos = inPos;
}

void Camera::privCalcFrustumVerts(void)
{
	this->nearTopLeft = this->vPos - this->vDir * this->nearDist + this->vUp * this->near_height * 0.5f -
		this->vRight * this->near_width * 0.5f;
	this->nearTopRight = this->vPos - this->vDir * this->nearDist + this->vUp * this->near_height * 0.5f +
		this->vRight * this->near_width * 0.5f;
	this->nearBottomLeft = this->vPos - this->vDir * this->nearDist - this->vUp * this->near_height * 0.5f -
		this->vRight * this->near_width * 0.5f;
	this->nearBottomRight = this->vPos - this->vDir * this->nearDist - this->vUp * this->near_height * 0.5f +
		this->vRight * this->near_width * 0.5f;

	this->farTopLeft = this->vPos - this->vDir * this->farDist + this->vUp * this->far_height * 0.5f -
		this->vRight * this->far_width * 0.5f;
	this->farTopRight = this->vPos - this->vDir * this->farDist + this->vUp * this->far_height * 0.5f +
		this->vRight * this->far_width * 0.5f;
	this->farBottomLeft = this->vPos - this->vDir * this->farDist - this->vUp * this->far_height * 0.5f -
		this->vRight * this->far_width * 0.5f;
	this->farBottomRight = this->vPos - this->vDir * this->farDist - this->vUp * this->far_height * 0.5f +
		this->vRight * this->far_width * 0.5f;
}

void Camera::privCalcFrustumCollisionNormals(void)
{
	// Normals of the frustum around nearTopLeft
	Vect A = this->nearBottomLeft - this->nearTopLeft;
	Vect B = this->nearTopRight - this->nearTopLeft;
	Vect C = this->farTopLeft - this->nearTopLeft;

	this->frontNorm = A.cross(B);
	this->frontNorm.norm();

	this->leftNorm = C.cross(A);
	this->leftNorm.norm();

	this->topNorm = B.cross(C);
	this->topNorm.norm();

	// Normals of the frustum around farBottomRight
	A = this->farBottomLeft - this->farBottomRight;
	B = this->farTopRight - this->farBottomRight;
	C = this->nearBottomRight - this->farBottomRight;

	this->backNorm = A.cross(B);
	this->backNorm.norm();
	
	this->rightNorm = B.cross(C);
	this->rightNorm.norm();

	this->bottomNorm = C.cross(A);
	this->bottomNorm.norm();
}

void Camera::privUpdateProjMatrix(void)
{
	this->projMatrix[m0] = 2.0f * this->nearDist / this->near_width;
	this->projMatrix[m1] = 0.0f;
	this->projMatrix[m2] = 0.0f;
	this->projMatrix[m3] = 0.0f;

	this->projMatrix[m4] = 0.0f;
	this->projMatrix[m5] = 2.0f * this->nearDist / this->near_height;
	this->projMatrix[m6] = 0.0f;
	this->projMatrix[m7] = 0.0f;

	this->projMatrix[m8] = 0.0f;
	this->projMatrix[m9] = 0.0f;
	this->projMatrix[m10] = (this->farDist + this->nearDist) / (this->nearDist - this->farDist);
	this->projMatrix[m11] = -1.0f;

	this->projMatrix[m12] = 0.0f;
	this->projMatrix[m13] = 0.0f;
	this->projMatrix[m14] = (2.0f * this->farDist * this->nearDist) / (this->nearDist - this->farDist);
	this->projMatrix[m15] = 0.0f;
}

void Camera::privUpdateViewMatrix(void)
{
	// This function assumes that your vUp, vRight, and vDir are still unit
	// And perpendicular to each other.
	// view = Rot(orient) * trans(-(eye.basis))

	this->viewMatrix[m0] = this->vRight[x];
	this->viewMatrix[m1] = this->vUp[x];
	this->viewMatrix[m2] = this->vDir[x];
	this->viewMatrix[m3] = 0.0f;

	this->viewMatrix[m4] = this->vRight[y];
	this->viewMatrix[m5] = this->vUp[y];
	this->viewMatrix[m6] = this->vDir[y];
	this->viewMatrix[m7] = 0.0f;

	this->viewMatrix[m8] = this->vRight[z];
	this->viewMatrix[m9] = this->vUp[z];
	this->viewMatrix[m10] = this->vDir[z];
	this->viewMatrix[m11] = 0.0f;

	// Change of basis (dot with the basis vectors)
	this->viewMatrix[m12] = -vPos.dot(vRight);
	this->viewMatrix[m13] = -vPos.dot(vUp);
	this->viewMatrix[m14] = -vPos.dot(vDir);
	this->viewMatrix[m15] = 1.0f;
}

void Camera::privUpdateProjMatrixOrtho(void)
{
	float l = this->nearTopLeft[x];
	float r = this->nearTopRight[x];
	float t = this->nearTopLeft[y];
	float b = this->nearBottomLeft[y];
	this->projMatrix[m0] = 2.0f / (r - l);
	this->projMatrix[m1] = 0.0f;
	this->projMatrix[m2] = 0.0f;
	this->projMatrix[m3] = 0.0f;

	this->projMatrix[m4] = 0.0f;
	this->projMatrix[m5] = 2.0f / (t - b);
	this->projMatrix[m6] = 0.0f;
	this->projMatrix[m7] = 0.0f;

	this->projMatrix[m8] = 0.0f;
	this->projMatrix[m9] = 0.0f;
	this->projMatrix[m10] = 2.0f / (this->nearDist - this->farDist);
	this->projMatrix[m11] = 0.0f;

	this->projMatrix[m12] = (r + l) / (l - r);;
	this->projMatrix[m13] = (t + b) / (b - t);
	this->projMatrix[m14] = (this->farDist + this->nearDist) / (this->nearDist - this->farDist);
	this->projMatrix[m15] = 1.0f;
}

// Update everything (make sure it's consistent)
void Camera::updateCamera(void)
{
	// First find the near height/width, far height/width
	if (this->cameraType == Camera::Type::PERSPECTIVE)
	{
		this->privCalcPlaneHeightWidth();
	}
	else
	{
		this->privCalcPlaneHeightWidthOrtho();
	}

	// Find the frustum physical verts
	this->privCalcFrustumVerts();

	// Find the frustum collision normals
	this->privCalcFrustumCollisionNormals();
	
	// Update the projection matrix
	if (this->cameraType == Camera::Type::PERSPECTIVE)
	{
		this->privUpdateProjMatrix();
	}
	else
	{
		this->privUpdateProjMatrixOrtho();
	}

	// Update the view matrix
	this->privUpdateViewMatrix();
}

Matrix &Camera::getViewMatrix(void)
{
	return this->viewMatrix;
}

Matrix &Camera::getProjMatrix(void)
{
	return this->projMatrix;
}

void Camera::getPos(Vect &outPos) const
{
	outPos = this->vPos;
}

void Camera::getDir(Vect &outDir) const
{
	outDir = this->vDir;
}

void Camera::getUp(Vect &outUp) const
{
	outUp = this->vUp;
}

void Camera::getTarget(Vect &outTarget) const
{
	outTarget = this->vTarget;
}

void Camera::getRight(Vect &outRight) const
{
	outRight = this->vRight;
}

void Camera::getAspectRatio(float &Value) const
{
	Value = this->aspectRatio;
}

void Camera::setAspectRatio(const float Value)
{
	this->aspectRatio = Value;
}

void Camera::getNearDist(float &Value) const
{
	Value = this->nearDist;
}

void Camera::setNearDist(const float Value)
{
	this->nearDist = Value;
}

void Camera::getNearTopLeft(Vect &vOut) const
{
	vOut = this->nearTopLeft;
}

void Camera::getNearTopRight(Vect &vOut) const
{
	vOut = this->nearTopRight;
}

void Camera::getNearBottomLeft(Vect &vOut) const
{
	vOut = this->nearBottomLeft;
}

void Camera::getNearBottomRight(Vect &vOut) const
{
	vOut = this->nearBottomRight;
}

void Camera::getFarTopLeft(Vect &vOut) const
{
	vOut = this->farTopLeft;
}

void Camera::getFarTopRight(Vect &vOut) const
{
	vOut = this->farTopRight;
}

void Camera::getFarBottomLeft(Vect &vOut) const
{
	vOut = this->farBottomLeft;
}

void Camera::getFarBottomRight(Vect &vOut) const
{
	vOut = this->farBottomRight;
}

Camera *Camera::getNext()
{
	return this->pNext;
}

Camera *Camera::getPrev()
{
	return this->pPrev;
}

void Camera::setNext(Camera *inNext)
{
	this->pNext = inNext;
}

void Camera::setPrev(Camera *inPrev)
{
	this->pPrev = inPrev;
}
