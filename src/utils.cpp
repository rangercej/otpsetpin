#include <vector>
#include <iostream>

using namespace std;

vector<string> mkArgs (int argc, char **argv)
{
	vector<string> args;

	for (int i = 0; i < argc; i++) {
		args.push_back(argv[i]);
	}

	return args;
}
