CC = gcc

SRC_DIR = ./src
INC_DIR = $(SRC_DIR)/miniaudio
OUT_DIR = ./output

CFLAGS = -std=c11 -Wall -Wextra -I$(INC_DIR)
LDFLAGS = -lm -lpthread -ldl

SOURCES = $(shell find $(SRC_DIR) -type f -name '*.c')
TARGET = $(OUT_DIR)/rithmos

build: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

run: build
	./$(TARGET)

clean:
	rm -rf $(OUT_DIR)
