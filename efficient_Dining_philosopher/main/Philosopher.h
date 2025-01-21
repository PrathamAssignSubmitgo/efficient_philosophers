#pragma once
#include "CircularTable.h"
enum eState {
	THINKING,
	HUNGRY,
	WAITING,
	EATING,
	VACATION
};

class Philosopher
{
private:
	int RiceConsume;
	eState v_State;
	int myID;
	CircularTable* Food;
public:
	Philosopher(int id);
	~Philosopher();
	static DWORD WINAPI thread_func(LPVOID lpParam);
	void Run();
	char* getStatus();
	char* StateToString();
	int getRiceConsume();
	bool isVacationing();
};