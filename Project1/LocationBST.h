#pragma once
#include "LocationNode.h"
#include "PatientNode.h"

class LocationBST
{
private:
	LocationNode* Root;

public:
	LocationBST();
	~LocationBST();

	LocationNode* GetRoot();

	void Insert_Location(LocationNode* node);
	bool Insert_Patient(PatientNode* node);

	bool Search(char* name);
	char* Delete(char* name);

	void Print_PRE();
	void Print_IN();
	void Print_POST();
	void Print_LEVEL();

	void preorder(LocationNode* lo);
	void inorder(LocationNode* lo);
	void postorder(LocationNode* lo);
};