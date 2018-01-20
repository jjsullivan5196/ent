test: ces_test.cc ces.h mpl.h
	clang++ -std=c++17 ces_test.cc -o ces_test
	./ces_test
