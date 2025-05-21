CC = g++
CFLAGS = -Wall -std=c++11 -Iinclude
LDFLAGS = -pg -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXECUTABLE = $(BIN_DIR)/tp2.out

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test: $(OBJ_FILES)
	g++ -std=c++11 src/heap.cpp src/lista.cpp src/ListaAdjacencia.cpp src/graph.cpp program/*.cpp -Iinclude -Ithird_party -pg -o ./bin/teste_case
	./$(BIN_DIR)/teste_case

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)