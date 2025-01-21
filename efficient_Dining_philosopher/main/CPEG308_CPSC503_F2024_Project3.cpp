#include <iostream>
#include "CircularTable.h"
#include "Philosopher.h"

Philosopher* pPhilosopher[MAX_PHILOSOPHER];

void ReportStatus()
{
	for (int i = 0; i < MAX_PHILOSOPHER; i++)
		std::cout << pPhilosopher[i]->getStatus();
	std::cout << "\n";
}

int main()
{
	int id = 0, total = 0;
	
	for (int who = 0; who < MAX_PHILOSOPHER; who++)
	{
		//This will start a separate thread for each philosopher
		//and start thinking and eating rice they all share.
		pPhilosopher[who] = new Philosopher(who);
	}
	while (CircularTable::MoreRice())
	{
		ReportStatus();
		Sleep(1);
	}
	Sleep(100);
	//wait for all threads to finish
	for (int i = 0; i < MAX_PHILOSOPHER; i++)
		pPhilosopher[i]->isVacationing();

	ReportStatus();
	for (int i = 0; i < MAX_PHILOSOPHER; i++)
		total = total + pPhilosopher[i]->getRiceConsume();
	std::cout << "\nTotal Rice Consume = " << total;
}
