
/*
    Copyright 2024 Ron Zusman
*/ 

#pragma once

#include "../include/Elevator.h"
#include "Request.h"
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
    std::deque<Request> requests;

 public:
    ElevatorManager(){};
    ElevatorManager(Algorithm schedAlgorithm, int nelev);
    void initElevators(int numofelevators);
    bool ProcessRequest(Request elevRequest);
    void ManageElevators();
};  // class Elevator


// struct for parsing
struct init_data {
    int num_floors;
    int num_elev;
    std::vector<int> starting_floors;
    std::vector<Request> requests;
};
