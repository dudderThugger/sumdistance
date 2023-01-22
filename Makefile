CC=g++
CFLAGS= 
DEPS = graph.h
OBJ = main.o graph.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

output: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)