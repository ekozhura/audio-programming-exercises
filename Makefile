CC=clang++
CFLAGS=-c
LDFLAGS=
SOURCES=main.cpp oscill.cpp utils.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=osc

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -I/usr/local/include -L/usr/local/lib -lportaudio -lsndfile

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I/usr/local/include

clean: 
	rm $(OBJECTS) $(EXECUTABLE)