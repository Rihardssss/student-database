CC = gcc
CFLAGS = -Wall -Wextra

OUTPUT = main

SOURCES = main.c database.c
HEADERS = database.h students.h

OBJECTS = $(SOURCES:.c=.o)


all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OUTPUT)
