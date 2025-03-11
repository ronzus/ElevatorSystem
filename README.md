# Elevator Management System

## Overview
The Elevator Management System is a multi-threaded simulation of elevator operations using C++. It supports various scheduling algorithms to efficiently handle multiple requests. The system is designed to model real-world elevator traffic with thread-safe request handling and dynamic decision-making.

## Features
- Multi-threaded implementation using `std::thread` for concurrent elevator operations.
- Supports multiple scheduling algorithms:
  - **First-Come, First-Served (FCFS)**
  - **Shortest Seek Time First (SSTF)**
  - **SCAN (Elevator Algorithm)**
  - **Circular SCAN (CSCAN)**
  - **LOOK**
  - **CLOOK**
- Thread synchronization with `std::mutex` and `std::condition_variable`.
- Dynamic request allocation and processing.
- Real-time simulation with step-by-step elevator movement.

## Usage
1. Define the number of floors and elevators in `main.cpp`.
2. Choose a scheduling algorithm (e.g., `Algorithm::SSTF`).
3. Run the program to simulate elevator movements and request handling.
4. Observe outputs that indicate elevator status and request processing.

## Threading & Synchronization
- **Elevator Threads**: Each elevator runs in its own thread, executing `Elevator::run()`.
- **Mutex & Condition Variables**: Used to synchronize access to shared data (`std::mutex`, `std::condition_variable`).
- **Request Handling**: Requests are added to a queue, and elevators pick them up dynamically.

## Future Improvements
- Implement more real-world constraints like weight limits and door timers.
- Sideways Elevators (working on it currently)
