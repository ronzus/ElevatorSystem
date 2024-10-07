#include "Elevator.h"
#include <thread>
#include <mutex>
#include <algorithm>
std::mutex mtx;

Elevator::Elevator(int id ,int currLvl, DIR direction,float currLoad,Algorithm elevalgo,int startFloor,int endFloor) : id_(id),currlevel_(currLvl),direction_(direction),isDoorOpen_(false),currLoad_(currLoad),algo(elevalgo),startFloor_(startFloor),endFloor_(endFloor){};

    //Thread/Elevator action.

    void Elevator::run(){
        while(1){
            // ADD a condition variable
            std::lock_guard<std::mutex> lock(mtx);
            if(requests.empty())
                this_thread::sleep_for(chrono::milliseconds(2000)); //filler ,need to put mutex
            else{
                int targetFloor = -1;
                switch (this->algo)
                {
                case Algorithm::FCFS:

                    targetFloor = requests.front();
                    break;
                
                case Algorithm::SSTF:

                    int closestReq = calculateClosest(); //index
                    targetFloor = requests[closestReq];             
                    break;
                
                case Algorithm::SCAN:
                    /* code */
                      // Sort the requests
                    sort(requests.begin(), requests.end());
                    
                    
                    if(direction_ == DIR::UP){
                        targetFloor = MAX_LEVEL; //??
                    }
                    else{
                        targetFloor = 0;    //??
                    }
                      // Sort the requests
                    sort(requests.begin(), requests.end());
                    
                    

                    break;
                
                case Algorithm::LOOK:
                    /* code */
                    break;
                
                case Algorithm::CSCAN:
                    /* code */
                    break;
                
                case Algorithm::CLOOK:
                    /* code */
                    break;
                
                default:
                    break;
                }
                 // Move towards the target floor step-by-step
                if (currlevel_ < targetFloor) {
                    currlevel_++;
                    printf("Elevator %d moving up to level %d\n", this->id_, this->currlevel_);
                } else if (currlevel_ > targetFloor) {
                    currlevel_--;
                    printf("Elevator %d moving down to level %d\n", this->id_, this->currlevel_);
                }

                // Simulate time between floor transitions
                this_thread::sleep_for(chrono::milliseconds(1000));

                // When the elevator reaches the target floor
                if (currlevel_ == targetFloor) {
                    printf("Elevator %d reached target floor %d\n", this->id_, targetFloor);

                    // Simulate opening and closing the door
                    if (openDoor()) {
                        printf("Elevator %d doors opened.\n", this->id_);
                        this_thread::sleep_for(chrono::milliseconds(2000));  // Doors stay open for 2 seconds
                        closeDoor();
                        printf("Elevator %d doors closed.\n", this->id_);
                    }
                }
            }
        }

    };

    int Elevator::calculateClosest(){ //can be implemented better
        int ret = 0;
        int minDiff = abs(currlevel_ - requests.front());
        for(int i = 0 ; i < requests.size() ; i++){
            int diff = abs(currlevel_ - requests.at(i));
            if(diff < minDiff){
                minDiff = diff;
                ret = i;
            }
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
        return true;
        
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



