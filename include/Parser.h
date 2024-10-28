
#pragma once

#include "Request.h"

#include <vector>

struct traffic_data {
    std::vector<Request> requests;
};

struct config_data
{
    int algo;
    int num_floors;
    int num_elev;
    std::vector<int> starting_floors;
   
};

class Parser{

    public:
    
    static config_data parseConfig(std::string json_path);
 
    static traffic_data parseTraffic(std::string json_path);
};

