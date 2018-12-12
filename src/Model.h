#ifndef MODEL_H
#define MODEL_H

#include "sb7.h"
#include "MathEngine.h"
#include "DLink.h"

class Model : public DLink
{
public:
	Model();
	Model(Model &copyModel) = delete;
	Model &operator=(Model &copyModel) = delete;
	
	virtual ~Model();

	int numVerts;
	int numTris;

	GLuint vao;
	GLuint vbo[2];
protected:
	virtual void privCreateVAO(const char * const modelFileName) = 0;
private:
};

#endif
