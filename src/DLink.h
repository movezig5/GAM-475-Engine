#ifndef DLINK_H
#define DLINK_H

class DLink
{
public:
	DLink();
	virtual ~DLink();
	DLink *getNext();
	DLink *getPrev();
	void setNext(DLink *next);
	void setPrev(DLink *prev);
private:
	DLink *pNext;
	DLink *pPrev;
};

#endif
