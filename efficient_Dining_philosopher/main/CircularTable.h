#pragma once
#include "SemaphoreAPI.h"
#include <windows.h>
#define MAX_PHILOSOPHER 5
class CircularTable
{
public:
	CircularTable(int who);
	~CircularTable();
	void Eat(int* state, int new_state);
	static bool MoreRice();
private:
	int who;
	inline bool isEven() { return (who % 2) == 0; }
	
	//declaring the shared variables
	static int Rice;
	static SemaphoreAPI* chopstic[MAX_PHILOSOPHER];
	static SemaphoreAPI* mutex;

	void ConsumeRice(int* state, int new_state);
	void getLeftChopstic();
	void putLeftChopstic();
	void getRightChopstic();
	void putRightChopstic();
};


