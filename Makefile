TARGET = out/speechSynth
CC = gcc
MAKE = make
CFLAGS = -Wall -Iinc -flto
CHMOD = chmod

PREBUILD_DIRS = out/ out/src

.PHONY: default all clean

default: $(TARGET)
all: default

HEADERS = $(wildcard *.h)
HEADERS += $(wildcard inc/*.h)

SRC_C =  $(wildcard *.c)
SRC_C += $(wildcard src/*.c)

OBJECTS = $(addprefix out/, $(SRC_C:.c=.o))

$(PREBUILD_DIRS):
	mkdir -p $@

out/%.o: %.c $(HEADERS) | $(PREBUILD_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $^ $(CFLAGS) -o $@
	$(CHMOD) +x $@

clean:
	-rm -f out/*.o
	-rm -f out/src/*.o
	-rm -f $(TARGET)
	-rm -f $(TARGET).exe
