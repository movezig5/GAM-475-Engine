#include "DLinkList.h"

DLinkList::DLinkList()
{
	this->pHead = 0;
}

DLinkList::DLinkList(const DLinkList &obj)
{
	this->pHead = obj.pHead;
}

DLinkList &DLinkList::operator=(const DLinkList &rhs)
{
	this->pHead = rhs.pHead;
	return *this;
}

DLinkList::~DLinkList()
{
	DeleteAll();
}

void DLinkList::Add(DLink *link)
{
	link->setNext(pHead);
	if (pHead != 0)
		pHead->setPrev(link);
}

void DLinkList::Remove(DLink *link)
{
	DLink *current = pHead;
	while (current != link && current != 0)
		current = current->getNext();
	if (pHead == link)
	{
		if (link->getNext() != 0)
			link->getNext()->setPrev(link->getPrev());
		if (link->getPrev() != 0)
			link->getPrev()->setNext(link->getNext());
		else
			pHead = link->getNext();

		link->setNext(0);
		link->setPrev(0);
	}
}

DLink *DLinkList::GetHead()
{
	return pHead;
}

void DLinkList::DeleteAll()
{
	if (pHead != 0)
	{
		DLink *current = pHead;
		while (current->getNext() != 0)
		{
			current = current->getNext();
			delete current->getPrev();
		}
		delete current;
	}
}
