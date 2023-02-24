TARGET=verify
CC=g++
CFLAGS= --std=c++17 -Wall -g
LINKFLAGS= -lwiringPi

build: $(TARGET)

$(TARGET): verify.o
	$(CC) $(CFLAGS) -o $(TARGET) verify.o $(LINKFLAGS)

verify.o: verify.cpp
	$(CC) $(CFLAGS) -c verify.cpp

clean:
	rm $(TARGET) verify.o