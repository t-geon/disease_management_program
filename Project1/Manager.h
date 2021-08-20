#pragma once
#include "PatientNode.h"
#include "LocationBST.h"
#include "LocationHeap.h"

class Manager
{
private:
	queue <PatientNode*>* ds_queue;
	LocationBST* ds_bst;
	LocationHeap* ds_heap;
	ifstream fin;
	ofstream flog;
	int ln;
public:
	Manager();
	~Manager();

	void run(const char* command);
	bool LOAD();
	bool ADD(char* patient);
	bool QPOP(int n);
	bool SEARCH(char* r);
	bool PRINT(char* tt);
	bool BPOP(char* name);

	void PrintErrorCode(int num);
	void PrintSuccess(char* act);
};