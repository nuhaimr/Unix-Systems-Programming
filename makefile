EXEC = pipesim
OBJ = PipeSimulator.o LinkedList.o
CC = gcc 
CFLAGS = -g


$(EXEC)	:	$(OBJ)
	$(CC) $(OBJ) -o $(EXEC)


PipeSimulator.o	:	PipeSimulator.c PipeSimulator.h LinkedList.h
	$(CC) -c PipeSimulator.c $(CFLAGS)


LinkedList.o	:	LinkedList.c LinkedList.h
	$(CC) -c LinkedList.c $(CFLAGS)


clean:
	rm -f $(EXEC) $(OBJ)
