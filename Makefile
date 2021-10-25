CC = /usr/local/opt/llvm/bin/clang
INCLUDES = -Iinclude -I/usr/local/include 
LIBS = -L/usr/local/lib
CFLAGS = -g -Wall -Wextra -pedantic -std=c17 -Wno-unused-command-line-argument -std=c17 $(INCLUDES) $(LIBS)

SRC_FILES = testing-logger tester-list
OBJ_FILES = $(addprefix obj/,$(SRC_FILES:=.o))
LIB_FILES = testing-logger

MAIN = testing-example
MAIN_BINS = $(addprefix bin/,$(MAIN))
TEST_BINS = $(addprefix bin/test-, $(SRC_FILES))
LIBS_ARCH = $(addprefix lib/lib, $(LIB_FILES:=.a))

all: $(MAIN_BINS) $(TEST_BINS)

# Directory targets
obj:
	mkdir obj
bin:
	mkdir bin
lib:
	mkdir lib

# Binary targets
bin/%: main/%.c $(OBJ_FILES) | bin
	$(CC) $(CFLAGS) $^ -o $@

bin/test-%: tests/test-%.c $(OBJ_FILES) | bin
	$(CC) $(CFLAGS) $^ -o $@

# Object targets
obj/%.o: src/%.c | obj
	$(CC) -c $(CFLAGS) $^ -o $@

obj/%.o: main/%.c | obj
	$(CC) -c $(CFLAGS) $^ -o $@

obj/%.o: tests/%.c | obj
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -rf bin
	rm -rf obj
	rm -rf lib

test: $(TEST_BINS)
	@for f in $(TEST_BINS); do echo $$f; ASAN_OPTIONS=detect_leaks=1 $$f; echo; done

memcheck:
	ASAN_OPTIONS=detect_leaks=1 ./bin/main

.SECONDARY: 

# Library files
libs: $(LIBS_ARCH)

lib/lib%.a: $(OBJ_FILES) | lib
	ar rcs $@ $^
