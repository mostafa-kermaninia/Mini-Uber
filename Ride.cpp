#include "Ride.hpp"

Ride::Ride(long long start, long long end, int id, int dist)
{
    if (end < start)
        throw runtime_error("INVALID_ARGUMENTS");
    startTime = start;
    endTime = end;
    driverId = id;
    traveledDist = dist;
}
