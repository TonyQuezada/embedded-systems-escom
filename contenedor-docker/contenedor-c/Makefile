# Makefile – Contenedor C++ + gnuplot

CXX      = g++
CXXFLAGS = -Wall -O2 -std=c++17
TARGET   = generar_imagen

all: $(TARGET) run

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET) -lm

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
