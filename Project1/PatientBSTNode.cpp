#include "PatientBSTNode.h"
#include <cstring>
#pragma warning(disable:4996)

PatientBSTNode::PatientBSTNode()
{
	Name = new char;
}

PatientBSTNode::~PatientBSTNode()
{
	delete Name;
}

char* PatientBSTNode::GetName()
{
	return Name;
}

char PatientBSTNode::GetDisease()
{
	return Disease;
}

PatientBSTNode* PatientBSTNode::GetLeft()
{
	return pLeft;
}

PatientBSTNode* PatientBSTNode::GetRight()
{
	return pRight;
}

void PatientBSTNode::SetName(char* name)
{
	Name = new char[strlen(name) + 1];
	strcpy(Name, name);
}

void PatientBSTNode::SetDisease(char disease)
{
	Disease = disease;
}

void PatientBSTNode::SetLeft(PatientBSTNode* node)
{
	pLeft = node;
}

void PatientBSTNode::SetRight(PatientBSTNode* node)
{
	pRight = node;
}
