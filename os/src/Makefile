ECHO				=		@echo
RM					= 	@rm -f
RMDIR				=		@rm -rf

EXEC_NAME		=		kernel

SOURCES     := $(shell ls *.asm *.c)

OBJECTS 		:= 	$(SOURCES:.c=.o)
OBJECTS 		:= 	$(OBJECTS:.asm=.o)

INC					= include

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

all: $(EXEC_NAME)

$(EXEC_NAME):	$(OBJECTS)
	$(LD) $(LDFLAGS) $(LDOUT) $(OBJECTS)

%.o: %.c
	$(CC) $< $(CFLAGS) $(INCLUDES) $(CCOUT)

%.o: %.asm
	$(ASM) $< $(ASMFLAGS) $(ASMOUT)


.PHONY: clean
clean:
	$(RM) *.o $(EXEC_NAME)
