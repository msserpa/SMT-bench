SHELL=/bin/bash
CC := icc
HOST := $(shell hostname)
TARGET := bin/mixed.$(HOST)

SOURCES := $(shell find src -type f -name *.c)
OBJECTS := $(patsubst src/%,build/%,$(SOURCES:.c=.$(HOST).o))
CFLAGS := -O0  -Wmissing-declarations	 -Wunused-variable	 -Wpointer-arith -Wuninitialized -Wdeprecated -Wabi -Wunused-function -Wunknown-pragmas -Wmain -Wcomments -Wreturn-type   -Wall -Wextra -Werror 
#-xHost -qopt-report=5
LDFLAGS := -lpthread -L$(HOME)/papi/lib/ -lpapi -lm
INC := -I$(HOME)/papi/include/

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LDFLAGS)"; $(CC) $^ -o $(TARGET) $(LDFLAGS)

build/%.$(HOST).o: src/%.c
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo "rm -rf build/*.o* bin/mixed* "; rm -rf build/*.o* bin/mixed*

.PHONY: clean
