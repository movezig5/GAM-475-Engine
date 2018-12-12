#include <sb7.h>
#include <assert.h>

#include "NullModel.h"

NullModel::NullModel(const char * const modelFileName)
	: Model()
{
	UNUSED_VAR(modelFileName);
}

NullModel::~NullModel() {}

void NullModel::privCreateVAO(const char * const modelFileName)
{
	UNUSED_VAR(modelFileName);
}