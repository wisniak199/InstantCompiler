#include "JVMInstruction.h"

namespace {

typedef JVMInstructionBuilder::InstructionType InstructionType;

}

JVMBinaryOpInstruction::JVMBinaryOpInstruction(InstructionType linstr, InstructionType rinstr) : JVMInstruction(0) {
  int lstack = linstr->getStackSizeUsed();
  int rstack = rinstr->getStackSizeUsed();
  if (lstack < rstack) {
    this->linstr = rinstr;
    this->rinstr = linstr;
    this->swaped = true;
  } else {
    this->linstr = linstr;
    this->rinstr = rinstr;
    this->swaped = false;
  }
  this->stack_size_used = std::max(std::max(lstack, rstack), std::min(lstack, rstack) + 1);
}

void JVMConstInstruction::generateCode(std::ostream& out) {
  if (0 <= value && value <= 5) {
    out << "iconst_" << value << std::endl;
  } else {
    out << "ldc " << value << std::endl;
  }
}

void JVMAddInstruction::generateCode(std::ostream& out) {
  this->linstr->generateCode(out);
  this->rinstr->generateCode(out);
  out << "iadd" << std::endl;
}

void JVMSubInstruction::generateCode(std::ostream& out) {
  this->linstr->generateCode(out);
  this->rinstr->generateCode(out);
  if (this->swaped) {
    out << "swap" << std::endl;
  }
  out << "isub" << std::endl;
}

void JVMMulInstruction::generateCode(std::ostream& out) {
  this->linstr->generateCode(out);
  this->rinstr->generateCode(out);
  out << "imul" << std::endl;
}

void JVMDivInstruction::generateCode(std::ostream& out) {
  this->linstr->generateCode(out);
  this->rinstr->generateCode(out);
  if (this->swaped) {
    out << "swap" << std::endl;
  }
  out << "idiv" << std::endl;
}


void JVMPrintInstruction::generateCode(std::ostream& out) {
  if(this->expr_instruction->getStackSizeUsed() == 1) {
    out << "getstatic java/lang/System/out Ljava/io/PrintStream;" << std::endl;
    this->expr_instruction->generateCode(out);
  } else {
    this->expr_instruction->generateCode(out);
    out << "getstatic java/lang/System/out Ljava/io/PrintStream;" << std::endl
        << "swap" << std::endl;
  }
  out << "invokevirtual java/io/PrintStream/println(I)V" << std::endl;
}

void JVMAssignInstruction::generateCode(std::ostream& out) {
  this->expr_instruction->generateCode(out);
  out << "istore " << this->var_index << std::endl;
}

void JVMLoadVarInstruction::generateCode(std::ostream& out) {
  if (0 <= var_index && var_index <= 3) {
    out << "iload_" << this->var_index << std::endl;
  } else {
    out << "iload " << this->var_index << std::endl;
  }
}

InstructionType JVMInstructionBuilder::getAddInstruction(InstructionType l, InstructionType r) {
  return std::make_shared<JVMAddInstruction>(l ,r);
}

InstructionType JVMInstructionBuilder::getSubInstruction(InstructionType l, InstructionType r) {
  return std::make_shared<JVMSubInstruction>(l ,r);
}

InstructionType JVMInstructionBuilder::getMulInstruction(InstructionType l, InstructionType r) {
  return std::make_shared<JVMMulInstruction>(l ,r);
}

InstructionType JVMInstructionBuilder::getDivInstruction(InstructionType l, InstructionType r) {
  return std::make_shared<JVMDivInstruction>(l ,r);
}

InstructionType JVMInstructionBuilder::getPrintInstruction(InstructionType i) {
  return std::make_shared<JVMPrintInstruction>(i);
}

InstructionType JVMInstructionBuilder::getConstInstruction(int v) {
  return std::make_shared<JVMConstInstruction>(v);
}

InstructionType JVMInstructionBuilder::getAssignInstruction(int var_index, InstructionType instr) {
  return std::make_shared<JVMAssignInstruction>(var_index, instr);
}

InstructionType JVMInstructionBuilder::getLoadVariableInstruction(int var_index) {
  return std::make_shared<JVMLoadVarInstruction>(var_index);
}
