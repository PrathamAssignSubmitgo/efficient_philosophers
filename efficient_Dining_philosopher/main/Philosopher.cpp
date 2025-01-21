#include "Philosopher.h"
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <time.h>

HANDLE pThread = NULL;
DWORD thread_id = 0;

DWORD WINAPI Philosopher::thread_func(LPVOID lpParam) {
	((Philosopher*)lpParam)->Run();
	return 0;
}
Philosopher::Philosopher(int id)
{
	v_State = VACATION;
	myID = id;
	RiceConsume = 0;
	//All philosophers share a few things at the CircularTable
	Food = new CircularTable(id);
	pThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_func, (LPVOID)this, 0, &thread_id);
}
Philosopher::~Philosopher()
{
	CloseHandle(pThread);
}
void Philosopher::Run()
{
	v_State = EATING;

	while (Food->MoreRice())
	{
		if (v_State == THINKING)
		{
			v_State = HUNGRY;
		}
		else if (v_State == HUNGRY || v_State == WAITING)
		{
			v_State = WAITING;
			Food->Eat((int*)&v_State, (int)EATING);
			if (v_State == EATING) {
				RiceConsume = RiceConsume + 1;
			}
		}
		else if (v_State == EATING)
		{
			v_State = THINKING;
		}
		Sleep(10);
	}
	v_State = VACATION;
}
bool Philosopher::isVacationing()
{
	WaitForSingleObject(pThread, INFINITE);
	return (v_State == VACATION);
}
char* Philosopher::getStatus()
{
	char tmp[64];
	int len = sprintf_s(tmp, "%d %d %s |", myID, RiceConsume, StateToString());
	char* buff = new char[64];
	strcpy_s(buff, 64, (char*)&tmp[0]);
	return (buff);
}
char* Philosopher::StateToString()
{
	if (v_State == THINKING)
		return (char*)("THINKING");
	if (v_State == HUNGRY)
		return (char*)("HUNGRY");
	if (v_State == EATING)
		return (char*)("EATING");
	if (v_State == WAITING)
		return (char*)("WAITING");
	if (v_State == VACATION)
		return (char*)("VACATION");
	return nullptr;
}
int Philosopher::getRiceConsume()
{
	return RiceConsume;
}
