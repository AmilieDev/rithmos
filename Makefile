# build file which works on macOS or Linux ya :D

UNAME_S := $(shell uname -s)

SRC_DIR = ./src
INC_DIR = $(SRC_DIR)/external/miniaudio
OUT_DIR = ./output

# Platform-specific configuration (macOS or Linux)
ifeq ($(UNAME_S),Darwin)
    CC = clang
    PLATFORM = macOS

    # Apple Clang security and sanitizer flags
    ARCH_FLAGS =
    HARDEN_FLAGS = -fstack-protector-strong
    SANITIZER_FLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer

    # macOS uses Mach-O, not ELF
    PLATFORM_LDFLAGS =
    PLATFORM_LIBS =

# For Linux
else
    CC = gcc
    PLATFORM = Linux

    ARCH_FLAGS = -march=native
    HARDEN_FLAGS = -fstack-protector-strong
    SANITIZER_FLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer

    # Linux ELF linker hardening
    PLATFORM_LDFLAGS = -Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack -Wl,--as-needed
    PLATFORM_LIBS = -lm -pthread -ldl
endif

# !! NO WINDOWS SUPPORT !!

# Strict warnings for Rithmos which miniaudio isnt compatible with
WARNING_FLAGS = -Wall -Wextra -Werror -Wpedantic \
                -Wformat=2 -Wshadow -Wconversion \
                -Wstrict-prototypes -Wmissing-prototypes

# Compiler flags
CFLAGS = -std=c11 $(WARNING_FLAGS) -O2 \
         $(ARCH_FLAGS) $(HARDEN_FLAGS) \
         $(SANITIZER_FLAGS) -pthread

# MiniAudio compiles with relaxed warnings bc it isnt compatible with all of rithmos' handling (see above)
MINIAUDIO_CFLAGS = -std=c11 -O2 -pthread

# Linker flags
LDFLAGS = $(PLATFORM_LDFLAGS) $(SANITIZER_FLAGS)
LDLIBS = $(PLATFORM_LIBS)

# Find source files
MINIAUDIO_SRC = $(INC_DIR)/miniaudio.c
SOURCES = $(filter-out $(MINIAUDIO_SRC),$(shell find $(SRC_DIR) -type f -name '*.c'))

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OUT_DIR)/%.o,$(SOURCES))
MINIAUDIO_OBJ = $(OUT_DIR)/miniaudio/miniaudio.o

TARGET = $(OUT_DIR)/rithmos

# Automatically generate header dependencies
DEPFLAGS = -MMD -MP
DEPS = $(OBJECTS:.o=.d) $(MINIAUDIO_OBJ:.o=.d)

.PHONY: build run clean info

build: $(TARGET)

# Compile Rithmos with strict warnings
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Compile MiniAudio separately
$(MINIAUDIO_OBJ): $(MINIAUDIO_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(MINIAUDIO_CFLAGS) $(DEPFLAGS) -c $< -o $@

# Link executable
$(TARGET): $(OBJECTS) $(MINIAUDIO_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(OBJECTS) $(MINIAUDIO_OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

# Run Rithmos from a built project
run: build
	./$(TARGET)

# Show build configuration
info:
	@echo "Rithmos Build Configuration"
	@echo "Platform: $(PLATFORM)"
	@echo "Compiler: $(CC)"
	@echo "Architecture flags: $(ARCH_FLAGS)"
	@echo "Sanitizers: $(SANITIZER_FLAGS)"

# Remove build artifacts (/output)
clean:
	rm -rf $(OUT_DIR)

# Include generated dependency files
-include $(DEPS)
