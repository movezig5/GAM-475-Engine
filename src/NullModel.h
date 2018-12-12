#ifndef NULL_MODEL_H
#define NULL_MODEL_H

#include "Model.h"

class NullModel : public Model
{
public:
	NullModel(const char * const modelFileName);
	~NullModel();

	NullModel(const NullModel &) = delete;
	NullModel &operator=(const NullModel &) = delete;

private:
	virtual void privCreateVAO(const char * const modelFileName) override;
};

#endif
