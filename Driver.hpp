#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "Mission.hpp"
class Driver
{
private:
    int driverId;
    vector<Mission *> driverMissions;

public:
    Driver(int Id);
    ~Driver();

    void addNewMission(Mission *newMission);
    int getId() { return driverId; };
    vector<Mission *> getMissions() { return driverMissions; };
    void doneMission(Mission *mission);
};