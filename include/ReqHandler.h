#pragma once

#include <Request.h>
#include <string>
#include <iostream>
#include <queue>

using namespace std;
enum Mode{
    SIM,
    RT
};
class ReqHandler{
    private:
        queue<Request> requestQueue;
        Mode handlerMode;
    public:

};