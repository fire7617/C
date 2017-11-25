libdir = /home/fire7617/usr/include/CUnit/

vpath %.h $(libdir)

C_SRC_FILES += main.c
H_SRC_FILES +=

INC_DIRS += /home/fire7617/usr/include/
LIB_DIRS +=
LIB_DIRS += /home/fire7617/usr/lib
LIB_NAMES += cunit

OBJ_FILES += $(C_SRC_FILES:.c=.o)

EXE_PROG ?= heap.exe

TEST_FLAG += _UNIT_TEST_

CC = gcc
CCFLAGS += -g -Wall
CCFLAGS += $(addprefix -I, $(INC_DIRS))
LD_FLAGS += $(addprefix -D, $(TEST_FLAG))
LD_FLAGS += $(addprefix -L, $(LIB_DIRS))
LD_FLAGS += $(addprefix -l, $(LIB_NAMES))


all:$(H_SRC_FILES) main.o 
	$(CC) $(CCFLAGS) $(LD_FLAGS)  -o $(EXE_PROG)  $(OBJ_FILES)

clean:
	-rm -f $(EXE_PROG)
	-rm -f $(OBJ_FILES)

%.o:$(H_SRC_FILES) %.c
	$(CC) $(CCFLAGS) $(LD_FLAGS) -c $(filter %.c,$^)
