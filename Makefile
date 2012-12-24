
CC=g++
FLAGS=--std=c++0x -lpthread

SRC_HELLOWORLD=helloworld.cpp

helloworld:$(SRC_HELLOWORLD)
	$(CC) $? -o $@ $(FLAGS)

clean:
	rm -f helloworld *.o