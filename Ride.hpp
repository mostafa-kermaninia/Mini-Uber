#pragma once
#include <iostream>
using namespace std;

class Ride
{
private:
    long long startTime;
    long long endTime;
    int driverId;
    int traveledDist;

public:
    Ride(long long startTime, long long endTime, int driverId, int traveledDist);
    int getDriverId() { return driverId; }
    long long getStartTime() { return startTime; }
    long long getEndTime() { return endTime; }
    int gettraveledDis() { return traveledDist; }
};
