CC = g++
CFLAGS = -Wall -std=c++11 -Iinclude
LDFLAGS = -pg -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXECUTABLE = $(BIN_DIR)/tp1.out

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

mem: $(EXECUTABLE)
#	valgrind --leak-check=full --show-leak-kinds=all -s ./$(EXECUTABLE) -s "0 | 1 & 2" eae
#	valgrind --track-origins=yes --show-leak-kinds=all -s ./$(EXECUTABLE) -s "( 5 | ( ( 3 & ( ( 0 | 1 ) | 2 ) ) & 4 ) )" aee001
#	valgrind --track-origins=yes --show-leak-kinds=all --verbose -s ./$(EXECUTABLE) -s "( 5 | ( ( 3 & ( ( 0 | 1 ) | 2 ) ) & 4 ) )" aee001
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --show-leak-kinds=all --verbose -s ./$(EXECUTABLE) -s "( 5 | ( ( 3 & ( ( 0 | 1 ) | 2 ) ) & 4 ) )" aee001

perf: $(EXECUTABLE)
	perf stat ./$(EXECUTABLE)

run: $(EXECUTABLE)
#	./$(EXECUTABLE) -a "~ ~ 0 | 1" 10
#	./$(EXECUTABLE) -a "( ~  ( ~ 0 ) ) | 1" 10
#	./$(EXECUTABLE) -s "0 | 1 & 2" 0e0
#	./$(EXECUTABLE) -s "0 | 1 & 2" e00
#	./$(EXECUTABLE) -s "0 | 1 & 2" e11
#	./$(EXECUTABLE) -s "0 | 1 & 2" eae
	./$(EXECUTABLE) -s "( ( 0 & 1 ) & ( 2 & 3 ) & ( 4 & 5 ) & ( 6 & 7 ) & ( 8 & 9 ) )" e1e1e1e1e1
#	./$(EXECUTABLE) -s "0 | 1" ea
#	./$(EXECUTABLE) -s "0 | ~ ~ 1" ea
#	./$(EXECUTABLE) -s "(0 & 1) | (~12 | 10) | (4 & 13)" ee00e00000a0ae
#	./$(EXECUTABLE) -s "( 5 | ( ( 3 & ( ( 0 | 1 ) | 2 ) ) & 4 ) )" a00001

gprof: LDFLAGS = -pg -lm
gprof: all
#	./$(EXECUTABLE) -s "( 5 | ( ( 3 & ( ( 0 | 1 ) | 2 ) ) & 4 ) )" a00001
#	./$(EXECUTABLE) -s "( 5 | ( ( 3 & ( ( 0 | 1 ) | 2 ) ) & 4 ) )" ae0001
#	./$(EXECUTABLE) -s "( 5 | ( ( 3 & ( ( 0 | 1 ) | 2 ) ) & 4 ) )" aee001
#	./$(EXECUTABLE) -s "( 5 | ( ( 3 & ( ( 0 | 1 ) | 2 ) ) & 4 ) )" aeea01
#	./$(EXECUTABLE) -s "( 5 | ( ( 3 & ( ( 0 | 1 ) | 2 ) ) & 4 ) )" aeeae1
#	./$(EXECUTABLE) -s "( 5 | ( ( 3 & ( ( 0 | 1 ) | 2 ) ) & 4 ) ) & ( 6 | ( ( 7 & ( ( 8 | 9 ) | 10 ) ) & 11 ))" aeeaeaeaaeae
#	./$(EXECUTABLE) -s "( 5 | ( ( 3 & ( ( 0 | 1 ) | 2 ) ) & 4 ) ) & ( 6 | ( ( 7 & ( ( 8 | 9 ) | 10 ) ) & 11 )) & ( 12 | ( ( 13 & ( ( 14 | 15 ) | 16 ) ) & 17 ))" aeeaeaeaaeae000111                                  
#	./$(EXECUTABLE) -s "(0 & 1) | (~12 | 10) | (4 & 13)" ee00e00000a0ae aeeaeaeaaeae000111 
	@gprof $(EXECUTABLE) gmon.out > test/report_x_variaveis_comando_s.txt

test: $(OBJ_FILES)
	g++ -std=c++11 src/Pilha.cpp src/Vector.cpp program/*.cpp -Iinclude -Ithird_party -pg -o ./bin/teste_case
	./$(BIN_DIR)/teste_case

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)