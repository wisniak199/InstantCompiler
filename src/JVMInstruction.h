#ifndef JVM_INSTRUCTION_H
#define JVM_INSTRUCTION_H

#include <iostream>
#include <memory>


class JVMInstruction {
public:
  JVMInstruction(int stack_size_used) : stack_size_used(stack_size_used) {}
  virtual ~JVMInstruction() {}
  virtual void generateCode(std::ostream&) = 0;
  int getStackSizeUsed() {return stack_size_used;}
  typedef std::shared_ptr<JVMInstruction> InstructionType;
protected:
  int stack_size_used;
};

class JVMConstInstruction : public JVMInstruction {
public:
  JVMConstInstruction(int value) : JVMInstruction(1), value(value) {}
  ~JVMConstInstruction() {}
  void generateCode(std::ostream&) override;

private:
  int value;
};


class JVMBinaryOpInstruction : public JVMInstruction {
public:
  JVMBinaryOpInstruction(InstructionType, InstructionType);
  virtual ~JVMBinaryOpInstruction() {}
protected:
  InstructionType linstr;
  InstructionType rinstr;
  bool swaped;
};


class JVMAddInstruction : public JVMBinaryOpInstruction {
public:
  JVMAddInstruction(InstructionType li, InstructionType ri) : JVMBinaryOpInstruction(li, ri) {}
  void generateCode(std::ostream&) override;
};

class JVMSubInstruction : public JVMBinaryOpInstruction {
public:
  JVMSubInstruction(InstructionType li, InstructionType ri) : JVMBinaryOpInstruction(li ,ri) {}
  void generateCode(std::ostream&) override;
};

class JVMMulInstruction : public JVMBinaryOpInstruction {
public:
  JVMMulInstruction(InstructionType li, InstructionType ri) : JVMBinaryOpInstruction(li ,ri) {}
  void generateCode(std::ostream&) override;
};

class JVMDivInstruction : public JVMBinaryOpInstruction {
public:
  JVMDivInstruction(InstructionType li, InstructionType ri) : JVMBinaryOpInstruction(li, ri) {}
  void generateCode(std::ostream&) override;
};

class JVMPrintInstruction : public JVMInstruction {
public:
  JVMPrintInstruction(InstructionType i) : JVMInstruction(std::max(i->getStackSizeUsed(), 2)), expr_instruction(i) {}
  void generateCode(std::ostream&) override;
private:
  InstructionType expr_instruction;
};

class JVMAssignInstruction : public JVMInstruction {
public:
  JVMAssignInstruction(int var_index, InstructionType i) : JVMInstruction(i->getStackSizeUsed()), var_index(var_index), expr_instruction(i) {}
  void generateCode(std::ostream&) override;
private:
  int var_index;
  InstructionType expr_instruction;
};

class JVMLoadVarInstruction : public JVMInstruction {
public:
  JVMLoadVarInstruction(int var_index) : JVMInstruction(1), var_index(var_index) {}
  void generateCode(std::ostream&) override;
private:
  int var_index;
};

class JVMInstructionBuilder {
public:
  typedef JVMInstruction::InstructionType InstructionType;

  InstructionType getAddInstruction(InstructionType, InstructionType);
  InstructionType getSubInstruction(InstructionType, InstructionType);
  InstructionType getMulInstruction(InstructionType, InstructionType);
  InstructionType getDivInstruction(InstructionType, InstructionType);
  InstructionType getPrintInstruction(InstructionType);
  InstructionType getAssignInstruction(int, InstructionType);
  InstructionType getConstInstruction(int);
  InstructionType getLoadVariableInstruction(int);

};

#endif
