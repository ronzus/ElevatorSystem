#include "Parser.h"
#include "../include/json.hpp"

using json = nlohmann::json;

#include <fstream>

config_data Parser::parseConfig(std::string json_path) {
    // Open and parse the JSON file
    std::ifstream f(json_path);
    json data = json::parse(f);
   // Extract the number of floors and elevators
    int algo = data["algorithm"];
    int num_floors = data["number of floors"];
    int num_elev = data["number of elevators"];
    
    // Extract the starting floors as a vector of integers
    std::vector<int> starting_floors = data["starting floors"].get<std::vector<int>>();

    return config_data{
        algo,
        num_floors,
        num_elev,
        starting_floors
    };  
}

traffic_data Parser::parseTraffic(std::string json_path) {
    // Open and parse the JSON file
    std::ifstream f(json_path);
    json data = json::parse(f);
   
    std::vector<Request> requests;
    int id = 0;

    for (const auto& request : data["entries"]) {
        // Check if request has required fields
        if (!request.contains("entry_floor") || !request.contains("dest_floor") || !request.contains("time")) {
            printf("Missing required fields in request at index %d\n", id);
            continue; // Skip this request or handle it appropriately
        }

        // Parse each event (request)
        int entry_floor = request["entry_floor"];
        int dest_floor = request["dest_floor"];
        int time = request["time"];

        // Create the Request object and push to the requests vector
        requests.push_back(Request(id, entry_floor, dest_floor, -1, time));
        /*
        printf("id:%d\nentry floor:%d\ndest floor:%d\ntime:%d\n\n", 
                requests.back().request_id,
                requests.back().entry_floor,
                requests.back().requested_floor,
                requests.back().time);
        */
        id++;
    }
    return traffic_data{
       requests
    };
}