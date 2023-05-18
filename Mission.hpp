#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Ride.hpp"
const string ON_GOING = "ongoing";
const string COMPLETED = "completed";
const int DEFAULT_END_TIMESTAMP = -1;
using namespace std;

class Mission
{
private:
    int missionId;
    long long startTimestamp;
    long long endTimestamp;
    int rewardAmount;
    string status = ON_GOING;

public:
    Mission(int id, long long startTime, long long endTime, int reward);
    virtual bool isEnd() = 0;
    virtual Mission *clone() const = 0;
    virtual void updateDistToTarget(Ride *newRide) = 0;
    int getId() { return missionId; }
    long long getStartTime() { return startTimestamp; }
    void setEndTime(long long endTime) { endTimestamp = endTime; }
    string getStatus() { return status; }
    void recordRidePrintInfo();
    void showStatusPrintInfo();
    void setStatus(string status);
    bool isRideTimeValid(long long startTime, long long endTime);
};