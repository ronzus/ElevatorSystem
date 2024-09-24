#pragma once
#include <Request.h>
#include <Elevator.h>
#include <string>
#include <iostream>
#include <list>

using namespace std;
enum Algorithm{ //Look into dynamic sched and moving in not stright dir (final final)
    FCFS,
    SSTF,
    SCAN,
    LOOK,
    CSCAN,
    CLOOK 
};
class ElevatorManager{
    private:
            const Algorithm ALGO;
            list<Elevator> elevators;
            


    public:
        //TODO Rule of 5
        ElevatorManager(Algorithm schedAlgorithm);

        bool ProcessRequest(Request elevRequest);



        
}; // class Elevator