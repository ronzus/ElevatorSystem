#include "Elevator.h"


Elevator::Elevator(int id ,int currLvl, DIR direction,float currLoad ) : id_(id),currlevel_(currLvl),direction_(direction),isDoorOpen_(false),currLoad_(currLoad){};

 
    //Elevator Operations

    bool Elevator::moveDOWN(){

        // basically shouldn't happen ,if this does occur its due to sync error.

        if(this->currlevel_ == 0)
            return false;

        this->currlevel_--;

        return true;
    };

    bool Elevator::moveUP(){

        if(this->currlevel_ == 0)
            return false;

        this->currlevel_++;
        
    };

    //consider turning these 2 into 1 ,might be harder to recognize weird behaviors though. 

    bool Elevator::openDoor(){

        if(isDoorOpen_){ //consider ignoring this behavior 
            return false;    
        }

        isDoorOpen_ = true;

        return true;
    };

    bool Elevator::closeDoor(){

         if(!isDoorOpen_){ //consider ignoring this behavior 
            return false;    
        }

        isDoorOpen_ = false;

        return true;
    }

    /*

    Getters and Setters

    */
    int Elevator::getId(){

        return this->id_;

    }

    
    int Elevator::getCurrLevel(){

        return this->currlevel_;

    }

    void Elevator::setCurrLevel(int level){

        this->currlevel_ = level;

    }

    DIR Elevator::getDir(){

        return this->direction_;

    }
    //change to bool?
    void Elevator::setDir(DIR newDir){

        this->direction_ = newDir;
        

    }

    float Elevator::getLoad(){

        return this->currLoad_;

    }

    void Elevator::setLoad(float newLoad){

        this->currLoad_ = newLoad;

    }



