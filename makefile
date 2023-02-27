TARGET=main
CC=g++
CFLAGS= --std=c++17 -Wall -g
LINKFLAGS= -lwiringPi -lcurl

build: $(TARGET)

$(TARGET): main.o keypad.o client.o terminal.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o keypad.o client.o terminal.o $(LINKFLAGS)

main.o: src/main.cpp include/main.h src/keypad.cpp include/keypad.h src/client.cpp include/client.h src/terminal.cpp include/terminal.h
	$(CC) $(CFLAGS) -c src/main.cpp

keypad.o: src/keypad.cpp include/keypad.h src/client.cpp include/client.h
	$(CC) $(CFLAGS) -c src/keypad.cpp

client.o: src/client.cpp include/client.h src/terminal.cpp include/terminal.h
	$(CC) $(CFLAGS) -c src/client.cpp

terminal.o: src/terminal.cpp include/terminal.h
	$(CC) $(CFLAGS) -c src/terminal.cpp

check: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm $(TARGET) keypad.o client.o terminal.o