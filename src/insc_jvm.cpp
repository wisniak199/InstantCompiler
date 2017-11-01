#include <iostream>
#include <cstdio>

#include <parser/Parser.H>

#include "JVMVisitor.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
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
  JVMVisitor jvm_visitor;
  program->accept(&jvm_visitor);
  jvm_visitor.generateIR();
  fclose(input);
  return 0;
}
