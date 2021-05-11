ROOTCFLAGS = -pthread -std=c++17 -m64 -I/cvmfs/sft.cern.ch/lcg/releases/ROOT/6.18.00-2459b/x86_64-centos7-gcc8-opt/include
ROOTLIBS   = $(shell root-config --libs)

CXX = g++
RM  = rm -f

INCLUDE = -L$(PWD)/../lib -llib

CXXFLAGS += $(ROOTCFLAGS) -I$(PWD)/../lib
CXXFLAGS += -Wall -Wno-deprecated -ggdb -fPIC -O2 -fopenmp
LIBS     += $(ROOTLIBS) -lTreePlayer -lMinuit

SRC = $(wildcard *.cxx $(PWD)/../lib/*.cxx)
OBJ = $(patsubst %.cxx, %.o, $(SRC))

RUN = $(wildcard *.C $(PWD)/../include/*.C)
EXE = $(patsubst %.C, %.exe, $(RUN))

GARBAGE = $(OBJ) $(EXE)

all : $(OBJ) $(EXE)

%.exe : %.C $(OBJ)
	@echo "creating " $@
	$(CXX) $+ -o $@ $(CXXFLAGS) $(LIBS)
%.o : %.cxx %.h
	@echo "creating " $@
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	@$(RM) $(GARBAGE)
