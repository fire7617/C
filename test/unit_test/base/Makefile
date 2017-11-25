libdir=/home/fire7617/usr/include/CUnit

vpath %.h $(libdir)

TARGET_OBJFILES += $(C_SRC_FILES:.c=.o)

H_FILES=$(libdir)/CUnit
SRC_FILES=


INC_DIRS += /home/fire7617/usr/include
LIB_DIRS += .
LIB_DIRS += /home/fire7617/usr/lib
LIB_NAMES += cunit

TARGET_EXE = test

CC = gcc
CCFLAGS += -Wall -g
CCFLAGS += $(addprefix -I, $(INC_DIRS))
LDFLAGS += $(addprefix -l, $(LIB_NAMES))
LDFLAGS += $(addprefix -L, $(LIB_DIRS))

test_var:
	@echo INC_DIRS= $(INC_DIRS)
	@echo LIB_DIRS= $(LIB_DIRS)
	@echo LIB_NAMES= $(LIB_NAMES)

all:
	$(CC) $(CCFLAGS) test.c -o $(TARGET_EXE) $(LDFLAGS) 

clean:
	-rm -f $(TARGET_OBJFILES)
	-rm -f $(TARGET_EXE)

%.o: $(H_FILES) %.c
	$(CC) $(CCFLAGS) -c $(filter %.c, $^)
