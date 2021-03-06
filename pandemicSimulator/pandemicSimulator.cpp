// pandemicSimulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Population.h"
#include "Pathogen.h"

void displayStats(Population pop, int time) {
	std::cout << "Time:\n" << time << "\n"
		<< "\nUnfected: " << pop.counter(0)
		<< "\nInfected: " << pop.counter(1)
		<< "\nRecovered: " << pop.counter(2)
		<< "\nDead: " << pop.counter(3)
		<< "\nImmune: " << pop.counter(4) <<"\n";
}

int main()

	//TODO: Lockdown programming (don't shuffle for set number of days)
{
	int iter = 1000;

	//A pathogen with a 4.6% mortality rate, 25% infection rate, provides no immunity after infection and remains in the body for a minimum of 14 days
	Pathogen pathogen(46, 250, false, 14);
	Population pop(100, 500, pathogen, 30);
	pop.randomStart();
	for (int time = 0; time < iter; ++time) {
		pop.infectAdjacent(time);
		pop.recoverOrDie(time);

		system("cls");
		displayStats(pop, time);
	}

	int x;
	std::cout << "\nPress enter to exit";
	std::cin >> x;
	
    return 0;
}



