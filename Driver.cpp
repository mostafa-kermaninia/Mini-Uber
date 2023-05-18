#include "Driver.hpp"

Driver::Driver(int Id)
{
    driverId = Id;
}

Driver::~Driver()
{
    for (auto &mission : driverMissions)
        delete mission;
}

void Driver::addNewMission(Mission *newMission)
{
    for (auto mission : driverMissions)
        if (mission->getId() == newMission->getId())
            throw runtime_error("DUPLICATE_DRIVER_MISSION");

    Mission *copiedMission = newMission->clone();
    copiedMission->setStatus(ON_GOING);

    if (driverMissions.size() == 0)
    {
        driverMissions.push_back(copiedMission);
        return;
    }
    if (newMission->getStartTime() > driverMissions[driverMissions.size() - 1]->getStartTime())
    {
        driverMissions.insert(driverMissions.end(), copiedMission);
        return;
    }
    for (int i = 0; i < driverMissions.size(); i++)
        if (newMission->getStartTime() < driverMissions[i]->getStartTime())
        {
            driverMissions.insert(driverMissions.begin() + i, copiedMission);
            return;
        }
}

void Driver::doneMission(Mission *mission)
{
    mission->setStatus(COMPLETED);
}
