
using namespace std;
#include <iostream>
#include "../Source/Engine/Core/random.h"
#include "../Source/Engine/Core/fileIO.h"
int main() {
	kiko::seedRandom((unsigned int)time(nullptr));
	cout << kiko::getFilePath() << endl;
	kiko::setFilePath("Assets");
	cout << kiko::getFilePath() << endl;
	size_t size;
	kiko::getFileSize("everything.txt", size);
	for (int i = 0; i < 10; i++) {
		cout << kiko::random(10, 20) << endl;
	}
}