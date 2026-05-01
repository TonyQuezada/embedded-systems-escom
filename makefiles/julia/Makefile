# Variables 
CXX = g++
CXXFLAGS = -std=c++23 -O3

GP = julia_set.gp 
TXT = $(GP:.gp=.txt)
PNG = $(GP:.gp=.png)

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

APP  = julia

## TARGETS

all: run plot open 

.PHONY: vars
vars:
	@echo "print variables"
	@echo "SRCS = $(SRCS)"
	@echo "OBJS = $(OBJS)"
	@echo "PRE  = $<"
	@echo "NAME = $@"
	@echo "GP   = $(GP)"
	@echo "TXT  = $(TXT)"

%.o: %.cpp
	@echo "Compiling"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(APP): $(OBJS)
	@echo "Linking"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(APP)

run: $(APP)
	@echo "RUN"
	./$(APP)

plot: $(TXT)
	@echo "Plot"
	gnuplot $(GP)

open:
	@echo "Open"
	cmd /c start $(PNG)

clean: 
	rm *.o $(APP) *.txt *.png