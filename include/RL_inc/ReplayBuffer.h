#pragma once 


class ReplayBuffer{
 private:


 public:
  //void store(state, action, reward, next_state);
  void sample(int batch_size);
};