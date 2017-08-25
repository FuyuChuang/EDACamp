CC=g++
LDFLAGS=-std=c++11 -O3
SOURCES=src/checker.cpp src/main.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=checker
INCLUDES=src/checker.h src/car.h

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o:  %.c  ${INCLUDES}
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
