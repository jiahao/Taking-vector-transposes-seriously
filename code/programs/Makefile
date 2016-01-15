DIR_EIGEN=/usr
CXX=c++
CXXOPTS=-std=c++11 -Wall -Wno-unused-variable -Wno-deprecated-declarations
TORCH=$(HOME)/torch/install/bin/th

all: bin/eigen3 r julia torch
	bin/eigen3

r: R.R
	R -f R.R > /dev/null

julia: julia.jl
	julia julia.jl

torch: torch.lua
	$(TORCH) torch.lua

bin/eigen3: eigen.cpp
	$(CXX) $(CXXOPTS) -I $(DIR_EIGEN)/include/eigen3 -o eigen3 eigen.cpp
	mkdir -p bin
	mv eigen3 bin/

clean:
	rm -f bin/*
