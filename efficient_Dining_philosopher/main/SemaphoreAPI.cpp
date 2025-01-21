#include "SemaphoreAPI.h"
#include <WinBase.h>
SemaphoreAPI::SemaphoreAPI(int init_count, int max_count)
{
	hSemaphore = CreateSemaphoreA(
		NULL,
		init_count,           // Initial count
		max_count,            // Max count                                  
		NULL);
}
SemaphoreAPI::~SemaphoreAPI()
{
	if (hSemaphore != NULL)
		CloseHandle(hSemaphore);;
}
void SemaphoreAPI::wait()
{
	DWORD status;
	if (hSemaphore != NULL)
		status = WaitForSingleObject(hSemaphore, INFINITE);
	Sleep(5);
}

void SemaphoreAPI::signal()
{
	if (hSemaphore != NULL)
		ReleaseSemaphore(hSemaphore, 1, NULL);
}
