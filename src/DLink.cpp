#include "DLink.h"
DLink::DLink()
{
	this->pNext = 0;
	this->pPrev = 0;
}

DLink::~DLink() {}

DLink *DLink::getNext()
{
	return this->pNext;
}

DLink *DLink::getPrev()
{
	return this->pPrev;
}

void DLink::setNext(DLink *next)
{
	this->pNext = next;
}

void DLink::setPrev(DLink *prev)
{
	this->pPrev = prev;
}
