#pragma once
#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <winnt.h>
class SemaphoreAPI
{
private:
	HANDLE hSemaphore;
public:
	SemaphoreAPI(int init_count, int max_count);
	~SemaphoreAPI();
	void wait();
	void signal();
};
