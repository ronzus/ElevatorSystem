#include "Elevator.h"
#include <thread>


Elevator::Elevator(int id ,int currLvl, DIR direction,float currLoad,Algorithm elevalgo) : id_(id),currlevel_(currLvl),direction_(direction),isDoorOpen_(false),currLoad_(currLoad),algo(elevalgo){};

    //Thread/Elevator action.

    void Elevator::run(){
        while(1){
            if(!requests.empty())
                this_thread::sleep_for(chrono::milliseconds(200000)); //filler ,need to put mutex
            else{
               
                switch (this->algo)
                {
                case FCFS:
                    int destfloor = requests.front();
                    requests.pop_front();
                    this_thread::sleep_for(chrono::milliseconds(1000*(abs(currlevel_ - destfloor)))); //no reason to use other functions? we aren't stopping so it doesn't matter. might still consider simulating floors when logging 
                    currlevel_ = destfloor;
                    printf("Elevator %d reached level %d",this->id_,this->currlevel_);
                    break;
                
                case SSTF:
                    int closestReq = calculateClosest();
                    int destfloor = requests; // implement getter
                    
                    /* code */
                    break;
                
                case SCAN:
                    /* code */
                    break;
                
                case LOOK:
                    /* code */
                    break;
                
                case CSCAN:
                    /* code */
                    break;
                
                case CLOOK:
                    /* code */
                    break;
                
                default:
                    break;
                }
            }
        }

    };

    int Elevator::calculateClosest(){ //can be implemented better
        int ret = 0;
        int minDiff = abs(currlevel_ - requests.front());
        for(int i = 0 ; i < requests.size() ; i++){
            int diff = abs(currlevel_ - requests.at(i));
            if(diff < minDiff)
                minDiff = diff;
                ret = i;
        }
        return ret;
    };
 
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



