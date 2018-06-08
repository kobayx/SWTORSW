#include <iostream>
#include "priority.h"
#include "galaxy.h"
#include "reader.h"

using namespace std;

int main() {
	fstream fin;
	Travel_Times travel;
	Reader red(fin, travel, "routes.txt");
	return 0;
}