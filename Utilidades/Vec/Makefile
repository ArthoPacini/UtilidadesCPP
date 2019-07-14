CC_WINDOWS=g++
CC_UNIX=g++-9
CC=g++
CFLAGS=-I. -std=c++17 -pthread -ffast-math -Wall -O3 -mavx

make:
	$(CC) main.cpp -o main $(CFLAGS)
make unix:
	$(CC_UNIX) main.cpp -o main $(CFLAGS)
make windows:
	$(CC_WINDOWS) main.cpp -o main $(CFLAGS)

clean:
	rm ./main