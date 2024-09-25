CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET = build/my_sat

SRC_DIR = src

SRCS = $(SRC_DIR)/sat_solver.cpp $(SRC_DIR)/main.cpp

OBJS = $(SRCS:.cpp=.o)


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -c $@ $<

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

.PHONY: all clean