CC = gcc
CCFLAG = -g -Wall -pg
CCFLAG += $(addprefix -I, .)

H_SOURCE_FILES = env.h file.h mem.h heap.h 
C_SOURCE_FILES = file.c mem.c heap.c
OBJ = file.o mem.o heap.o

TARGET = esort


all: $(OBJ)
	$(CC) $(CCFLAG) -o $(TARGET)  main.c  $(OBJ)
clean:
	-rm -f esort
	-rm $(OBJ)
	-rm -f meminfo.out
	-rm -f mem.data
	-rm -f log
	-rm -rf data

%.o:$(H_SOURCE_FILES) %.c
	$(CC) $(CCFLAG) -c $(filter %.c, $^)
