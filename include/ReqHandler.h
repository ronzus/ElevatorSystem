
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
        ElevatorManager& manager_;

 public:
        ReqHandler(std::vector<Request> requests, ElevatorManager& manager);

        void run(Request &req);
};

