#ifndef TRI_PYRAMID_MODEL_H
#define TRI_PYRAMID_MODEL_H

#include "Model.h"

class TriPyramidModel : public Model
{
public:
	TriPyramidModel(const char * const pModelFileName);
	TriPyramidModel() = delete;
	TriPyramidModel(const TriPyramidModel &) = delete;
	TriPyramidModel & operator = (TriPyramidModel &) = delete;
	virtual ~TriPyramidModel();

private:
	virtual void privCreateVAO(const char * const pModelFileName) override;
};

#endif
#pragma once
