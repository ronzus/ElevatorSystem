#pragma once

#include <string>
#include <iostream>
#include <queue>

using namespace std;

enum DIR{
    UP,
    DOWN
};

const int MAX_LEVEL = 5;

class Elevator{
    private:
            const int id_;
            int currlevel_;
            DIR direction_;
            bool isDoorOpen_;
            float currLoad_;

    public:
        //TODO Rule of 5
        Elevator(int id,int currLvl,DIR dir,float currLd);

        
        //consider changing to list
        //floors to visit
        queue<int> floorQueue;

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