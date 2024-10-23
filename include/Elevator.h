
/*
    Copyright 2024 Ron Zusman
*/ 

#pragma once 
#include <string>
#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include <mutex>
#include <condition_variable> 
#include <unordered_map>
#include "Request.h"

enum class DIR{
    UP,
    DOWN,
    IDLE
};

enum class Algorithm{
    FCFS = 1,
    SSTF = 2,
    SCAN = 3,
    LOOK = 4,
    CSCAN = 5,
    CLOOK = 6
};

const int MAX_LEVEL = 5;
#include <utility>  // for std::move

class Elevator {
 private:
    const int id_;
    int currlevel_;
    DIR direction_;
    bool isDoorOpen_;
    float currLoad_;
    Algorithm algo;
    std::deque<int> floorsToVisit;  // only actual floors to visit
    std::unordered_map<int,std::vector<Request&>> external_to_request; 
    std::unordered_map<int,std::vector<Request&>> internal_to_request; 
    int startFloor_;
    int endFloor_;
    std::mutex ReqsMutex;
    std::condition_variable cv;


 public:
    // Constructor
    Elevator(int id, int currLvl, DIR dir, float currLd, Algorithm algo, int startFloor, int endFloor)
        : id_(id), currlevel_(currLvl), direction_(dir), isDoorOpen_(false), currLoad_(currLd),
          algo(algo), startFloor_(startFloor), endFloor_(endFloor) {}

    // Destructor
    ~Elevator() {
        // Nothing special to clean up here, but included for completeness.
    }

    // Copy Constructor
    Elevator(const Elevator& other)
        : id_(other.id_), currlevel_(other.currlevel_), direction_(other.direction_),
          isDoorOpen_(other.isDoorOpen_), currLoad_(other.currLoad_), algo(other.algo),
          floorsToVisit(other.floorsToVisit), startFloor_(other.startFloor_), endFloor_(other.endFloor_) {
        // Copying a mutex is not allowed, so we don't copy `ReqsMutex`
    }

    // Copy Assignment Operator
    Elevator& operator=(const Elevator& other) {
        if (this == &other) {
            return *this;  // Handle self-assignment
        }
        // id_ is const, so we can't reassign it. Other members can be reassigned.
        currlevel_ = other.currlevel_;
        direction_ = other.direction_;
        isDoorOpen_ = other.isDoorOpen_;
        currLoad_ = other.currLoad_;
        algo = other.algo;
        floorsToVisit = other.floorsToVisit;
        startFloor_ = other.startFloor_;
        endFloor_ = other.endFloor_;
        // Don't copy `ReqsMutex` as mutexes can't be copied
        return *this;
    }

    // Move Constructor
    Elevator(Elevator&& other) noexcept
        : id_(other.id_), currlevel_(std::move(other.currlevel_)), direction_(std::move(other.direction_)),
          isDoorOpen_(std::move(other.isDoorOpen_)), currLoad_(std::move(other.currLoad_)),
          algo(std::move(other.algo)), floorsToVisit(std::move(other.floorsToVisit)),
          startFloor_(std::move(other.startFloor_)), endFloor_(std::move(other.endFloor_)) {
        // Move mutex by default since we cannot move the mutex, we need to reconstruct it
        // Since the mutex object itself doesn't manage resources, there's no harm in letting the new Elevator object construct a new mutex.
    }

    // Move Assignment Operator
    Elevator& operator=(Elevator&& other) noexcept {
        if (this == &other) {
            return *this;  // Handle self-assignment
        }

        // id_ is const, so it cannot be reassigned
        currlevel_ = std::move(other.currlevel_);
        direction_ = std::move(other.direction_);
        isDoorOpen_ = std::move(other.isDoorOpen_);
        currLoad_ = std::move(other.currLoad_);
        algo = std::move(other.algo);
        floorsToVisit = std::move(other.floorsToVisit);
        startFloor_ = std::move(other.startFloor_);
        endFloor_ = std::move(other.endFloor_);

        // Same as move constructor, we don't move mutex

        return *this;
    }

    void run();
    int calculateClosest();
    bool moveDOWN();
    bool moveUP();
    bool openDoor();
    bool closeDoor();

    // Getters and Setters
    int getId();
    int getCurrLevel();
    void setCurrLevel(int level);
    DIR getDir();
    void setDir(DIR new_direction);
    float getLoad();
    void setLoad(float newLoad);
    std::deque<int> getRequests();
    void addRequest(Request &req);
};
