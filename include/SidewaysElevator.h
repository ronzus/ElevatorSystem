
#include "Elevator.h"
#include <tuple>
class SidewaysElevator: public Elevator{
 private:
    // (bottom left, top left, top right, bottom right)(x,y coordinates)
    std::tuple<std::pair<int,int>,std::pair<int,int>,std::pair<int,int>,std::pair<int,int>> coordinates; 

 public:
    void run();
};