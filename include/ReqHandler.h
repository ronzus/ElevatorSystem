
/*
    Copyright 2024 Ron Zusman
*/ 

#pragma once

#include "../include/ElevatorManager.h"
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <thread>



class ReqHandler{
 private:
        std::vector<std::thread> thread_vector;
        std::vector<Request>& reqs;
        ElevatorManager& manager_;
        //TODO (add summary function)...
        std::vector<float> seek_time;
        std::vector<float> total_dist;

 public:
        ReqHandler(std::vector<Request>& requests, ElevatorManager& manager);

        void processRequests();

        void run(Request &req);
};

