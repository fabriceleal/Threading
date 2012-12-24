
CC=g++
FLAGS=--std=c++0x -lpthread

SRC_HELLOWORLD=helloworld.cpp
SRC_SHARING=sharingiscaring.cpp

all: helloworld sharing

helloworld:$(SRC_HELLOWORLD)
	$(CC) $? -o $@ $(FLAGS)


sharing:$(SRC_SHARING)
	$(CC) $? -o $@ $(FLAGS)


clean:
	rm -f helloworld sharing *.o
