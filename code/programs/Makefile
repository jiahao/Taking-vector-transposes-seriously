

DIR_EIGEN=/usr/local/Cellar/eigen/3.2.6
CXX=c++
CXXOPTS=-std=c++11 -Wall -Wno-unused-variable

all: bin/eigen3
	bin/eigen3

bin/eigen3: eigen.cpp
	$(CXX) $(CXXOPTS) -I $(DIR_EIGEN)/include/eigen3 -o eigen3 eigen.cpp
	mkdir -p bin
	mv eigen3 bin/

clean:
	rm -f bin/*
