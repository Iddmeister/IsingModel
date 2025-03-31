CC = g++
CFLAGS = -std=c++17
SRC = main.cpp 
EXEC = main

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)
