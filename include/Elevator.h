#pragma once

#include <string>
#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include <ReqHandler.h>

using namespace std;

enum class DIR{
    UP,
    DOWN
};

enum class Algorithm{ //Look into dynamic sched and moving in not straight dir (final final)
    FCFS = 1,
    SSTF = 2,
    SCAN = 3,
    LOOK = 4,
    CSCAN = 5,
    CLOOK = 6 
};

const int MAX_LEVEL = 5;

class Elevator{
    private:    //Add speed parameter
            const int id_;
            int currlevel_;
            DIR direction_;
            bool isDoorOpen_;
            float currLoad_;
            Algorithm algo;
            vector<Request> requests; // update to request ,mby change to map or set 
            int startFloor_;
            int endFloor_;

    public:
        //TODO Rule of 5
        Elevator(int id,int currLvl,DIR dir,float currLd,Algorithm algo,int startFloor,int endFloor);

        void run();

        int calculateClosest(); //calculate which request is closest to curr position.

        //consider changing to list
        //floors to visit
        //queue<int> floorQueue;

        //Elevator movements

        bool moveDOWN();

        bool moveUP();

        // Door Operations

        bool openDoor();

        bool closeDoor();

        /*
        Getters & Setters
        */

        int getId();

        int getCurrLevel();

        void setCurrLevel(int level);

        DIR getDir();

        void setDir(DIR new_direction);

        float getLoad();

        void setLoad(float newLoad);

        
}; // class Elevator
