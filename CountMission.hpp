#pragma once
#include "Mission.hpp"

class CountMission : public Mission
{
private:
    int targetNumber;
    int ridesCount;

public:
    CountMission(int id, long long startTime, long long endTime, int targetNum, int reward);

    CountMission *clone() const { return new CountMission(*this); }

    void updateDistToTarget(Ride *ride);
    bool isEnd();
};
