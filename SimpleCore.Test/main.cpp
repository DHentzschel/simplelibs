#include <cstdlib>
#include "queuetest.cpp"
#include "vectortest.cpp"
#include "stopwatchtest.cpp"
#include "dirtest.cpp"
#include "filetest.cpp"
#include "inifiletest.cpp"


int main(int argc, char** argv)
{
	VectorTest vectorTest;
	vectorTest.testAll();

	StopwatchTest stopwatchTest;
	stopwatchTest.testAll();

	QueueTest queueTest;
	queueTest.testAll();

	DirTest dirTest;
	dirTest.testAll();

	FileTest fileTest;
	fileTest.testAll();

	IniFileTest iniFileTest;
	iniFileTest.testAll();

	return EXIT_SUCCESS;
}
