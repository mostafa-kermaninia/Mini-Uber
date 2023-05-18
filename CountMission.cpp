#include "CountMission.hpp"

CountMission::CountMission(int id, long long startTime, long long endTime, int targetNum, int reward)
    : Mission(id, startTime, endTime, reward)
{
    if (targetNum < 0)
        throw runtime_error("INVALID_ARGUMENTS");
    targetNumber = targetNum;
    ridesCount = 0;
}

void CountMission::updateDistToTarget(Ride *ride)
{
    if (isRideTimeValid(ride->getStartTime(), ride->getEndTime()))
        ridesCount++;
}

bool CountMission::isEnd()
{
    return ridesCount >= targetNumber;
}
