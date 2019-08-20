#include <cstdlib>
#include "aqueuetest.cpp"
#include "vectortest.cpp"
#include "stopwatchtest.cpp"

int main(int argc, char** argv)
{
	VectorTest vectorTest;
	vectorTest.testAll();

	StopwatchTest stopwatchTest;
	stopwatchTest.testAll();

	QueueTest queueTest;
	queueTest.testAll();

	return EXIT_SUCCESS;
}