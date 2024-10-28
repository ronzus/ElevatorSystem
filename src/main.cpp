
/*
    Copyright 2024 Ron Zusman
*/ 

#include "ElevatorManager.h"
#include "ReqHandler.h"
#include "../include/json.hpp"
#include "Parser.h"
#include <fstream>

using json = nlohmann::json;

int main(){
    
    config_data con = Parser::parseConfig("data/config.json");
    traffic_data traf = Parser::parseTraffic("data/traffic.json");

    ElevatorManager manager(static_cast<Algorithm>(con.algo),con.num_elev,con.starting_floors,con.num_floors);
    std::thread managerThread1([&]() {
        manager.initElevators(con.num_elev,con.starting_floors,con.num_floors);
    });
    std::thread managerThread2([&manager]() {
        manager.ManageElevators();
    });
    ReqHandler handler(traf.requests, manager); 
    std::thread handlerThread([&handler]() {
        handler.processRequests();  // Assuming processRequests() is the method that handles all requests
    });
    //wait for both threads
    if (managerThread1.joinable()) {
        managerThread1.join();
    }
    if (managerThread2.joinable()) {
        managerThread2.join();
    }
    if (handlerThread.joinable()) {
        handlerThread.join();
    }

 return 0;   
}
