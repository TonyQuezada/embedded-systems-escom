# ====================================
#               Variables
# ====================================

# Operating System
OS = Windows

# Compiler
CXX = g++

# Compiler flags
#CXXFLAGS = -g -std=c++23 -Wall
CXXFLAGS = -std=c++23 -O3

# Formater
CPP_FORMATER = clang-format

# Source code
#SRCS = $(wildcard *.cpp)
SRCS = main.cpp

# Generate object file list
OBJS = $(SRCS:.cpp=.o)

# Target name
TARGET = julia_set

# Formater
CLANG_FORMAT = $(shell command -v $(CPP_FORMATER))

# 1 PNG   2 PDF
TERMINAL ?= 1

# ====================================
#               Targets
# ====================================

.PHONY: run formater gnuplot clean view

all: $(TARGET) run gnuplot view

# Rule to compile every .cpp to a .o
%.o: %.cpp
	@echo "> Compiling $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(TARGET): $(OBJS)
	@echo "> Linking object files"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) 

run:
	@echo "> Running $(TARGET)"
	./$(TARGET)

gnuplot:
	@echo "> Running gnuplot"
	gnuplot -c $(TARGET).gp $(TERMINAL)

view:
	@echo "> Opening viewer"
ifeq ($(TERMINAL), 1)
  ifeq ($(OS), Linux)
	  xdg-open $(TARGET).png &
  else ifeq ($(OS), Windows)
	  start $(TARGET).png &
  endif
endif
ifeq ($(TERMINAL), 2)
  ifeq ($(OS), Linux)
	  xdg-open $(TARGET).pdf &
  else ifeq ($(OS), Windows)
	  start $(TARGET).pdf &
  endif
endif

format: $(SRCS)
	@if command -v $(CPP_FORMATER) > /dev/null 2>&1 ; then \
		echo "> $(CPP_FORMATER) -i $^"; \
		$(CPP_FORMATER) -i $^ --style=Google; \
	else \
	  echo "$(CPP_FORMATER) is not installed. Formater skip."; \
	fi

clean:
	@echo "> Removing *.exe and *.o"
	rm -rf *.o *.exe *.txt *.png *.pdf $(TARGET)

help:
	@echo "> Help"

