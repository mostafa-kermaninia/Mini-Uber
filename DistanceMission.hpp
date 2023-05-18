#pragma once
#include "Mission.hpp"

class DistanceMission : public Mission
{
private:
    int targetDistanceInMeters;
    int goneDist;

public:
    DistanceMission(int id, long long startTime, long long endTime, int targetDist, int reward);
    DistanceMission *clone() const { return new DistanceMission(*this); }
    
    bool isEnd();
    void updateDistToTarget(Ride *ride);
};
