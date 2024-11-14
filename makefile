CC = g++
CFLAGS = -std=c++14

hungarian: main.o hung.o
	$(CC) -o hungarian main.o hung.o

hung.o: hungarian.cpp hungarian.h
	$(CC) -c hungarian.cpp -o hung.o

main.o: main.cpp hungarian.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

clean:
	-rm main.o hung.o