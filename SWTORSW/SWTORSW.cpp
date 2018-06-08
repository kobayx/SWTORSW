#include <iostream>
#include "priority.h"
#include "galaxy.h"
#include "reader.h"
#include <fstream>

using namespace std;

int main() {

	Reader red("routes.txt");
	red.load();
	return 0;
}