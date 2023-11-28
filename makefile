CXX = clang++
CXXFLAGS = -std=c++17
CC = clang
CCFLAGS = -std=c17

all: stcpu

stcpu: single_threaded_cpu.cpp
	$(CXX) $(CXXFLAGS) -o stcpu single_threaded_cpu.cpp

clean:
	rm -rf stcpu single_threaded_cpu_debug
