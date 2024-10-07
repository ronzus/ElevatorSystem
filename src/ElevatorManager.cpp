#include "ElevatorManager.h"

ElevatorManager::ElevatorManager(Algorithm algo,int numOfElev) : algo_(algo){
    initElevators(numOfElev);
};

/*
Initializing Elevators access DS
*/

void ElevatorManager::initElevators(int nelev)
{
    for (int i = 0; i < nelev; i++){

        Elevator* newElev = new Elevator(i,0,DIR::UP,0,this->algo_);
        elevators.push_back(newElev);
        thread threadObj(&Elevator::run,*newElev);
        elevthreads.push_back(threadObj);
    }

};

bool ElevatorManager::ProcessRequest(Request req){

    

};