
/*
    Copyright 2024 Ron Zusman
*/ 

#include "ElevatorManager.h"
#include "ReqHandler.h"
#include "../include/json.hpp"

#include <fstream>

using json = nlohmann::json;

init_data parseTrafficFile(std::string json_path);

int main(){

    //here parsing the json file needs to occur.
    init_data d = parseTrafficFile("data/config_input.json");
    
    ElevatorManager manager(Algorithm::FCFS,d.num_elev);
    ReqHandler handler(d.requests, manager);
    
 return 0;   
}



init_data parseTrafficFile(std::string json_path) {
    // Open and parse the JSON file
    std::ifstream f(json_path);
    json data = json::parse(f);
   // Extract the number of floors and elevators
    int num_floors = data["number of floors"];
    int num_elev = data["number of elevators"];

    // Extract the starting floors as a vector of integers
    std::vector<int> starting_floors = data["starting floors"].get<std::vector<int>>();

    // Extract the events and convert them to Request objects
    std::vector<Request> requests;
    int id = 0;
    for (const auto& request : data["events"]) {
        // Parse each event (request)
        int entry_floor = request["entry_floor"];
        int dest_floor = request["dest_floor"];
        int time = request["time"];

        // Create the Request object and push to the requests vector
        requests.push_back(Request{id, entry_floor, dest_floor, -1, time});

        printf("id:%d\nentry floor:%d\ndest floor:%d\ntime:%d\n\n",id,entry_floor,dest_floor,time);

        id++;
    }

    // Create and return the init_data structure
    return init_data{
        num_floors,
        num_elev,
        starting_floors,
        requests
    };
}

