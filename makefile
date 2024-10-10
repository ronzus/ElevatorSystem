CC = g++
CFLAGS = -Wall -g -Iinclude

# Target for the final executable - Linker
main: main.o ElevatorManager.o Elevator.o ReqHandler.o
	$(CC) $(CFLAGS) -o main main.o ElevatorManager.o Elevator.o ReqHandler.o

# Compile the main file
main.o: src/main.cpp include/ElevatorManager.h include/Elevator.h include/ReqHandler.h
	$(CC) $(CFLAGS) -c src/main.cpp

# Compile the ElevatorManager
ElevatorManager.o: src/ElevatorManager.cpp include/ElevatorManager.h include/Elevator.h
	$(CC) $(CFLAGS) -c src/ElevatorManager.cpp

# Compile the Elevator
Elevator.o: src/Elevator.cpp include/Elevator.h
	$(CC) $(CFLAGS) -c src/Elevator.cpp

# Compile the ReqHandler
ReqHandler.o: src/ReqHandler.cpp include/ReqHandler.h
	$(CC) $(CFLAGS) -c src/ReqHandler.cpp

# Clean up object files and the final executable
clean:
	rm -f *.o main
