all: calc

CXXFLAGS=-g -std=c++11
CC=$(CXX)
INCS=$(shell ls *.h)

calc: token.o parser.o calc.o vars.o funcs.o retval.o

calc.o: calc.cpp $(INCS)

token_test: token.o token_test.o

token.o: token.cpp token.h

retval_test: retval.o retval_test.o 

retval.o: retval.cpp retval.h

retval_test.o: retval_test.cpp retval.h

vars_test: vars.o vars_test.o retval.o

vars.o: vars.cpp vars.h retval.h

funcs_test: funcs.o funcs_test.o

funcs.o: funcs.cpp funcs.h const.h

repo:
	./all_tests.sh
	-git commit -a 
	git push origin master
