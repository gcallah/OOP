all: calc

CXXFLAGS=-g -std=c++11
CC=$(CXX)

calc: token.o parser.o calc.o vars.o funcs.o retval.o

token_test: token.o token_test.o
token.o: token.cpp token.h

vars_test: vars.o vars_test.o
vars.o: vars.cpp vars.h

funcs_test: funcs.o funcs_test.o
funcs.o: funcs.cpp funcs.h

retval_test: retval.o retval_test.o 
retval.o: retval.cpp retval.h
retval_test.o: retval_test.cpp retval.h

repo:
	git commit -a -m "New calculator version."
	git push origin master
