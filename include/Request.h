#pragma once

#include <mutex>
#include <condition_variable>
#include <utility>  // for std::move


class Request { //update all
   public:
    int request_id;
    int entry_floor;  // External request
    int requested_floor;  // Internal request
    int status;  // -1 - not onboard , 0 - onboard, 1 - done
    int time;  // update to float when done
    //float weight;
    std::mutex req_lk;
    std::condition_variable cv_req;
    // Comparison operators

    Request(int id, int entryFloor,int destFloor, int status, int time): request_id(id), entry_floor(entryFloor),
    requested_floor(destFloor), status(status), time(time){}

     // Destructor
    ~Request() {
        // Nothing special to clean up here, but included for completeness.
    }

    // Copy Constructor
    Request(const Request& other)
        : request_id(other.request_id), entry_floor(other.entry_floor), requested_floor(other.requested_floor),
          status(other.status), time(other.time) {
        // Copying a mutex is not allowed, so we don't copy `ReqsMutex`
    }

    // Copy Assignment Operator
    Request& operator=(const Request& other) {
        if (this == &other) {
            return *this;  // Handle self-assignment
        }
        // id_ is const, so we can't reassign it. Other members can be reassigned.
        request_id = other.request_id;
        entry_floor = other.entry_floor;
        requested_floor = other.requested_floor;
        status = other.status;
        time = other.time;
        
        // Don't copy `ReqsMutex` as mutexes can't be copied
        return *this;
    }

    // Move Constructor
    Request(Request&& other) noexcept
        : request_id(other.request_id), entry_floor(std::move(other.entry_floor)), requested_floor(std::move(other.requested_floor)),
          status(std::move(other.status)), time(std::move(other.time)){
        // Move mutex by default since we cannot move the mutex, we need to reconstruct it
        // Since the mutex object itself doesn't manage resources, there's no harm in letting the new Elevator object construct a new mutex.
    }

    // Move Assignment Operator
    Request& operator=(Request&& other) noexcept {
        if (this == &other) {
            return *this;  // Handle self-assignment
        }

        // id_ is const, so it cannot be reassigned
        request_id = std::move(other.request_id);
        entry_floor = std::move(other.entry_floor);
        requested_floor = std::move(other.requested_floor);
        status = std::move(other.status);
        time = std::move(other.time);        

        // Same as move constructor, we don't move mutex

        return *this;
    }

    //implement rule of 5.
   
};
