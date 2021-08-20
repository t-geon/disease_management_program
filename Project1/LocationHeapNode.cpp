#include "LocationHeapNode.h"
#include<cstring>
#pragma warning(disable:4996)

LocationHeapNode::LocationHeapNode()
{
	Count = 0;
}

LocationHeapNode::~LocationHeapNode()
{
	delete Location;
}

int LocationHeapNode::GetCount()
{
	return Count;
}

char* LocationHeapNode::GetLoc()
{
	return Location;
}

void LocationHeapNode::SetCount(int count)
{
	Count += count;
}

void LocationHeapNode::SetLoc(char* location)
{
	Location = new char[strlen(location) + 1];
	strcpy(Location, location);
}
