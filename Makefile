SRCEXT      := c
OBJEXT      := o
HEADEREXT   := h

# directories

SRC_DIR     := src
BUILD_DIR   := build
BIN_DIR     := bin
LIB_DIR     := lib
INCLUDE_DIR := include

# compiler options

EXE_NAME    := xhash

CC          := gcc
CFLAGS      := -Wall -Ofast
CDBGFLAGS   := -Wall -g -ggdb -D DEBUG
DBG         := gdb -q

INCLUDE     := -I $(INCLUDE_DIR) -I $(LIB_DIR)
LIB         := -L$(LIB_DIR) -lm

# targets

TARGET_NAME := $(EXE_NAME)
TARGET      := $(BIN_DIR)/$(TARGET_NAME)
DBG_TARGET  := $(BIN_DIR)/$(TARGET_NAME)-dbg

SOURCES     := $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT))
HEADERS     := $(shell find $(INCLUDE_DIR)/ -name "*."$(HEADEREXT))

## release build

all: mkdirp $(TARGET)

OBJECTS     := $(patsubst $(SRC_DIR)/%.$(SRCEXT), $(BUILD_DIR)/%.$(OBJEXT), $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)))

$(OBJECTS): $(SOURCES)
	@cd $(SRC_DIR) && $(MAKE)

$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) -o $(TARGET) $(LIB)

## debug build

dbg: mkdirp $(DBG_TARGET)

DBG_OBJECTS := $(patsubst $(SRC_DIR)/%.$(SRCEXT), $(BUILD_DIR)/%-dbg.$(OBJEXT), $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)))

$(DBG_OBJECTS): $(SOURCES)
	@cd $(SRC_DIR) && $(MAKE) dbg

$(DBG_TARGET): $(DBG_OBJECTS)
	@$(CC) $(CDBGFLAGS) $(INCLUDE) $(DBG_OBJECTS) -o $(DBG_TARGET) $(LIB)

## execution

run: mkdirp $(TARGET)
	./$(TARGET)

rundbg: mkdirp $(DBG_TARGET)
	$(DBG) $(DBG_TARGET)

## mkdirp

mkdirp:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

## Clean

clean:
	@cd $(SRC_DIR) && $(MAKE) clean

cleaner:
	@cd $(SRC_DIR) && $(MAKE) cleaner
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)
