#pragma once
#include "Mission.hpp"
const int MINUTE_SECONDS = 60;

class TimeMission : public Mission
{
private:
    int targetTimeInMinutes;
    int passedTime;

public:
    TimeMission(int id, long long startTime, long long endTime, int targetTime, int reward);
    TimeMission *clone() const { return new TimeMission(*this); };

    bool isEnd();
    void updateDistToTarget(Ride *ride);
};
