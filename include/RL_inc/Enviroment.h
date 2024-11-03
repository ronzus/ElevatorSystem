#pragma once

#include <vector>
#include <queue>
#include <map>
#include "ElevatorManager.h"

enum class State{

};

class Environment {
private:
    int numFloors;
    std::vector<Elevator> elevators;          // Active elevators in the environment
    std::queue<Request> requestQueue;         // New requests generated dynamically
    std::map<int, std::vector<int>> floorMap; // Map to hold pending requests for each floor

public:
    Environment(int floors, int elevators, std::queue<Request> initialRequests);

    void generateRequest(int floor, int destination);
    bool isRequestPending(int floor);
    std::vector<int> getPendingRequests(int elevatorId);

    void step();  // Runs a single step in the environment for state update
    State getState();  // Extracts the current environment state for agents
};
