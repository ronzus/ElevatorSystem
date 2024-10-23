

#include <mutex>

struct Request {

    int request_id;
    int entry_floor;  // External request
    int requested_floor;  // Internal request
    int status;  // -1 - not onboard , 0 - onboard, 1 - done
    int time;  // update to float when done
    std::mutex req_lk;
    // Comparison operators
    bool operator<(const Request &a) const {
        return requested_floor < a.requested_floor;
    }

    bool operator=(const Request &a) const {
        return  (request_id == a.request_id) &&
                (status == a.status) &&
                (entry_floor == a.entry_floor) &&
                (requested_floor == a.requested_floor);
    }
};
