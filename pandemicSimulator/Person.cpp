#include "stdafx.h"
#include "Person.h"


Person::Person(int new_state) : state(new_state)
{
	immune = false;
}


Person::~Person()
{
}

int Person::getState() { return state; }

void Person::setState(int new_state) { state = new_state; }

int Person::getTimeInfected() { return timeInfected; }

void Person::setTimeInfected(int time) { timeInfected = time; }

bool Person::getImmunity() { return immune; }

void Person::setImmunity(bool new_immune) { immune = new_immune; }



