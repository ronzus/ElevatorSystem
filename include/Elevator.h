#pragma once

#include <string>
#include <iostream>
#include <deque>
#include <list>
#include <vector>

using namespace std;

enum DIR{
    UP,
    DOWN
};

enum Algorithm{ //Look into dynamic sched and moving in not straight dir (final final)
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
            list<int> requests; // update to request ,mby change to map or set 

    public:
        //TODO Rule of 5
        Elevator(int id,int currLvl,DIR dir,float currLd,Algorithm algo);

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