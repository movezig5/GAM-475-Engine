#ifndef PLANE_MODEL_H
#define PLANE_MODEL_H

#include "Model.h"

class PlaneModel : public Model
{
public:
	PlaneModel(const char * const pModelFileName);
	PlaneModel() = delete;
	PlaneModel(const PlaneModel &) = delete;
	PlaneModel & operator = (PlaneModel &) = delete;
	virtual ~PlaneModel();

private:
	virtual void privCreateVAO(const char * const pModelFileName) override;
};

#endif
