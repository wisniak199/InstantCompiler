#include <iostream>
#include <cstdio>
#include <locale>

#include <lib/parser/Parser.H>

#include "JVMVisitor.h"
#include "CompileError.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <filename> <classname>" << std::endl;
    return 1;
  }

  FILE *input = fopen(argv[1], "r");
  if (!input) {
    std::cout << "Cannot open file: " << argv[1] << std::endl;
    return 1;
  }

  Program *program = pProgram(input);
  if (!program) {
    std::cout << "Failed to parse program" << std::endl;
    fclose(input);
    return 1;
  }
  JVMVisitor jvm_visitor(argv[2]);

  int res = 0;
  try {
    program->accept(&jvm_visitor);
    jvm_visitor.generateIR();
  } catch(CompileError& e) {
    std::cerr << "Compilation Error: " << e.what() << std::endl;
    res = 1;
  }
  fclose(input);
  return res;
}
