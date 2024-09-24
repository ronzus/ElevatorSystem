#pragma once

#include <string>
#include <iostream>
#include <queue>

using namespace std;
enum DIR{
    UP,
    DOWN
};
class Elevator{
    private:
            const int id_;
            int currlevel_;
            DIR direction_;
            bool isDoorOpen_;
            float currLoad_;
            


    public:
        //TODO Rule of 5
        Elevator(int id);

        
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

        void getId();

        int getCurrLevel();

        void setCurrLevel(int level);

        DIR getDir();

        void setDir(DIR new_direction);

        float getLoad();

        void setLoad(float newLoad);

        
}; // class Elevator