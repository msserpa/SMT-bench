SHELL=/bin/bash
CC := gcc -fopenmp
HOST := $(shell hostname)
TARGET := bin/mixed.$(HOST).x

SOURCES := $(shell find src -type f -name *.c)
OBJECTS := $(patsubst src/%,build/%,$(SOURCES:.c=.$(HOST).o))
CFLAGS := -O0 -Wall -Wextra 
#-xHost -qopt-report=5
LDFLAGS := -lpthread -L/usr/local/lib/ -lpapi -lm

$(TARGET): $(OBJECTS)
	@echo "  ./nasm-2.13.03/nasm -DNASM_ENABLE_DEBUG=0 -w+all -o build/asm-methods.o -f elf64 src/asm-methods.asm"; ./nasm-2.13.03/nasm -DNASM_ENABLE_DEBUG=0 -w+all -o build/asm-methods.o -f elf64 src/asm-methods.asm
	@echo " Linking..."
	@echo "  $(CC) $^ -o $(TARGET) build/asm-methods.o $(LDFLAGS)"; $(CC) $^ -o $(TARGET) build/asm-methods.o $(LDFLAGS)

build/%.$(HOST).o: src/%.c
	@echo "  $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo "  rm -rf build/*.o* bin/mixed* "; rm -rf build/*.o* bin/mixed*

.PHONY: clean
