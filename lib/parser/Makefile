CC = g++
CCFLAGS = -g
FLEX = flex
BISON = bison
LATEX = latex
DVIPS = dvips

all: TestInstant Instant.ps

clean:
	rm -f *.o Instant.dvi Instant.aux Instant.log Instant.ps TestInstant

distclean:
	 rm -f *.o Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H Instant.l Instant.y Instant.tex Instant.dvi Instant.aux Instant.log Instant.ps TestInstant Makefile

TestInstant: Absyn.o Lexer.o Parser.o Printer.o Test.o
	@echo "Linking TestInstant..."
	${CC} ${CCFLAGS} *.o -o TestInstant
        
Absyn.o: Absyn.C Absyn.H
	${CC} ${CCFLAGS} -c Absyn.C

Lexer.C: Instant.l
	${FLEX} -oLexer.C Instant.l

Parser.C: Instant.y
	${BISON} Instant.y -o Parser.C

Lexer.o: Lexer.C Parser.H
	${CC} ${CCFLAGS} -c Lexer.C 

Parser.o: Parser.C Absyn.H
	${CC} ${CCFLAGS} -c Parser.C

Printer.o: Printer.C Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Printer.C

Skeleton.o: Skeleton.C Skeleton.H Absyn.H
	${CC} ${CCFLAGS} -c Skeleton.C

Test.o: Test.C Parser.H Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Test.C

Instant.dvi: Instant.tex
	${LATEX} Instant.tex

Instant.ps: Instant.dvi
	${DVIPS} Instant.dvi -o Instant.ps

