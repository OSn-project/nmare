TARGET = nmare
LIBBASE_SRC = ../OSn/root/libs/libbase
LIBS = $(LIBBASE_SRC)/src/libbase.a
CC = clang++
CFLAGS = -g -O0 -Wall -isystem $(LIBBASE_SRC)/include

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = main.o lexer.o token.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
