#include "DriverMissionSystem.hpp"

DriverMissionSystem::DriverMissionSystem()
{
}
DriverMissionSystem::~DriverMissionSystem()
{
    for (auto &driver : drivers)
        delete driver;
    for (auto &mission : missions)
        delete mission;
    for (auto &ride : rides)
        delete ride;
}

void DriverMissionSystem::handle_commands()
{
    string command;
    int missionId, targetTimeInMinutes, rewardAmount,
        targetDistanceInMeters, targetNumber, driverId, distance;
    long long startTimestamp, endTimestamp;
    while (cin >> command)
    {
        try
        {
            if (command == "add_time_mission")
            {
                cin >> missionId >> startTimestamp >> endTimestamp >> targetTimeInMinutes >> rewardAmount;
                if (cin.fail())
                    throw runtime_error("INVALID_ARGUMENTS");
                addTimeMission(missionId, startTimestamp, endTimestamp, targetTimeInMinutes, rewardAmount);
            }
            else if (command == "add_distance_mission")
            {
                cin >> missionId >> startTimestamp >> endTimestamp >> targetDistanceInMeters >> rewardAmount;
                if (cin.fail())
                    throw runtime_error("INVALID_ARGUMENTS");
                addDistanceMission(missionId, startTimestamp, endTimestamp, targetDistanceInMeters, rewardAmount);
            }
            else if (command == "add_count_mission")
            {
                cin >> missionId >> startTimestamp >> endTimestamp >> targetNumber >> rewardAmount;
                if (cin.fail())
                    throw runtime_error("INVALID_ARGUMENTS");
                addCountMission(missionId, startTimestamp, endTimestamp, targetNumber, rewardAmount);
            }
            else if (command == "assign_mission")
            {
                cin >> missionId >> driverId;
                if (cin.fail())
                    throw runtime_error("INVALID_ARGUMENTS");
                assignMission(missionId, driverId);
            }
            else if (command == "record_ride")
            {
                cin >> startTimestamp >> endTimestamp >> driverId >> distance;
                if (cin.fail())
                    throw runtime_error("INVALID_ARGUMENTS");
                recordRide(startTimestamp, endTimestamp, driverId, distance);
            }
            else if (command == "show_missions_status")
            {
                cin >> driverId;
                if (cin.fail())
                    throw runtime_error("INVALID_ARGUMENTS");
                showMissionsStatus(driverId);
            }
            else
                invalidCommand();
        }
        catch (const std::runtime_error &e)
        {
            cout << e.what() << '\n';
        }
        cin.clear();
    }
}

void DriverMissionSystem::addTimeMission(int missionId, long long startTimestamp, long long endTimestamp, int targetTimeInMinutes, int rewardAmount)
{
    if (isDuplicatedMission(missionId))
        throw runtime_error("DUPLICATE_MISSION_ID");
    missions.push_back(new TimeMission(missionId, startTimestamp, endTimestamp, targetTimeInMinutes, rewardAmount));
    cout << "OK\n";
}
void DriverMissionSystem::addDistanceMission(int missionId, long long startTimestamp, long long endTimestamp, int targetDistanceInMeters, int rewardAmount)
{
    if (isDuplicatedMission(missionId))
        throw runtime_error("DUPLICATE_MISSION_ID");
    missions.push_back(new DistanceMission(missionId, startTimestamp, endTimestamp, targetDistanceInMeters, rewardAmount));
    cout << "OK\n";
}
void DriverMissionSystem::addCountMission(int missionId, long long startTimestamp, long long endTimestamp, int targetNumber, int rewardAmount)
{
    if (isDuplicatedMission(missionId))
        throw runtime_error("DUPLICATE_MISSION_ID");
    missions.push_back(new CountMission(missionId, startTimestamp, endTimestamp, targetNumber, rewardAmount));
    cout << "OK\n";
}
void DriverMissionSystem::assignMission(int missionId, int driverId)
{
    Mission *selectedMission = findMissionById(missionId);
    Driver *selectedDriver;
    try
    {
        selectedDriver = findDriverById(driverId);
    }
    catch (const runtime_error &e)
    {
        selectedDriver = new Driver(driverId);
        drivers.push_back(selectedDriver);
    }
    selectedDriver->addNewMission(selectedMission);
    cout << "OK\n";
}
void DriverMissionSystem::recordRide(long long startTimestamp, long long endTimestamp, int driverId, int distance)
{
    Driver *selectedDriver;
    try
    {
        selectedDriver = findDriverById(driverId);
    }
    catch (const runtime_error &e)
    {
        // DO NOTHING;
    }
    Ride *newRide = new Ride(startTimestamp, endTimestamp, driverId, distance);
    rides.push_back(newRide);

    cout << "completed missions for driver " << driverId << ':';
    bool hasvalidMission = false;
    for (int i = 0; i < selectedDriver->getMissions().size(); i++)
    {
        selectedDriver->getMissions()[i]->updateDistToTarget(newRide);
        if (selectedDriver->getMissions()[i]->isEnd() && selectedDriver->getMissions()[i]->getStatus() == ON_GOING)
        {
            hasvalidMission = true;
            selectedDriver->getMissions()[i]->setEndTime(newRide->getEndTime());
            selectedDriver->getMissions()[i]->recordRidePrintInfo();
            selectedDriver->doneMission(selectedDriver->getMissions()[i]);
        }
    }
    if (!hasvalidMission)
        cout << endl;
}
void DriverMissionSystem::showMissionsStatus(int driverId)
{
    Driver *selectedDriver = findDriverById(driverId);
    cout << "missions status for driver " << driverId << ':' << endl;
    selectedDriver->getMissions()[0]->showStatusPrintInfo();
    for (int i = 1; i < selectedDriver->getMissions().size(); i++)
    {
        cout << endl;
        selectedDriver->getMissions()[i]->showStatusPrintInfo();
    }
}
void DriverMissionSystem::invalidCommand()
{
    throw runtime_error("INVALID COMMAND");
}

bool DriverMissionSystem::isDuplicatedMission(int newMissionId)
{
    for (auto mission : missions)
        if (mission->getId() == newMissionId)
            return true;
    return false;
}
Driver *DriverMissionSystem::findDriverById(int id)
{
    for (auto driver : drivers)
        if (driver->getId() == id)
            return driver;
    throw runtime_error("MISSION_NOT_FOUND");
}
Mission *DriverMissionSystem::findMissionById(int id)
{
    for (auto mission : missions)
        if (mission->getId() == id)
            return mission;
    throw runtime_error("MISSION_NOT_FOUND");
}

vector<Ride *> DriverMissionSystem::findRidesByDriverId(int driverId)
{
    vector<Ride *> result;
    for (auto &ride : rides)
        if (ride->getDriverId() == driverId)
            result.push_back(ride);
    return result;
}

long long DriverMissionSystem::findLastRideTime(vector<Ride *> rides)
{
    long long lastEnd = 0;
    for (auto ride : rides)
        if (ride->getEndTime() > lastEnd)
            lastEnd = ride->getEndTime();
    return lastEnd;
}
