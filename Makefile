CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11

SRC_DIR := src
BIN_DIR := bin
INCLUDE_DIR := $(SRC_DIR)/inc

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRC_FILES))

EXECUTABLE := $(BIN_DIR)/interpreter.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

$(BIN_DIR):
	if not exist "$(BIN_DIR)" mkdir $(BIN_DIR)

clean:
	if exist "$(BIN_DIR)" rmdir /s /q "$(BIN_DIR)"

.PHONY: all clean