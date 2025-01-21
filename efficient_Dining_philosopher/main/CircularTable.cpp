#include "CircularTable.h"
#include <time.h>
#include <wchar.h>
#include <random>
#include "RandomNumberGenerator.h"

int CircularTable::Rice;
SemaphoreAPI* CircularTable::chopstic[MAX_PHILOSOPHER];
SemaphoreAPI* CircularTable::mutex;

CircularTable::CircularTable(int who)
{
	this->who = who;
			
	//Initializing the shared variables once.
	if (mutex == NULL)
	{
		//pound of rice
		Rice = 50;
		mutex = new SemaphoreAPI(1, 1);
		for (int i = 0; i < MAX_PHILOSOPHER; i++)
			chopstic[i] = new SemaphoreAPI(1, 1);
	}
}

CircularTable::~CircularTable()
{
	if(chopstic[0]!=NULL)
	for (int i = 0; i < MAX_PHILOSOPHER; i++)
		if (chopstic[i] != NULL)
			delete chopstic[i];
	if (mutex != NULL)
		delete mutex;
}

//This function implements the critical section that protects the share variable Rice
void CircularTable::Eat(int* state, int new_state)
{
	bool got_rice = false;
	////////////////////////////////////////////////////////////
	//TODO: Add the code that create a critical section that meet
	//the requirements.
	got_rice = MoreRice();
	if (got_rice) {
		Rice--; //getting rice	
	}
	//More than one philosopher is allowed to ConsumeRice in parallel
	if (got_rice) {
		ConsumeRice(state, new_state);
	}
}
bool CircularTable::MoreRice()
{
	return (Rice > 0);
}
void CircularTable::getLeftChopstic()
{
	chopstic[who]->wait();
}
void CircularTable::getRightChopstic()
{
	chopstic[(who + 1) % MAX_PHILOSOPHER];
}
void CircularTable::putLeftChopstic()
{
	chopstic[who]->signal();
}
void CircularTable::putRightChopstic()
{
	chopstic[(who + 1) % MAX_PHILOSOPHER]->signal();
}
void CircularTable::ConsumeRice(int* state, int new_state)
{
	*state = new_state;
	//The time a philosopher takes to eat is stochastic
	//so some philosophers will eat less than others
	Sleep(RandomNumberGenerator::Get());
}
