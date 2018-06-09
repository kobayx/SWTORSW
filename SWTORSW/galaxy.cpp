#include "galaxy.h"
#include <algorithm>

void Itinerary::print(Fleet & fleet, std::ostream & out)
{
		//out << fleet.name(legs[0].id) << '\n';
		//out << destinations[0]->name << '\n' << legs[0].departure_time << '\n' << legs[0].arrival_time;
}

void Edge::sort()
{
	std::sort(departures.begin(), departures.end(), Leg::less_than);
}

Planet * Planet::search(PriorityQueue<Planet, int(*)(Planet*, Planet*)>& queue)
{
	Planet *temp = 0;
	temp = queue.pop();
	temp->set_priority(-2);
	temp->best_leg.arrival_time = 0;
	temp->best_leg.departure_time = 0;
	relax_neighbors(queue);
	while (!queue.empty()) {
		temp = queue.pop();
		if (temp->get_priority() == -2)
			break;
		temp->set_priority(-2);
		temp->relax_neighbors(queue);
	}
	return temp;
}

Itinerary * Planet::make_itinerary(Planet * destination)
{
	Planet* temp = destination;
	Itinerary* itinerary = new Itinerary(this);
	while (temp != this) {
		itinerary->destinations.push_back(temp);
		itinerary->legs.push_back(temp->best_leg);
		temp = temp->predecessor;
	}
	return itinerary;
}

void Planet::dump(Galaxy * galaxy)
{
	for (auto item : edges)
		for (auto itm : item->departures)
			std::cerr << itm.arrival_time << std::endl;
}

void Planet::relax_neighbors(PriorityQueue<Planet, int(*)(Planet*, Planet*)>& queue)
{
	for (auto item : edges) {
		if(item->destination->get_priority() != -2)
			queue.push_back(item->destination);
		for (auto itm : item->departures)
			if (itm.arrival_time + arrival_time() < item->destination->arrival_time()) {
				item->destination->best_leg.arrival_time = itm.arrival_time + arrival_time();
				item->destination->best_leg.id = itm.id;
				item->destination->best_leg.departure_time = itm.departure_time;
				item->destination->predecessor = this;
			}
	}
}

void Galaxy::search()
{
	PriorityQueue<Planet, int(*)(Planet*, Planet*)> queue(Planet::compare);
	Planet* temp = 0;
	for (unsigned int i = 0; i < planets.size(); i++) {
		while (!queue.empty())
			queue.pop();
		queue.push_back(planets[i]);
		temp = planets[i]->search(queue);
		Itinerary* itin = planets[i]->make_itinerary(temp);
//		itin->print(fleet);
		reset();
	}
}

void Galaxy::dump()
{
	for (auto item : planets)
		item->dump(this);
}