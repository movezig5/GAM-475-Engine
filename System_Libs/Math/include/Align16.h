#ifndef ALIGN_16_H
#define ALIGN_16_H

class Align16
{
public:
	void *operator new(size_t size_s)
	{
		void *p = _aligned_malloc(size_s, 16);
		return p;
	}

	void *operator new[](size_t size_s)
	{
		void *p = _aligned_malloc(size_s, 16);
		return p;
	}

	void operator delete(void *p)
	{
		_aligned_free(p);
	}

	void operator delete[](void *p)
	{
		_aligned_free(p);
	}
};

#endif