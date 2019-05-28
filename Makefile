CC=gcc
CFLAGS=-g -Wall
HEADERS=include/ include/parser.h include/fin_parser.h
SOURCE=src/shrewd.c
TARGET=shrewd

all:
	$(CC) $(CFLAGS) -I$(HEADERS) $(SOURCE) -o $(TARGET)
clean:
	rm $(TARGET)
