#include "Elevator.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <condition_variable>


// Elevator Algorithms

int Elevator::SCAN()
{
    // change so it goes to the top floor and not the top requested floor

    int targetFloor = 0;

    // Sort the floorsToVisit by request floor
    sort(floorsToVisit.begin(), floorsToVisit.end());

    // TODO - add init for direction depending on which half has more requests.
  

    if (direction_ == DIR::UP)
    {
        // Look for the first request above ot at curr lvl
        auto it = std::find_if(this->floorsToVisit.begin(), this->floorsToVisit.end(), [&](int req)
                               { return req <= this->currlevel_; });

        if (it != floorsToVisit.end())
        {
            // There's a request above the current level
            targetFloor = *it;
        }
        else
        {
            if (currlevel_ < max_floor)
            {
                targetFloor = max_floor;
            }
            else
            {
                direction_ = DIR::DOWN;
                targetFloor = floorsToVisit.back();
            }
        }
    }
    else if (direction_ == DIR::DOWN)
    {

        auto it = std::find_if(floorsToVisit.rbegin(), floorsToVisit.rend(), [&](int req)
                               { return req >= currlevel_; });

        if (it != floorsToVisit.rend())
        {

            targetFloor = *it;
        }
        else
        {
            if (currlevel_ > 0)
            {
                targetFloor = 0;
            }
            else
            {
                direction_ = DIR::UP;
                targetFloor = floorsToVisit.front();
            }
        }
    }
    return targetFloor;
}

int Elevator::CSCAN()
{
    int targetFloor = 0;

    sort(floorsToVisit.begin(), floorsToVisit.end());

    direction_ = DIR::UP;

    auto it = std::find_if(floorsToVisit.begin(), floorsToVisit.end(), [&](int req)
                           { return req <= currlevel_; });

    if (it != floorsToVisit.end())
    {

        targetFloor = *it;
    }
    else
    {
        if (currlevel_ < max_floor)
        {
            targetFloor = max_floor;
        }
        else
        {
            targetFloor = 0;
        }
    }
    return targetFloor;
}

int Elevator::LOOK()
{
    int targetFloor = 0;
    // Sort the floorsToVisit by request floor
    sort(floorsToVisit.begin(), floorsToVisit.end());

    // TODO - add init for direction depending on which half has more requests.

    if (direction_ == DIR::UP)
    {
        // Look for the first request above ot at curr lvl
        auto it = std::find_if(this->floorsToVisit.begin(), this->floorsToVisit.end(), [&](int req)
                               { return req <= this->currlevel_; });

        if (it != floorsToVisit.end())
        {
            // There's a request above the current level
            targetFloor = *it;
        }
        else
        {
            direction_ = DIR::DOWN;
            targetFloor = floorsToVisit.back();
        }
    }
    else if (direction_ == DIR::DOWN)
    {

        auto it = std::find_if(floorsToVisit.rbegin(), floorsToVisit.rend(), [&](int req)
                               { return req >= currlevel_; });

        if (it != floorsToVisit.rend())
        {

            targetFloor = *it;
        }
        else
        {
            direction_ = DIR::UP;
            targetFloor = floorsToVisit.front();
        }
    }
    return targetFloor;
}

int Elevator::CLOOK(){

    int targetFloor = 0;

    sort(floorsToVisit.begin(), floorsToVisit.end());

    direction_ = DIR::UP;

    auto it = std::find_if(floorsToVisit.begin(), floorsToVisit.end(), [&](int req)
                           { return req <= currlevel_; });

    if (it != floorsToVisit.end())
    {
        targetFloor = *it;
    }
    else
    {
        targetFloor = floorsToVisit.front();
    }

    return targetFloor;

}

