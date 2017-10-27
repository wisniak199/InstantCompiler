CC = /home/wisniak199/mrjp/llvm-3.7.0/bin/clang++
LLVM_FLAGS = $(shell /home/wisniak199/mrjp/llvm-3.7.0/bin/llvm-config --cxxflags)
LLVM_LINK = $(shell /home/wisniak199/mrjp/llvm-3.7.0/bin/llvm-config --ldflags --system-libs --libs core)
CC_FLAGS = $(LLVM_FLAGS) -I.

all: insc_llvm

insc_llvm: parser insc_llvm.o LLVMVisitor.o
	$(CC) $(CC_FLAGS) -o insc_llvm LLVMVisitor.o insc_llvm.o parser/Absyn.o parser/Lexer.o parser/Parser.o $(LLVM_LINK)

parser:
	cd parser && $(MAKE)

insc_llvm.o: src/insc_llvm.cpp
	$(CC) $(CC_FLAGS) -c src/insc_llvm.cpp

LLVMVisitor.o: src/LLVMVisitor.cpp src/LLVMVisitor.h
	${CC} $(CC_FLAGS) -c src/LLVMVisitor.cpp

clean:
	cd parser && $(MAKE) clean
	cd src && rm -f *.o
	rm insc_llvm
