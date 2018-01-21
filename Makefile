.DEFAULT_GOAL := test
CXX := clang++
CXXFLAGS := -std=c++17

ces: ces_test.cc ces.h mpl.h
	$(CXX) $(CXXFLAGS) ces_test.cc -o ces

test: ces
	clear
	./ces
