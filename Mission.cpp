#include "Mission.hpp"

Mission::Mission(int id, long long startTime, long long endTime, int reward)
{
    if (endTime < startTime || reward < 0)
        throw runtime_error("INVALID_ARGUMENTS");
    missionId = id;
    startTimestamp = startTime;
    endTimestamp = endTime;
    rewardAmount = reward;
}

void Mission::recordRidePrintInfo()
{
    cout << endl
         << "mission: " << missionId << endl
         << "start timestamp: " << startTimestamp << endl
         << "end timestamp: " << endTimestamp << endl
         << "reward: " << rewardAmount << endl;
}

void Mission::showStatusPrintInfo()
{
    cout << "mission " << missionId << ":" << endl
         << "start timestamp: " << startTimestamp << endl;
    if (status == ON_GOING)
        cout << "end timestamp: " << DEFAULT_END_TIMESTAMP << endl;
    else
        cout << "end timestamp: " << endTimestamp << endl;
    cout << "reward: " << rewardAmount << endl
         << "status: " << status << endl;
}

void Mission::setStatus(string stat)
{
    status = stat;
}

bool Mission::isRideTimeValid(long long startTime, long long endTime)
{
    return startTime >= startTimestamp && endTime <= endTimestamp;
}
