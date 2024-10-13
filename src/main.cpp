#include "ElevatorManager.h"
#include "../include/json.hpp"

#include <fstream>

using json = nlohmann::json;

int main(){

    //here parsing the json file needs to occur.
    init_data d = parseDataFile("../data/config_input.json");
    ElevatorManager manager(Algorithm::FCFS,d.num_elev);
    
    
 return 0;   
}



init_data parseDataFile(std::string json_path) {
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
    for (const auto& event : data["events"]) {
        // Parse each event (request)
        int entry_floor = event["entry_floor"];
        int dest_floor = event["dest_floor"];

        // Create the Request object and push to the requests vector
        requests.push_back(Request{id, entry_floor, dest_floor});
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

