
/*
    Copyright 2024 Ron Zusman
*/ 

#include <algorithm>
#include <thread>
#include "ReqHandler.h"


ReqHandler::ReqHandler(std::vector<Request&> requests, ElevatorManager& manager) : manager_(manager){
    std::sort(requests.begin(),requests.end(),[&](Request reqA, Request reqB){
        return reqA.time < reqB.time;
    });

    for (Request request : requests) {
        thread_vector.emplace_back([&](){run(request);});
    }

    for (auto& t: thread_vector){
        t.join();
    }

}


void ReqHandler::run(Request& req){ 
    //  simulate time of request 
    std::this_thread::sleep_for(std::chrono::milliseconds(1000*req.time));
    //  submit the request
    manager_.ProcessRequest(req);
};


