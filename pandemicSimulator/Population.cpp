#include "stdafx.h"
#include "Population.h"
#include "Person.h"
#include "Pathogen.h"
#include <vector>

Population::Population(int x, int y, Pathogen new_pathogen, int new_lockdownAfterDays)
{
	pathogen = new_pathogen;
	new_lockdownAfterDays = lockdownAfterDays;

	//Generates a fully uninfected population
	
//	population.assign(originalPop.begin(), originalPop.end());
	population = createUninfectedPopulation(x,y);
}

Population::~Population()
{
}

std::vector<std::vector<Person>> Population::createUninfectedPopulation(int x, int y) {
	//Creates initial uninfected poulation
	std::vector<Person> row(y, Person(0));
	std::vector<std::vector<Person>> originalPop(x, row);
	return originalPop;
}

int Population::randomNumWithinRange(int a, int b) {
	int n = a + (std::rand() % (b - a + 1));
	return n;
}

void Population::randomStart() {
	//Randomly infects one person

	int i = randomNumWithinRange(0, population.size() - 1);
	int j = randomNumWithinRange(0, population.size() - 1);
	population[i][j].setState(1);
	population[i][j].setTimeInfected(0);
}

void Population::infectAdjacent(int time) {

	//Processes infection
	for (int i = 0; i < population.size(); ++i) {
		for (int j = 0; j < population[i].size(); ++j) {

			//Checks if person is infected
			if (population[i][j].getState() == 1) {

				//Infects above if either unineffected or recovered but person cannot be immune after recover
				if ((i != 0) && (chanceProcessor(pathogen.getinfectionRate()) == true)) {//Checks if not at edge
					if ((population[i - 1][j].getState() == 0) || ((pathogen.isImmuneAfterRecovery() == false) && (population[i - 1][j].getState() == 2))) {
						population[i - 1][j].setState(1);
						population[i - 1][j].setTimeInfected(time);
					}
				}

				//Infects diagonal up and left if either unineffected or recovered but person cannot be immune after recover
				else if (((i != 0) && (j != 0)) && (chanceProcessor(pathogen.getinfectionRate()) == true)) {
					if ((population[i - 1][j - 1].getState() == 0)||((pathogen.isImmuneAfterRecovery()==false)&&(population[i - 1][j - 1].getState() == 2))) {
						population[i - 1][j - 1].setState(1);
						population[i - 1][j - 1].setTimeInfected(time);
					}
				}

				//Infects left if either unineffected or recovered but person cannot be immune after recover
				else if ((j != 0) && (chanceProcessor(pathogen.getinfectionRate()) == true)) {//Checks if not at edge
					if ((population[i][j - 1].getState() == 0) || ((pathogen.isImmuneAfterRecovery() == false) && (population[i][j - 1].getState() == 2))) {
						population[i][j - 1].setState(1);
						population[i][j - 1].setTimeInfected(time);
					}
				}

				//Infects diagonal left and down if either unineffected or recovered but person cannot be immune after recover
				else if (((i != (population.size() - 1)) && (j != 0)) && (chanceProcessor(pathogen.getinfectionRate()) == true)) {
					if ((population[i + 1][j - 1].getState() == 0) || ((pathogen.isImmuneAfterRecovery() == false) && (population[i + 1][j - 1].getState() == 2))) {
						population[i + 1][j - 1].setState(1);
						population[i + 1][j - 1].setTimeInfected(time);
					}
				}

				//Infects below if either unineffected or recovered but person cannot be immune after recover
				else if ((i != (population.size() - 1)) && (chanceProcessor(pathogen.getinfectionRate()) == true)) {//Checks if not at edge
					if ((population[i + 1][j].getState() == 0) || ((pathogen.isImmuneAfterRecovery() == false) && (population[i + 1][j].getState() == 2))) {
						population[i + 1][j].setState(1);
						population[i + 1][j].setTimeInfected(time);
					}
				}

				//Infects diagonal down and right if either unineffected or recovered but person cannot be immune after recover
				else if (((i != (population.size() - 1)) && (j != (population.size() - 1))) && (chanceProcessor(pathogen.getinfectionRate()) == true)) {
					if ((population[i + 1][j + 1].getState() == 0) || ((pathogen.isImmuneAfterRecovery() == false) && (population[i + 1][j + 1].getState() == 2))) {
						population[i + 1][j + 1].setState(1);
						population[i + 1][j + 1].setTimeInfected(time);
					}
				}

				//Infects right if either unineffected or recovered but person cannot be immune after recover
				else if ((j != (population.size() - 1)) && (chanceProcessor(pathogen.getinfectionRate()) == true)) {//Checks if not at edge
					if ((population[i][j + 1].getState() == 0) || ((pathogen.isImmuneAfterRecovery() == false) && (population[i][j +1].getState() == 2))) {
						population[i][j + 1].setState(1);
						population[i][j + 1].setTimeInfected(time);
					}
				}

				//Infects diagonal up and right if either unineffected or recovered but person cannot be immune after recover
				else if ((i != 0) && (j != (population.size() - 1)) && (chanceProcessor(pathogen.getinfectionRate()) == true)) {
					if ((population[i - 1][j + 1].getState() == 0) || ((pathogen.isImmuneAfterRecovery() == false) && (population[i - 1][j + 1].getState() == 2))) {
						population[i - 1][j + 1].setState(1);
						population[i - 1][j + 1].setTimeInfected(time);
					}
				}

			}
		}
	}

}

bool Population::chanceProcessor(double chance) {
	//chance is a percentage * 10 e.g. chance = 23 means 2.3%

	int x = randomNumWithinRange(0, 1000);
	if (x < chance) {
		return true;
	}
	else {
		return false;
	}
}

void Population::recoverOrDie(int time) {

	for (int i = 0; i < population.size(); ++i) {
		for (int j = 0; j < population[i].size(); ++j) {

			//Checks if infected
			if (population[i][j].getState() == 1) {

				//checks the person has been infected for longer than the minimum time
				if (time - population[i][j].getTimeInfected() > pathogen.getMinDaysInfected()) {

					//Half chance a person is no longer infected for each unit of time after minimum time
					if (chanceProcessor(500) == true) {
						if (chanceProcessor(pathogen.getMortalityRate()) == true) {
							//Person dies
							population[i][j].setState(3);
						}
						else {

							//Checks is a person can be immune after recovery
							if (pathogen.isImmuneAfterRecovery() == true) {
								population[i][j].setState(4);
							}
							else {
								population[i][j].setState(2);
							}
						}
					}
				}
			}
		}
	}
}

int Population::counter(int ref) {
	int s = 0;

	for (int i = 0; i<population.size(); ++i) {
		for (int j = 0; j<population[i].size(); ++j) {
			if (population[i][j].getState() == ref) {
				s += 1;
			}
		}
	}

	return s;
}
