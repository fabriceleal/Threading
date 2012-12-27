
# This makefile will generate each target from a cpp file with the same name

CC=g++
FLAGS=--std=c++0x -lpthread
TARGETS=helloworld sharing bare waiting futures

all: $(TARGETS)

%: %.cpp
	$(CC) $? -o $@ $(FLAGS)

clean:
	rm -f $(TARGETS) *.o
