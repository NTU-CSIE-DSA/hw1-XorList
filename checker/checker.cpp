#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerChecker("XORList", argc, argv);
	compareRemainingLines();
}
