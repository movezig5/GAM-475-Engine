#ifndef DLINK_LIST_H
#define DLINK_LIST_H

#include "DLink.h"

class DLinkList
{
public:
	DLinkList();
	DLinkList(const DLinkList &);
	DLinkList &operator=(const DLinkList &);
	~DLinkList();
	void Add(DLink *link);
	void Remove(DLink *link);
	DLink *GetHead();
	void DeleteAll();
private:
	DLink *pHead;
};

#endif
