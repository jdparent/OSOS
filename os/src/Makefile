ECHO  = @echo
RM    = @rm -f
RMDIR = @rm -rf
MKDIR = @mkdir -p

EXEC_NAME = kernel

INC = include
OBJ = obj

SOURCES :=  $(shell ls *.asm *.c)
OBJECTS :=  $(SOURCES:.c=.o)
OBJECTS :=  $(OBJECTS:.asm=.o)
OBJECTS :=  $(OBJECTS:%=$(OBJ)/%)

INCLUDES		+=	-I$(INC)

ASM					=		nasm
ASMFLAGS		+= 	-felf
ASMOUT			=		-o $@

CC					=		gcc -c
CFLAGS			+= -nostdlib -nostdinc -fno-builtin -fno-stack-protector
CCOUT				=		-o $@


LD					=		ld
LDFLAGS			+=	-T ../../utils/compiler/Link.ld
LDOUT				=		-o $@

GROUPSTART = -\(
GROUPEND = -\)

all: $(OBJ)/$(EXEC_NAME)

$(OBJ): 
	$(MKDIR) $(OBJ)

$(OBJ)/$(EXEC_NAME): $(OBJ)	$(OBJECTS)
	$(LD) $(LDFLAGS) $(LDOUT) $(OBJECTS)

$(OBJ)/%.o: %.c
	$(CC) $< $(CFLAGS) $(INCLUDES) $(CCOUT)

$(OBJ)/%.o: %.asm
	$(ASM) $< $(ASMFLAGS) $(ASMOUT)


.PHONY: clean
clean:
	$(RMDIR) $(OBJ)
