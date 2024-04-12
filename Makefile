compiler = g++
flags = -Wno-deprecated-declarations
# sudo apt-get install libsqlite3-dev
# sudo apt-get install libssl-dev
LDFLAGS = -lsqlite3 -lcrypto

OBJ_DIR = obj
BIN_DIR = bin

SRC_DIR = src
TEST_DIR = tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TEST_OBJ_FILES = $(filter-out $(OBJ_DIR)/main.o,$(OBJ_FILES))

TARGET = $(BIN_DIR)/program
TEST_TARGET = $(BIN_DIR)/tests

PARK_DB = data/park.db
TEST_DB = data/test.db

all: $(TARGET) $(TEST_TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(compiler) $(flags) -c $< -o $@ $(LDFLAGS)

$(BIN_DIR)/program: $(OBJ_FILES) | $(BIN_DIR)
	$(compiler) $(flags) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)/tests: $(TEST_DIR)/tests.cpp $(TEST_OBJ_FILES) | $(BIN_DIR)
	$(compiler) $(flags) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR) $(BIN_DIR):
	mkdir $@

park_db:
	touch $(PARK_DB)
	sqlite3 $(PARK_DB) < data/park_struct.sql

test_db:
	rm -f data/test.db
	touch $(TEST_DB)
	sqlite3 $(TEST_DB) < data/park_struct.sql

build: $(TARGET)

test: $(TEST_TARGET) test_db
	./$(TEST_TARGET)

run: build test park_db
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

.PHONY: all clean run test build park_db test_db