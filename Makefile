
CC = gcc

SRC_DIR = ./src
INC_DIR = $(SRC_DIR)/external/miniaudio
OUT_DIR = ./output

# Compiler flags for Rithmos (Be hella strict!)
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -Wformat=2 -Wshadow -Wconversion -Wstrict-prototypes -Wmissing-prototypes -O2 -march=native -fstack-protector-strong -fsanitize=address,undefined -fno-omit-frame-pointer -pthread

# Less strict flags for MiniAudio
MINIAUDIO_CFLAGS = -std=c11 -O2 -pthread

# Linker configuration
LDFLAGS = -Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack -Wl,--as-needed -fsanitize=address,undefined -lm -pthread -ldl

LDLIBS = -lm -pthread -ldl

# Source files locations and seperating MiniAudio and everything else
MINIAUDIO_SRC = $(INC_DIR)/miniaudio.c
SOURCES = $(filter-out $(MINIAUDIO_SRC),$(shell find $(SRC_DIR) -type f -name '*.c'))

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OUT_DIR)/%.o,$(SOURCES))
MINIAUDIO_OBJ = $(OUT_DIR)/miniaudio/miniaudio.o

TARGET = $(OUT_DIR)/rithmos

.PHONY: build run clean

build: $(TARGET)

# Compile Rithmos source files with strict warnings
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Compile MiniAudio separately so that it doesn't kill us
$(MINIAUDIO_OBJ): $(MINIAUDIO_SRC)
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(MINIAUDIO_CFLAGS) -c $< -o $@

# Link everything together to make shit run properly
$(TARGET): $(OBJECTS) $(MINIAUDIO_OBJ)
	$(CC) $(OBJECTS) $(MINIAUDIO_OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

run: build
	./$(TARGET)

clean:
	rm -rf $(OUT_DIR)
