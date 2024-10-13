#pragma once

#include <Elevator.h>
#include <ReqHandler.h>
#include <string>
#include <iostream>
#include <vector>
#include <thread>


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


// struct for parsing
struct init_data {
        
    int num_floors;
    int num_elev;
    vector<int> starting_floors;
    vector<Request> requests;
};
