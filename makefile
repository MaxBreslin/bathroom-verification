TARGET=verify
CC=g++
CFLAGS= --std=c++20 -Wall -g
LINKFLAGS= -lwiringPi -lcurl

build: $(TARGET)

$(TARGET): verify.o
	$(CC) $(CFLAGS) -o $(TARGET) verify.o $(LINKFLAGS)

verify.o: verify.cpp
	$(CC) $(CFLAGS) -c verify.cpp

check: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm $(TARGET) verify.o