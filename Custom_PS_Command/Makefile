CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = ps08

run:
	./$(EXE)

$(EXE): ps08.h ps08.c setinfo.o processes.o
	$(CC) $(WARNING_FLAGS) -g ps08.c setinfo.o processes.o -o ps08

setinfo.o: ps08.h setinfo.c
	$(CC) $(WARNING_FLAGS) -g -c setinfo.c

processes.o: ps08.h processes.c
	$(CC) $(WARNING_FLAGS) -g -c processes.c

clean: 
	rm -r *.o