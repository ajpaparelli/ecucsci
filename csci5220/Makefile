CC     = gcc
LINK   = gcc
CFLAGS = -Wall
RM     = rm

CFILES = src/stringtable.c\
         src/teststringtable.c\
         src/lex.yy.c\
         src/testlexer.c\
	 src/ast.c\
	 src/testast.c\
	 src/symboltable.c\
	 src/testsymbol.c

OFILES = $(patsubst src/%.c,obj/%.o,$(CFILES))

EFILES = bin/teststringtable\
         bin/testlexer

STRINGTABLE_OFILES = obj/stringtable.o\
                     obj/teststringtable.o

TESTLEXER_OFILES = obj/stringtable.o\
		   obj/lex.yy.o\
                   obj/testlexer.o

AST_OFILES	= obj/stringtable.o\
		  obj/ast.o\
		  obj/testast.o

SYM_OFILES	= obj/stringtable.o\
		  obj/ast.o\
		  obj/symboltable.o\
		  obj/testsymbol.o

teststringtable: $(STRINGTABLE_OFILES)
	$(LINK) -o bin/teststringtable $(STRINGTABLE_OFILES)

testlexer: $(TESTLEXER_OFILES)
	$(LINK) -o bin/testlexer $(TESTLEXER_OFILES)

testast: $(AST_OFILES)
	$(LINK) -o bin/testast $(AST_OFILES)

testsymbol: $(SYM_OFILES)
	$(LINK) -o bin/testsymbol $(SYM_OFILES)

src/lex.yy.c: src/lexer.lex
	cd src; flex lexer.lex

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OFILES) $(EFILES)
