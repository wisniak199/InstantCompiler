CC = /home/wisniak199/mrjp/llvm-3.7.0/bin/clang++
LLVM_FLAGS = $(shell /home/wisniak199/mrjp/llvm-3.7.0/bin/llvm-config --cxxflags)
LLVM_LINK = $(shell /home/wisniak199/mrjp/llvm-3.7.0/bin/llvm-config --ldflags --system-libs --libs core)
CC_FLAGS = -I. -std=c++11

all: insc_llvm.bin insc_jvm.bin

insc_llvm.bin: parser insc_llvm.o LLVMVisitor.o src/insc_llvm.sh
	$(CC) $(CC_FLAGS) -o insc_llvm.bin LLVMVisitor.o insc_llvm.o lib/parser/Absyn.o lib/parser/Lexer.o lib/parser/Parser.o $(LLVM_LINK)
	cp src/insc_llvm.sh insc_llvm

insc_jvm.bin: parser insc_jvm.o JVMVisitor.o JVMInstruction.o src/insc_jvm.sh
	$(CC) $(CC_FLAGS) -o insc_jvm.bin JVMInstruction.o JVMVisitor.o insc_jvm.o lib/parser/Absyn.o lib/parser/Lexer.o lib/parser/Parser.o
	cp src/insc_jvm.sh insc_jvm

.PHONY: parser
parser:
	cd lib/parser && $(MAKE)

insc_llvm.o: src/insc_llvm.cpp
	$(CC) $(CC_FLAGS) $(LLVM_FLAGS) -fexceptions -c src/insc_llvm.cpp

LLVMVisitor.o: src/LLVMVisitor.cpp src/LLVMVisitor.h
	${CC} $(CC_FLAGS) $(LLVM_FLAGS) -fexceptions -c src/LLVMVisitor.cpp

insc_jvm.o: src/insc_jvm.cpp
	$(CC) $(CC_FLAGS) -c src/insc_jvm.cpp

JVMVisitor.o: src/JVMVisitor.cpp src/JVMVisitor.h
	${CC} $(CC_FLAGS) -c src/JVMVisitor.cpp

JVMInstruction.o: src/JVMInstruction.cpp src/JVMInstruction.h
	${CC} $(CC_FLAGS) -c src/JVMInstruction.cpp

clean:
	cd lib/parser && $(MAKE) clean
	rm insc_jvm insc_llvm insc_llvm.bin insc_jvm.bin *.o
