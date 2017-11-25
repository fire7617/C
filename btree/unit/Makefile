#######  basic project environment ############
updir1 = $(patsubst %/, %, $(dir $(PWD)))
updir2 = $(patsubst %/, %, $(dir $(updir1)))

PROJHOME = $(strip $(updir1))
SRC_ROOT = $(PROJHOME)/src

#################################
#
# setup source dirctory and files 
#
##################################i####

SRC_DIRS += $(SRC_ROOT)/Node
SRC_DIRS += $(SRC_ROOT)/info

INC_DIRS += $(SRC_DIRS)
INC_DIRS += $(SRC_ROOT)/env

LIB_DIRS += . 
LIB_NAMES += Node

vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIRS)

C_SRC_FILES = $(notdir $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c)))
H_SRC_FILES = $(notdir $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.h)))

TARGET_OBJFILES  += $(C_SRC_FILES:.c=.o)

############################
#
#running rules of programs
##############################

HELP_OBJFILES += $(C_HELP_FILES:.c=.o)

EXE_PROGS = btree

####################
#user interface
####################
TARGETS ?= $(EXE_PROGS)

all: $(TARGETS)

clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f out
	-rm -f $(TARGETS)
	-rm -f bt.info

test_var:
	@echo updir1:$(updir1)
	@echo PROJHOME:$(PROJHOME)
	@echo SRC_ROOT:$(SRC_ROOT)
	@echo SRC_DIRS:$(SRC_DIRS)
	@echo INC_DIRS:$(INC_DIRS)
	@echo C_SRC_FILES:$(C_SRC_FILES)
	@echo H_SRC_FILES:$(H_SRC_FILES)
	
##################################
#
#compilation rules
#######################################

CC = gcc

CCFLAGS += -Wall -g
CCFLAGS += $(addprefix -I, $(INC_DIRS))
LD_FLAGS += $(addprefix -l, $(LIB_NAMES))
LD_FLAGS += $(addprefix -L, $(LIB_DIRS))


btree: lib$(LIB_NAMES).a $(TARGET_OBJFILES) $(HELP_OBJFILES) btree.o
	$(CC) $(CCFLAGS) -o btree btree.o $(LD_FLAGS)

%.a:$(TARGET_OBJFILES)
	ar rcs lib$(LIB_NAMES).a  $(TARGET_OBJFILES)

%.o:$(H_SRC_FILES) %.c
	$(CC) $(CCFLAGS) -c $(filter %.c, $^)


