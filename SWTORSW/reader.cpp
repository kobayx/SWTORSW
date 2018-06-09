#include "reader.h"
#include <cctype>
#include <sstream>


Reader::Reader(std::string filename)
{
	fin.open(filename);
	galaxy = new Galaxy();
	constraints = new Travel_Times();
}

Reader::~Reader()
{
	fin.close();
	delete galaxy;
	delete constraints;
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
			if (galaxy->planets[i]->name == item.second->name) {
				for( auto itm : item.first)
					galaxy->planets[i]->add(itm.second);
			}
		}
	}
	return galaxy;
}

bool Reader::get_record()
{
	if (fin.eof())
		return false;

	char c[256] = { 0 };
	char peeker;
	std::map<const Planet*, Edge*> innerTime;
	Edge* edge_;
	Leg leg_;
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
		//	if (planets.find(current_input_line) == planets.end()) {
				Planet* newPlanet = new Planet(current_input_line);
				planets.insert(std::pair<std::string, Planet*>(current_input_line, newPlanet));
		//	}
			departure_planet = planets[current_input_line];
			//departure_planet = newPlanet;
		} else if (i == 2) {
			departure_time = std::stoi(current_input_line);
		} else if (i == 3) {
		//	if (planets.find(current_input_line) == planets.end()) {
				Planet* newPlanet2 = new Planet(current_input_line);
				planets.insert(std::pair<std::string, Planet*>(current_input_line, newPlanet2));
			//}
			destination_planet = planets[current_input_line];
		//	destination_planet = newPlanet2;
			
		} else if (i == 4) {
			arrival_time = std::stoi(current_input_line);
		}
	}
	leg_.departure_time = departure_time;
	leg_.arrival_time = arrival_time;
	leg_.id = ship_id;
	edge_ = new Edge(destination_planet);
	edge_->add(leg_);
	innerTime.insert(std::pair<const Planet*, Edge*>(destination_planet, edge_));
	edges.insert(std::pair<std::map<const Planet*, Edge*>, const Planet*>(innerTime, departure_planet));

	return true;
}

bool Reader::validate()
{
	Travel_Times times_;
	fin.open("conduits.txt");
	char c[256];
	std::string str;

	// checks to see if the planets match
	while (!fin.eof()) {
		fin.getline(c, 256, '\n');
		std::stringstream ss(c);
			for (int i = 0; i < 2; i++) {
				std::getline(ss, str, '\t');
				if (planets.find(str) == planets.end())
						return false;
				return true;
			}
	}
	return false;
}