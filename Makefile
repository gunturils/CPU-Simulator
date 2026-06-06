# CXX is the variable for the C++ compiler
CXX = g++

#CXXFLAGS are flags passed to the compiler every time it runs
CXXFLAGS = -I./include -Wall -Wextra

SRCS = src/main.cpp src/cpu.cpp

TARGET = simulator

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
