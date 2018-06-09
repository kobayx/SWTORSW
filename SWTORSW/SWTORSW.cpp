#include <iostream>
#include "priority.h"
#include "galaxy.h"
#include "reader.h"
#include <fstream>

using namespace std;

int main() {
	Reader red("routes.txt");
	Galaxy* Gal(red.load());
	Gal->search();
	return 0;
}