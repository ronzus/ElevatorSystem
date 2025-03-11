
/*
    Copyright 2024 Ron Zusman
*/

#include "Algorithms.cpp"
#include <thread>
#include <mutex>
#include <algorithm>
#include <condition_variable>

bool end = false;

// Thread/Elevator action.

void Elevator::run()
{

    int targetFloor = -1;
    while (!end)
    {
        // wait for floorsToVisit.
        std::unique_lock<std::mutex> lock(this->ReqsMutex);

        // Wait until floorsToVisit is not empty (condition variable)
        this->cv.wait(lock, [&]
                      {
                          return !this->floorsToVisit.empty(); // Wait until there's a request
                      });

        if (!this->floorsToVisit.empty())
        {
            switch (this->algo)
            {

            case Algorithm::FCFS:
            {
                targetFloor = floorsToVisit.front();
                break;
            }
            case Algorithm::SSTF:
            {
                int closestReq = calculateClosest(); // index
                targetFloor = floorsToVisit[closestReq];
                break;
            }
            case Algorithm::SCAN:
            {
                targetFloor = SCAN();
                break;
            }
            case Algorithm::CSCAN:
            {
                targetFloor = CSCAN();
                break;
            }

            case Algorithm::LOOK:
            {
                targetFloor = LOOK();
                break;
            }
            case Algorithm::CLOOK:
            {
                targetFloor = CLOOK();
                break;
            }
            default:
            {
                break;
            }
            }

            // Move towards the target floor step-by-step
            if (currlevel_ < targetFloor)
            {
                direction_ = DIR::UP;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                moveUP();
                printf("Elevator %d moving up to level %d\n", this->id_, this->currlevel_);
            }

            else if (currlevel_ > targetFloor)
            {
                direction_ = DIR::UP;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                moveDOWN();
                printf("Elevator %d moving down to level %d\n", this->id_, this->currlevel_);
            }

            // When the elevator reaches the target floor
            if (currlevel_ == targetFloor)
            {

                printf("Elevator %d reached target floor %d\n", this->id_, targetFloor);

                floorsToVisit.erase(std::remove(floorsToVisit.begin(), floorsToVisit.end(), targetFloor), floorsToVisit.end());
                // remove exisiting external requests at current floor (due to completion) and add internal requests to queue
                for (Request *req : external_to_request[currlevel_])
                {
                    floorsToVisit.push_back(req->requested_floor);
                    req->status = 0;
                    if (internal_to_request.count(req->requested_floor))
                    {
                        std::vector<Request *> req_vec;
                        req_vec.push_back(req);
                        internal_to_request.insert({req->requested_floor, req_vec});
                    }
                    else
                    {
                        internal_to_request[req->requested_floor].push_back(req);
                    }
                }

                external_to_request.erase(currlevel_);
                // remove exisiting internal requests to current floor (due to completion)
                for (Request *req : internal_to_request[currlevel_])
                {
                    std::unique_lock<std::mutex> lock(req->req_lk);
                    req->status = 1;
                    req->cv_req.notify_all();
                }
                internal_to_request.erase(currlevel_);

                // Simulate opening and closing the door
                if (openDoor())
                {
                    printf("Elevator %d doors opened.\n", this->id_);
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Doors stay open for 2 seconds
                    closeDoor();
                    printf("Elevator %d doors closed.\n", this->id_);
                }
            }
        }
    }
}



// returns the index of the closest request in floorsToVisit.
int Elevator::calculateClosest()
{
    int ret = 0;
    int minDiff = abs(currlevel_ - floorsToVisit.front());

    // fix casting - not recommended (unless you are sure that floorsToVisit.size will always fit within the range of an int).
    for (int i = 0; i < static_cast<int>(floorsToVisit.size()); i++)
    {

        int diff = abs(currlevel_ - floorsToVisit.at(i));

        if (diff < minDiff)
        {

            minDiff = diff;
            ret = i;
        }
    }

    return ret;
}

// Elevator Operations

bool Elevator::moveDOWN()
{

    // basically shouldn't happen ,if this does occur its due to sync error.

    if (this->currlevel_ == 0)
        return false;

    this->currlevel_--;
    return true;
};

bool Elevator::moveUP()
{

    if (this->currlevel_ == max_floor)
        return false;

    this->currlevel_++;
    return true;
};

bool Elevator::openDoor()
{

    if (isDoorOpen_)
    { // consider ignoring this behavior
        return false;
    }

    isDoorOpen_ = true;

    return true;
};

bool Elevator::closeDoor()
{

    if (!isDoorOpen_)
    { // consider ignoring this behavior
        return false;
    }

    isDoorOpen_ = false;

    return true;
}




/*

Getters and Setters

*/
int Elevator::getId()
{

    return this->id_;
}

int Elevator::getCurrLevel()
{

    return this->currlevel_;
}

void Elevator::setCurrLevel(int level)
{ // do I really need this?

    this->currlevel_ = level;
}

DIR Elevator::getDir()
{

    return this->direction_;
}
// change to bool?
void Elevator::setDir(DIR newDir)
{

    this->direction_ = newDir;
}

float Elevator::getLoad()
{

    return this->currLoad_;
}

void Elevator::setLoad(float newLoad)
{

    this->currLoad_ = newLoad;
}

std::deque<int> Elevator::getRequests()
{
    return floorsToVisit;
}

void Elevator::addRequest(Request &req)
{
    std::unique_lock<std::mutex> lock(this->ReqsMutex);
    this->floorsToVisit.push_back(req.entry_floor);
    if (external_to_request.count(req.entry_floor))
    {
        std::vector<Request *> req_vec;
        req_vec.push_back(&req);
        external_to_request.insert({req.entry_floor, req_vec});
    }
    else
    {
        external_to_request[req.entry_floor].push_back(&req);
    }

    this->cv.notify_all();
}

void Elevator::endOperation()
{
    end = true;
}
