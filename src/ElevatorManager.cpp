
/*
    Copyright 2024 Ron Zusman
*/ 

#include "ElevatorManager.h"
#include <algorithm>
#include <mutex>
#include <condition_variable>


std::mutex reqMutex;  
std::condition_variable cv_mng;

ElevatorManager::ElevatorManager(Algorithm algo,int numOfElev,std::vector<int> startingFloors,int numOfFloors) : algo_(algo){
    //initElevators(numOfElev, startingFloors, numOfFloors);
    printf("init Elevs\n");
};

/*
Initializing Elevators access DS
*/

void ElevatorManager::initElevators(int nelev, std::vector<int> startingFloors, int numOfFloors)
{
    for (int i = 0; i < nelev; i++) {

        Elevator* newElev = new Elevator(i, startingFloors[i], DIR::IDLE, 0, this->algo_, numOfFloors); // Review
        elevators.push_back(newElev);

        // Create the thread and move it into the vector
        std::thread threadObj(&Elevator::run, newElev);
        elevthreads.push_back(std::move(threadObj));  
    }

    for (auto& t: elevthreads){
        t.join();
    }
}


void ElevatorManager::ManageElevators() {
    while (1) {
        std::unique_lock<std::mutex> lock(reqMutex);
        cv_mng.wait(lock,[&]{ return !requests.empty(); });
        if (!requests.empty()) {
            Request& newRequest = *requests.front();
            requests.pop_front();

            bool requestProcessed = ProcessRequest(newRequest);

            if (!requestProcessed) {
                std::cout << "No elevator available to handle the request" << std::endl;
            }

        }
       
    }
}


bool ElevatorManager::ProcessRequest(Request& req) {

    for (Elevator* elev : elevators) {
        std::deque<int> temp = elev->getRequests();
        
        // Check if the elevator is passing through the request's entry floor (it is an external request)
        auto it = std::find_if(temp.begin(), temp.end(), [&](int floor) {
            return floor == req.entry_floor;
        });

        // If the elevator has the requested floor in its request queue, assign the new request to it
        if (it != temp.end() || temp.empty()) {
            elev->addRequest(req);
            return true;
        }
        
    }
    //if not found we'll just add it to elev[0]'s queue (temporary)
    elevators[0]->addRequest(req);
    return true;
}

void ElevatorManager::addRequest(Request* req) {
    std::unique_lock<std::mutex> lock(reqMutex);
    this->requests.push_back(req);  
    cv_mng.notify_one();

}

void ElevatorManager::endSequence(){

};