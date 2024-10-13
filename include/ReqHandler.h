#pragma once

#include <string>
#include <iostream>
#include <queue>

using namespace std;
enum Mode{
    SIM,
    RT
};
struct Request {

    int request_id;
    int entry_floor; //External request
    int requested_floor; //Internal request
    int status; // -1 - not onboard , 0 - onboard, 1 - done

    //Comparison operators

    bool operator<(const Request &a) const
    {
        return requested_floor < a.requested_floor;
    }

    bool operator=(const Request &a) const
    {
        return  (request_id == a.request_id) && 
                (status == a.status) && 
                (entry_floor == a.entry_floor) && 
                (requested_floor == a.requested_floor);
    }
};

class ReqHandler{
    private:
        queue<Request> request_queue;
        Mode handler_mode;
        
    public:

        ReqHandler(vector<Request> requests);

        void run();

        Request CreateRequest(int requestid,int entryFloor, int requestedFloor);//Basically generate

};

