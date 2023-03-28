#include "libUtil/util.h"

int test_mat_part1(int argc, char* argv[]);

using namespace std;
using namespace app;
int main(int argc, char* argv[])
{
	const string logFilename("./log.txt");
	const bool showInConsole = true;
	startLogThread(logFilename, showInConsole);

	test_mat_part1( argc, argv);

	endLogThread();
	return 0;
}

