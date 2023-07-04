#include "Memory.h"
#include <iostream>

using namespace std;


kiko::MemoryTracker kiko::g_memoryTracker;
void* operator new (size_t size)
{
	void* ptr = malloc(size);
	kiko::g_memoryTracker.Add(ptr, size);
	//cout << "allocated: " << size << endl;

	return ptr;
}

void operator delete (void* address, size_t size)
{
	//cout << "deallocated: " << size << endl;
	kiko::g_memoryTracker.Remove(address, size);
	free(address);
}
namespace kiko {
	void MemoryTracker::Add(void* address, size_t size)
	{
		m_bytesAllocated += size;
		m_numAllocations++;
	}
	void MemoryTracker::Remove(void* address, size_t size)
	{
		m_bytesAllocated -= size;
		m_numAllocations--;
	}
	void MemoryTracker::displayInfo()
	{
		cout << "current bytes allocated: " << m_bytesAllocated << endl;
		cout << "current number allocated: " << m_numAllocations << endl;
	}
}