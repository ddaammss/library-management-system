CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = library

SRCS = $(wildcard src/*.cpp src/**/*.cpp)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
