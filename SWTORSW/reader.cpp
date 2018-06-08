#include "reader.h"
#include <cctype>
#include <sstream>

//typedef int Ship_ID;

Reader::Reader()
{
	fin.open("routes.txt");
	Fleet uss;
	while (get_record()) {}

}

Reader::Reader(std::fstream& in, Travel_Times * constraints, std::string filename)
{
	in.open(filename);
}

Galaxy * Reader::load()
{
	return nullptr;
}

bool Reader::get_record()
{
	if (fin.eof())
		return false;


	std::string g;
	char c[256] = { 0 };
	char d;
	std::map<Planet*, int> innerTime;

	d = fin.peek();
	if (d == '#' || isspace(d))
		fin.ignore(256, '\n');
	
	fin.getline(c, 256, '\n');
	std::stringstream ss(c);

	for (int i = 0; i < 5; i++) {
		std::getline(ss, g, '\t');
		if(i == 0){
			ships.insert(std::pair<std::string,int>(g, ships.size()));
			ship_id = ships.size() - 1;
		} else if (i == 1) {
			Planet * newPlanet = new Planet(g);
			planets.insert(std::pair<std::string, Planet*>(g, newPlanet));
			departure_planet = newPlanet;
		} else if (i == 2) {
			departure_time = std::stoi(g);
		} else if (i == 3) {
			Planet*newPlanet2 = new Planet(g);
			planets.insert(std::pair<std::string, Planet*>(g, newPlanet2));
			destination_planet = newPlanet2;
		} else if (i == 4) {
			arrival_time = std::stoi(g);
		}
	}
	innerTime.insert(std::pair<Planet*, int>(destination_planet, (arrival_time - departure_time)));
	constraints->times.insert(std::pair<Planet*, std::map<Planet*, int>>(departure_planet, innerTime));

	return true;
}

bool Reader::validate()
{
	return false;
}