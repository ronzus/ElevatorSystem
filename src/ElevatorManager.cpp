#include "ElevatorManager.h"
#include <algorithm>
#include <mutex>


ElevatorManager::ElevatorManager(Algorithm algo,int numOfElev) : algo_(algo){
    initElevators(numOfElev);
    ManageElevators();

};

/*
Initializing Elevators access DS
*/

void ElevatorManager::initElevators(int nelev)
{
    for (int i = 0; i < nelev; i++) {

        Elevator* newElev = new Elevator(i, 0, DIR::UP, 0, this->algo_, 0, 5); // Review
        elevators.push_back(newElev);

        // Create the thread and move it into the vector
        thread threadObj(&Elevator::run, *newElev);
        elevthreads.push_back(std::move(threadObj));  // Use std::move here
    }
}

std::mutex reqMutex;  

void ElevatorManager::ManageElevators() {
    while (1) {
        std::unique_lock<std::mutex> lock(reqMutex);
        if (!requests.empty()) {
            Request newRequest = requests.front();
            requests.pop_front();
            lock.unlock();  // Unlock as soon as the request is retrieved

            bool requestProcessed = ProcessRequest(newRequest);

            if (!requestProcessed) {
                std::cout << "No elevator available to handle the request" << std::endl;
            }
            
        } else {
            lock.unlock();  // Unlock in case no requests are present
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


bool ElevatorManager::ProcessRequest(Request req) {

    for (Elevator* elev : elevators) {
        std::deque<int> temp = elev->getRequests();
        
        // Check if the elevator is passing through the request's entry floor (it is an external request)
        auto it = std::find_if(temp.begin(), temp.end(), [&](int floor) {
            return floor == req.entry_floor;
        });

        // If the elevator has the requested floor in its request queue, assign the new request to it
        if (it != temp.end()) {
            elev->addRequest(req);
            return true;
        }
    }
    //if not found we'll just add it to elev[0]'s queue (temporary)
    elevators[0]->addRequest(req);
    return true;
}
