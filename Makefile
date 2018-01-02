ent.o : util.h ent.h ent.cc
	g++ -c ent.cc

test: sys.h ent.o
	g++ test.cc ent.o -o test
