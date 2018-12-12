#ifndef CAMERA_H
#define CAMERA_H

#include "MathEngine.h"

class Camera final : public Align16
{
public:
	enum Type
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

	void getHelper(Vect &up, Vect &tar, Vect &pos, Vect &upNorm, Vect &forwardNorm, Vect &rightNorm);
	void setHelper(Vect &up, Vect &tar, Vect &pos);

	Camera();
	Camera(Type type);
	Camera(const Camera &) = delete;
	Camera &operator=(const Camera &) = delete;
	virtual ~Camera();

	void setPerspective(const float HalfAngle, const float AspectRatio, const float NearDist, const float FarDist);
	void setViewport(const int inX, const int inY, const int width, const int height);
	void setOrientAndPosition(const Vect &Up_vect, const Vect &Target_pt, const Vect &pos_pt);

	void updateCamera(void);

	Matrix &getViewMatrix();
	Matrix &getProjMatrix();

	void getPos(Vect &outPos) const;
	void getDir(Vect &outDir) const;
	void getUp(Vect &outUp) const;
	void getTarget(Vect &outTarget) const;
	void getRight(Vect &outRight) const;

	int getScreenWidth() const;
	int getScreenHeight() const;

	void getAspectRatio(float &Value) const;
	void setAspectRatio(const float Value);

	void getNearDist(float &value) const;
	void setNearDist(const float Value);

	void getNearTopLeft(Vect &vOut) const;
	void getNearTopRight(Vect &vOut) const;
	void getNearBottomLeft(Vect &vOut) const;
	void getNearBottomRight(Vect &vOut) const;

	void getFarTopLeft(Vect &vOut) const;
	void getFarTopRight(Vect &vOut) const;
	void getFarBottomLeft(Vect &vOut) const;
	void getFarBottomRight(Vect &vOut) const;

	Camera *getNext();
	Camera *getPrev();

	void setNext(Camera *inNext);
	void setPrev(Camera *inPrev);

private:
	void privSetViewState(void);
	void privCalcPlaneHeightWidth(void);
	void privCalcPlaneHeightWidthOrtho(void);
	void privCalcFrustumVerts(void);
	void privCalcFrustumCollisionNormals(void);
	void privUpdateProjMatrix(void);
	void privUpdateProjMatrixOrtho(void);
	void privUpdateViewMatrix(void);

	// Data
	// Aligned
	Matrix projMatrix;
	Matrix viewMatrix;

	Vect vUp;
	Vect vDir;
	Vect vRight;
	Vect vPos;

	Vect vTarget;

	Vect nearTopLeft;
	Vect nearTopRight;
	Vect nearBottomLeft;
	Vect nearBottomRight;

	Vect farTopLeft;
	Vect farTopRight;
	Vect farBottomLeft;
	Vect farBottomRight;

	Vect frontNorm;
	Vect backNorm;
	Vect rightNorm;
	Vect leftNorm;
	Vect topNorm;
	Vect bottomNorm;

	Camera *pNext;
	Camera *pPrev;

	Type cameraType;
	char pad0;
	char pad1;
	char pad2;
	char pad4;

	// Unaligned
	float nearDist;
	float farDist;
	float fovy;
	float aspectRatio;

	float near_height;
	float near_width;
	float far_height;
	float far_width;

	int viewport_x;
	int viewport_y;
	int viewport_width;
	int viewport_height;
};

#endif
