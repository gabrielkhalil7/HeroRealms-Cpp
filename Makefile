# Compilateur et options
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -Iinclude

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

TARGET = hero_realms

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: run
run: $(TARGET)
	./$(TARGET) $(ARG)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
