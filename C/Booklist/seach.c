#include "main.h"

BLink *BookSearch(BLink *Head, int Data)
{
	if(NULL = Head)
	{
		return NULL;
	}
	
	BLink * curr = Head -> next;
	
	while(NULL != curr)
	{
		if(curr->Data == Data)
		return curr;
	
	curr = curr -> next;
	}
	return NULL;
	
}


