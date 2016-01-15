DIR_EIGEN=/usr
CXX=c++
CXXOPTS=-std=c++11 -Wall -Wno-unused-variable -Wno-deprecated-declarations

all: bin/eigen3
	bin/eigen3
	R -f R.R > /dev/null
	julia julia.jl

bin/eigen3: eigen.cpp
	$(CXX) $(CXXOPTS) -I $(DIR_EIGEN)/include/eigen3 -o eigen3 eigen.cpp
	mkdir -p bin
	mv eigen3 bin/

clean:
	rm -f bin/*
