#include "PatientNode.h"
#include<iostream>
#include<cstring>
#pragma warning(disable:4996)
using namespace std;

PatientNode::PatientNode()
{

}

PatientNode::~PatientNode()
{
	delete Name;
	delete Location;
}

char* PatientNode::GetName()
{
	return Name;
}

float PatientNode::GetTemp()
{
	return Temperature;
}

char PatientNode::GetCough()
{
	return Cough;
}

char* PatientNode::GetLoc()
{
	return Location;
}


void PatientNode::SetName(char* name)
{
	Name = new char[strlen(name) + 1];
	strcpy(Name, name);
}

void PatientNode::SetTemp(float temp)
{
	Temperature = temp;
}

void PatientNode::SetCough(char cough)
{
	Cough = cough;
}

void PatientNode::SetLoc(char* location)
{
	Location = new char[strlen(location) + 1];
	strcpy(Location, location);
}
