#pragma once
#include "stdafx.h"
#include "Population.h"
#include "Person.h"
#include "Pathogen.h"
#include <vector>

class Population{
	std::vector<std::vector<Person>> population;
	Pathogen pathogen;
	int lockdownAfterDays; //A negative number means the population never goes into lockdown

public:
	Population(int x, int y, Pathogen new_pathogen, int new_lockdownAfterDays);
	~Population();

	std::vector<std::vector<Person>> createUninfectedPopulation(int x, int y);
	int randomNumWithinRange(int a, int b);
	void randomStart();
	void infectAdjacent(int time);
	void recoverOrDie(int time);
	bool chanceProcessor(double chance);
	int counter(int ref);

};

