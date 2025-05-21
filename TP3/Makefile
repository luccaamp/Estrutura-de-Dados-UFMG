CC = g++
CFLAGS = -Wall -std=c++11 -Iinclude
LDFLAGS = -pg -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXECUTABLE = $(BIN_DIR)/tp3.out

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

mem: $(EXECUTABLE)
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --show-leak-kinds=all --verbose -s ./$(EXECUTABLE)

perf: $(EXECUTABLE)
	perf stat ./$(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

test: $(OBJ_FILES)
	g++ -std=c++11 src/segTree.cpp program/*.cpp -Iinclude -Ithird_party -pg -o ./bin/teste_case
	./$(BIN_DIR)/teste_case

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)

val:
	./val.sh case-1

gen:
	./gen.sh
