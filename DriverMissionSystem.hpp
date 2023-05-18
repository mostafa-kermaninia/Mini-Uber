#pragma once
#include <iostream>
#include "TimeMission.hpp"
#include "DistanceMission.hpp"
#include "CountMission.hpp"
#include "Driver.hpp"
#include "Ride.hpp"
using namespace std;

class DriverMissionSystem
{
private:
    vector<Driver *> drivers;
    vector<Mission *> missions;
    vector<Ride *> rides;

    void addTimeMission(int missionId, long long startTimestamp,
                        long long endTimestamp, int targetTimeInMinutes, int rewardAmount);
    void addDistanceMission(int missionId, long long startTimestamp,
                            long long endTimestamp, int targetDistanceInMeters, int rewardAmount);
    void addCountMission(int missionId, long long startTimestamp,
                         long long endTimestamp, int targetNumber, int rewardAmount);
    void assignMission(int missionId, int driverId);
    void recordRide(long long startTimestamp, long long endTimestamp, int driverId, int distance);
    void showMissionsStatus(int driverId);
    void invalidCommand();

    bool isDuplicatedMission(int newMissionId);
    Driver *findDriverById(int id);
    Mission *findMissionById(int id);
    vector<Ride *> findRidesByDriverId(int driverId);
    long long findLastRideTime(vector<Ride *> rides);

public:
    DriverMissionSystem();
    ~DriverMissionSystem();

    void handle_commands();
};
