#pragma once
class Person
{
	int state; // 0 = Uninfected, 1 = Infected, 2 = Recovered, 3 = Dead, 4 = Immune
	int timeInfected; //set timeInfected when state = 1
	bool immune;

public:
	Person(int new_state);
	~Person();
	int getState();
	void setState(int new_state);
	int getTimeInfected();
	void setTimeInfected(int time);
	bool getImmunity();
	void setImmunity(bool new_immune);
};

