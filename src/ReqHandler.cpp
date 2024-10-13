#include "../include/ReqHandler.h"

ReqHandler::ReqHandler(vector<Request> requests){

}


void ReqHandler::run(){ // run for the req handler threads

};


Request ReqHandler::CreateRequest(int requestid,int entryFloor, int requestedFloor){
    Request newReq;
    newReq.entry_floor = entryFloor;
    newReq.requested_floor = requestedFloor;
    newReq.request_id = requestid;
    newReq.status = -1;
    return newReq;

};