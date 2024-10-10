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
    const string request_id;
    const string client_id; //optional
    const int requested_floor;
        //optional - direction

    //Comparison operators

    bool operator<(const Request& a) const
    {
        return requested_floor < a.requested_floor;
    }

    bool operator=(const Request& a) const
    {
        return (request_id == a.request_id) && (client_id == a.client_id) && (requested_floor == a.requested_floor);
    }
};
class ReqHandler{
    private:
        queue<Request> requestQueue;
        Mode handlerMode;
        
    public:

};

