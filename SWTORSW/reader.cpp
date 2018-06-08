#include "reader.h"
#include <cctype>
#include <sstream>


Reader::Reader(std::string filename)
{
	fin.open(filename);
	galaxy = new Galaxy();
	constraints = new Travel_Times();
}

Galaxy * Reader::load()
{
	while (get_record()) {}
	for (auto item : planets)
		galaxy->add(item.second);
	for (auto item : ships)
		galaxy->fleet.add(item.first);
	for (unsigned int i = 0; i < galaxy->planets.size(); i++) {
		for (auto item : edges) {
			if (galaxy->planets[i]->name == item.first->name) {
				for( auto itm : item.second)
					galaxy->planets[i]->add(itm.second);
			}
		}
	}
	return nullptr;
}

bool Reader::get_record()
{
	if (fin.eof())
		return false;

	char c[256] = { 0 };
	char peeker;
	std::map<const Planet*, Edge*> innerTime;
	Edge* edg;
	peeker = fin.peek();
	if (peeker == '#' || isspace(peeker))
		fin.ignore(256, '\n');
	
	fin.getline(c, 256, '\n');
	std::stringstream ss(c);

	for (int i = 0; i < 5; i++) {
		std::getline(ss, current_input_line, '\t');
		if(i == 0){
			ships.insert(std::pair<std::string,int>(current_input_line, ships.size()));
			ship_id = ships.size() - 1;
		} else if (i == 1) {
			Planet * newPlanet = new Planet(current_input_line);
			planets.insert(std::pair<std::string, Planet*>(current_input_line, newPlanet));
			departure_planet = newPlanet;
		} else if (i == 2) {
			departure_time = std::stoi(current_input_line);
		} else if (i == 3) {
			Planet*newPlanet2 = new Planet(current_input_line);
			planets.insert(std::pair<std::string, Planet*>(current_input_line, newPlanet2));
			destination_planet = newPlanet2;
		} else if (i == 4) {
			arrival_time = std::stoi(current_input_line);
		}
	}
	edg = new Edge(destination_planet);
	innerTime.insert(std::pair<const Planet*, Edge*>(destination_planet, edg));
	edges.insert(std::pair<const Planet*, std::map<const Planet*, Edge*>>(departure_planet, innerTime));

	return true;
}

bool Reader::validate()
{
	return false;
}