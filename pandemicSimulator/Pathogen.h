#pragma once
class Pathogen
{
	double mortalityRate;
	double infectionRate;
	bool immunityAfterInfected;
	int minDaysInfected;
public:
	Pathogen(double new_mortalityRate, double new_infectionRate, bool new_immunityAfterInfected, int new_minDaysInfected);
	Pathogen();
	~Pathogen();
	
	double getMortalityRate();
	double getinfectionRate();
	bool isImmuneAfterRecovery();
	int getMinDaysInfected();
};

