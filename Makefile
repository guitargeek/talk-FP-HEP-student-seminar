CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS=create_data_fp.cpp create_data_fp_multithread.cpp create_data_non_fp.cpp
OBJS=$(subst .cc,.o,$(SRCS))

all:
	g++ $(CPPFLAGS) $(LDLIBS) -o ./create_data_fp create_data_fp.cpp
	g++ $(CPPFLAGS) $(LDLIBS) -o ./create_data_fp_multithread create_data_fp_multithread.cpp
	g++ $(CPPFLAGS) $(LDLIBS) -o ./create_data_non_fp create_data_non_fp.cpp
