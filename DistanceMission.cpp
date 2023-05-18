#include "DistanceMission.hpp"

DistanceMission::DistanceMission(int id, long long startTime, long long endTime, int targetDist, int reward)
    : Mission(id, startTime, endTime, reward)
{
    if (targetDist < 0)
        throw runtime_error("INVALID_ARGUMENTS");
    targetDistanceInMeters = targetDist;
    goneDist = 0;
}

void DistanceMission::updateDistToTarget(Ride *ride)
{
    if (isRideTimeValid(ride->getStartTime(), ride->getEndTime()))
        goneDist += ride->gettraveledDis();
}

bool DistanceMission::isEnd()
{
    return goneDist >= targetDistanceInMeters;
}
