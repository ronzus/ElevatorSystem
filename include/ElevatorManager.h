#pragma once
#include <Request.h>
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


    public:
        //TODO Rule of 5
        ElevatorManager(Algorithm schedAlgorithm,int nelev);

        void initElevators(int numofelevators);

        bool ProcessRequest(Request elevRequest);



        
}; // class Elevator