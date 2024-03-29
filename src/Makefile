SRCEXT      := c
OBJEXT      := o
HEADEREXT   := h

# directories

SRC_DIR     := ../src
BUILD_DIR   := ../build
BIN_DIR     := ../bin
LIB_DIR     := ../lib
INCLUDE_DIR := ../include

# compiler options

EXE_NAME    := xhash

CC          := gcc
CFLAGS      := -Wall -Ofast
CDBGFLAGS   := -Wall -g -ggdb -D DEBUG
DBG         := gdb -q

INCLUDE     := -I $(INCLUDE_DIR) -I $(LIB_DIR)
LIB         := -L$(LIB_DIR) -lm

## release build

OBJECTS     := $(patsubst %.$(SRCEXT), %.$(OBJEXT), $(wildcard *.$(SRCEXT)))

all: mkdirp $(OBJECTS) cpobj

%.$(OBJEXT): %.$(SRCEXT)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

## debug build

DBG_OBJECTS := $(patsubst %.$(SRCEXT), %-dbg.$(OBJEXT), $(wildcard *.$(SRCEXT)))

dbg: mkdirp $(DBG_OBJECTS) cpobj

%-dbg.$(OBJEXT): %.$(SRCEXT)
	$(CC) $(CDBGFLAGS) $(INCLUDE) -c -o $@ $<

cpobj:
	@cp *.$(OBJEXT) $(BUILD_DIR)

mkdirp:
	@mkdir -p $(BUILD_DIR)/

clean:
	@rm -f *.$(OBJEXT)

cleaner: clean
	@rm -f $(BUILD_DIR)/*.$(OBJEXT)
