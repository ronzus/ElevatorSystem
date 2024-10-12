#include "Elevator.h"
#include <thread>
#include <mutex>
#include <algorithm>


Elevator::Elevator(int id ,int currLvl, DIR direction,float currLoad,Algorithm elevalgo,int startFloor,int endFloor) : id_(id),currlevel_(currLvl),direction_(direction),isDoorOpen_(false),currLoad_(currLoad),algo(elevalgo),startFloor_(startFloor),endFloor_(endFloor){};

    //Thread/Elevator action.

    void Elevator::run(){
        while(1){

            //condition variable
            std::unique_lock<std::mutex> lock(this->ReqsMutex);

            if(requests.empty())
                this_thread::sleep_for(chrono::milliseconds(2000)); //filler ,need to put mutex
            else{
                int targetFloor = -1;
                switch (this->algo)
                {
                case Algorithm::FCFS:{

                    targetFloor = requests.front();
                    break;

                }
                case Algorithm::SSTF:{

                    int closestReq = calculateClosest(); //index
                    targetFloor = requests[closestReq];             
                    break;

                }
                case Algorithm::SCAN:{ // change so it goes to the top floor and not the top requested floor

                    // Sort the requests
                    sort(requests.begin(), requests.end());
                    
                    
                    if(direction_ == DIR::UP ){
                        //Look for the first request above ot at curr lvl
                        auto it = std::find_if(this->requests.begin(),this->requests.end(),[&](int req){

                            return req >= this->currlevel_;

                        });

                        if(it != requests.end()){
                            //There's a request above the current level
                            targetFloor = *it;

                        } else {

                            direction_ = DIR::DOWN;
                            
                            targetFloor = requests.back();
                            
                        }

                    } else if(direction_ == DIR::DOWN) {

                         auto it = std::find_if(requests.rbegin(),requests.rend(),[&](int req){ 

                            return req <= currlevel_;

                        });

                        if(it != requests.rend()) {

                            targetFloor = *it;

                        } else {
                            
                            direction_ = DIR::UP;
                            
                            targetFloor = requests.front();

                        }

                    }

                    break;
                }
                case Algorithm::CSCAN:{



                    sort(requests.begin(), requests.end());

                    auto it = std::find_if(requests.begin(),requests.end(),[&](int req){ 

                        return req >= currlevel_;

                    });

                    if(it != requests.end()) {

                        targetFloor = *it;

                    } else {
                                                    
                        targetFloor = requests.front();

                    }

                    break;
                    
                }
                
                case Algorithm::LOOK:{
                    /* code */
                    break;
                }
                case Algorithm::CLOOK:{
                    /* code */
                    break;
                }
                default:
                {
                    break;
                }
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
                if(currlevel_ == targetFloor) {
                    printf("Elevator %d reached target floor %d\n", this->id_, targetFloor);
                    //remove request and add internal requests

                    // Simulate opening and closing the door
                    if(openDoor()) {
                        printf("Elevator %d doors opened.\n", this->id_);
                        this_thread::sleep_for(chrono::milliseconds(2000));  // Doors stay open for 2 seconds
                        closeDoor();
                        printf("Elevator %d doors closed.\n", this->id_);
                    }
                }

                
            }

            this->ReqsMutex.unlock();
        }

    };

    int Elevator::calculateClosest(){ //can be implemented better
        int ret = 0;
        int minDiff = abs(currlevel_ - requests.front() );

        // fix casting - not recommended (unless you are sure that requests.size will always fit within the range of an int).
        for(int i = 0 ; i < static_cast<int>(requests.size()) ; i++){ 

            int diff = abs(currlevel_ - requests.at(i) );

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

    void Elevator::setCurrLevel(int level){ //do I really need this?

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

    deque<int> Elevator::getRequests(){
        return requests;
    }

    void Elevator::addRequest(Request& req){
        //TODO
        std::unique_lock<std::mutex> lock(this->ReqsMutex);


        this->ReqsMutex.unlock();

        
    }
        

