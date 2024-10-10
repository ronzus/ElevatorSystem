#include "include/ElevatorManager.h"

ElevatorManager::ElevatorManager(Algorithm algo,int numOfElev) : algo_(algo){
    initElevators(numOfElev);
};

/*
Initializing Elevators access DS
*/

void ElevatorManager::initElevators(int nelev)
{
    for (int i = 0; i < nelev; i++) {

        Elevator* newElev = new Elevator(i, 0, DIR::UP, 0, this->algo_, 0, 5); // Review
        elevators.push_back(newElev);

        // Create the thread and move it into the vector
        thread threadObj(&Elevator::run, *newElev);
        elevthreads.push_back(std::move(threadObj));  // Use std::move here
    }
}

bool ElevatorManager::ProcessRequest(Request req){

    return false;

};