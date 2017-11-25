CC = gcc

CCflag += -g -Wall
CCflag += $(addprefix -I, .)

OBJ = stack_pop.o stack_push.o stack_cur_point.o
H_FILES = stack.h


all:$(H_FILES) $(OBJ) 
	$(CC) $(CCflag) -o maze main.c $(OBJ) 

clean:
	-rm -f $(OBJ) main.c 
	-rm -f maze 

%.o:%.c
	$(CC) $(CCflag) -c $(filter %.c, $^) 
