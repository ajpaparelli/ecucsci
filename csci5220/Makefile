CC	= gcc
LINK	= gcc
CFLAGS	= -Wall
RM	= rm

CFILES	= src/stringtable.c\
	  src/teststringtable.c

OFILES	= $(patsubst src/%.c,obj/%.o,$(CFILES))

EFILES	= bin/teststringtable

STRINGTABLE_OFILES = obj/stringtable.o\
		     obj/teststringtable.o

teststringtable: $(STRINGTABLE_OFILES)
	$(LINK) -o bin/teststringtable $(STRINGTABLE_OFILES)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OFILES) $(EFILES)
