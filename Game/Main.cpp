
using namespace std;
#include <iostream>
#include "../Source/Engine/Core/random.h"
#include "../Source/Engine/Core/fileIO.h"
#include "../Source/Engine/Core/Memory.h"
#include "../Source/Engine/Core/Time.h"
#include "../Source/Engine/Renderer/Renderer.h"


int main() {
	
	kiko::g_memoryTracker.displayInfo();
	int* ptr = new int;
	kiko::g_memoryTracker.displayInfo();
	delete ptr;
	kiko::g_memoryTracker.displayInfo();

	kiko::Time timer;
	for (int i = 0; i < 100000000; i++) {

	}
	cout << timer.GetElapsedSeconds() << endl;


	
	/*auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100000; i++) {

	}
	auto end = std::chrono::high_resolution_clock::now();
	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << endl;*/






	/*kiko::seedRandom((unsigned int)time(nullptr));
	cout << kiko::getFilePath() << endl;
	kiko::setFilePath("Assets");
	cout << kiko::getFilePath() << endl;
	size_t size = 0;
	kiko::getFileSize("everything.txt", size);
	for (int i = 0; i < 10; i++) {
		cout << kiko::random(10, 20) << endl;
	}*/
}