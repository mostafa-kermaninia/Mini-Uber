#include "TimeMission.hpp"

TimeMission::TimeMission(int id, long long startTime, long long endTime, int targetTime, int reward)
    : Mission(id, startTime, endTime, reward)
{
    if (targetTime < 0)
        throw runtime_error("INVALID_ARGUMENTS");
    targetTimeInMinutes = targetTime;
    passedTime = 0;
}

bool TimeMission::isEnd()
{
    long long targetTimeInSec = targetTimeInMinutes * MINUTE_SECONDS;
    return passedTime >= targetTimeInSec;
}

void TimeMission::updateDistToTarget(Ride *ride)
{
    if (isRideTimeValid(ride->getStartTime(), ride->getEndTime()))
        passedTime += (ride->getEndTime() - ride->getStartTime());
}