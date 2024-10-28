
/*
    Copyright 2024 Ron Zusman
*/ 

#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ReqHandler.h"


ReqHandler::ReqHandler(std::vector<Request>& requests, ElevatorManager& manager) : reqs(requests),manager_(manager){
    printf("init ReqHandler");
}

void ReqHandler::processRequests(){
     std::sort(reqs.begin(),reqs.end(),[&](Request reqA, Request reqB){
        return reqA.time < reqB.time;
    });

    for (Request& request : reqs) {
        thread_vector.emplace_back([&request, this](){ run(request); });
    }

    for (auto& t: thread_vector){
        t.join();
    }
    
}

void ReqHandler::run(Request& req){ 
    //  simulate time of request 
    std::this_thread::sleep_for(std::chrono::milliseconds(1000*req.time));
    //  submit the request
    manager_.addRequest(&req);
    printf("Client with id %d requested service\n",req.request_id);
    //  wait for completion
    double time1 = (double)std::clock()/CLOCKS_PER_SEC;

    std::unique_lock<std::mutex> lock(req.req_lk);

    req.cv_req.wait(lock, [&]{return (req.status == 1);});

    double timedif = (( ((double) clock()) / CLOCKS_PER_SEC) - time1) * 1000.0;

    printf("Client with id %d exited - service time was %f seconds\n",req.request_id,timedif);
};


