# Makefile for PK-Formula C implementation

CC = gcc
CFLAGS = -Wall -O2 -std=c99
LDFLAGS = -lm

# Source files
SOURCES = pk_formula.c
HEADERS = pk_formula.h
OBJECTS = $(SOURCES:.c=.o)

# Examples
EXAMPLES = example_basic
EXAMPLE_SOURCES = $(EXAMPLES:=.c)
EXAMPLE_OBJECTS = $(EXAMPLES:=.o)

# Default target
all: $(EXAMPLES)

# Build examples
example_basic: example_basic.o pk_formula.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Run examples
run: example_basic
	./example_basic

# Clean build files
clean:
	rm -f $(OBJECTS) $(EXAMPLE_OBJECTS) $(EXAMPLES)

# Clean everything including backup files
distclean: clean
	rm -f *~ *.bak

# Install (copy to /usr/local)
install: pk_formula.o
	install -d /usr/local/include
	install -m 644 pk_formula.h /usr/local/include/
	install -d /usr/local/lib
	ar rcs libpk_formula.a pk_formula.o
	install -m 644 libpk_formula.a /usr/local/lib/

# Uninstall
uninstall:
	rm -f /usr/local/include/pk_formula.h
	rm -f /usr/local/lib/libpk_formula.a

# Help
help:
	@echo "PK-Formula C Implementation Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  all        - Build all examples (default)"
	@echo "  run        - Build and run basic example"
	@echo "  clean      - Remove build files"
	@echo "  distclean  - Remove all generated files"
	@echo "  install    - Install library to /usr/local (requires sudo)"
	@echo "  uninstall  - Remove installed files"
	@echo "  help       - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make              # Build examples"
	@echo "  make run          # Build and run"
	@echo "  make clean        # Clean build files"
	@echo "  sudo make install # Install library system-wide"

.PHONY: all run clean distclean install uninstall help
