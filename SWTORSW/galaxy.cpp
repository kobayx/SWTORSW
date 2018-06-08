#include "galaxy.h"

void Itinerary::print(Fleet & fleet, std::ostream & out)
{
}

void Edge::sort()
{
}

void Edge::dump(Galaxy * galaxy)
{
}

Planet * Planet::search(PriorityQueue<Planet, int(*)(Planet*, Planet*)>& queue)
{
	return nullptr;
}

Itinerary * Planet::make_itinerary(Planet * destination)
{
	return nullptr;
}

void Planet::dump(Galaxy * galaxy)
{
}

void Planet::relax_neighbors(PriorityQueue<Planet, int(*)(Planet*, Planet*)>& queue)
{
}

void Galaxy::search()
{
}

void Galaxy::dump()
{
}

void Galaxy::dump_routes(Planet * origin, std::ostream & out)
{
}
