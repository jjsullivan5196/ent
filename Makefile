.DEFAULT_GOAL := test
CXX := clang++
CXXFLAGS := -std=c++17

ces: ces_test.cc ces.h mpl.h
	$(CXX) $(CXXFLAGS) ces_test.cc -o ces

test: ces
	clear
	./ces

test_index: test_index.cc
	clear
	$(CXX) $(CXXFLAGS) test_index.cc -o test_index
	clear
	./test_index
