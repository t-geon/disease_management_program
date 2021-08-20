#include "LocationNode.h"
#include <cstring>
#pragma warning(disable:4996)

LocationNode::LocationNode()
{
	BST = new PatientBST;
}

LocationNode::~LocationNode()
{
	delete BST;
}

char* LocationNode::GetLoc()
{
	return Location;
}

PatientBST* LocationNode::GetBST()
{
	return BST;
}

LocationNode* LocationNode::GetLeft()
{
	return pLeft;
}

LocationNode* LocationNode::GetRight()
{
	return pRight;
}

void LocationNode::SetLoc(char* location)
{
	Location = new char[strlen(location) + 1];
	strcpy(Location, location);
}

void LocationNode::SetLeft(LocationNode* node)
{
	pLeft = node;
}

void LocationNode::SetRight(LocationNode* node)
{
	pRight = node;
}
