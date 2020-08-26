#include "stdafx.h"
#include "Pathogen.h"

Pathogen::Pathogen() {
	//Default constructor
}

Pathogen::Pathogen(double new_mortalityRate, double new_infectionRate, bool new_immunityAfterInfected, int new_minDaysInfected) : 
	infectionRate(new_infectionRate), mortalityRate(new_mortalityRate), immunityAfterInfected(new_immunityAfterInfected), minDaysInfected(new_minDaysInfected)
{
}


Pathogen::~Pathogen()
{
}

double Pathogen::getMortalityRate() { return mortalityRate; }
double Pathogen::getinfectionRate() { return infectionRate; }
bool Pathogen::isImmuneAfterRecovery() { return immunityAfterInfected; }
int Pathogen::getMinDaysInfected() { return minDaysInfected; }
