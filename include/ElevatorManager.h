#pragma once
#include <Elevator.h>
#include <string>
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

class ElevatorManager{
    private:

            Algorithm algo_;
            vector<Elevator*> elevators;
            vector<thread> elevthreads;
            deque<Request> requests; // update to request ,mby change to map or set 


    public:
        //TODO Rule of 5
        ElevatorManager(Algorithm schedAlgorithm,int nelev);

        void initElevators(int numofelevators);

        bool ProcessRequest(Request elevRequest);

        void ManageElevators();



        
}; // class Elevator