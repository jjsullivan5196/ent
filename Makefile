ent.o : util.h ent.h ent.cc
	g++ -std=c++17 -c ent.cc

test: test.cc sys.h ent.o
	g++ -std=c++17 test.cc ent.o -o test
