
/*
    Copyright 2024 Ron Zusman
*/ 

#pragma once

#include "../include/Elevator.h"
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <thread>


class ElevatorManager{
 private:
    Algorithm algo_;
    std::vector<Elevator*> elevators;
    std::vector<std::thread> elevthreads;
    std::deque<Request*> requests;

 public:
    ElevatorManager(){};
    ElevatorManager(Algorithm schedAlgorithm, int nelev, std::vector<int> startingFloors, int numOfFloors);
    void initElevators(int numofelevators, std::vector<int> startingFloors, int numOfFloors);
    bool ProcessRequest(Request& elevRequest);
    void ManageElevators();
    void addRequest(Request* elevRequest);
    void endSequence();
};  // class Elevator


